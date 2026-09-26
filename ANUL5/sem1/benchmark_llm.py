import re
import time
import unicodedata
from pathlib import Path

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from ollama import Client

# ============================================================
# Lucrarea de laborator 2 - Modele LLM cu acces deschis
# Benchmark pentru 3 modele locale Ollama
# ============================================================

OLLAMA_HOST = "http://localhost:11434"

MODELS = [
    "gemma3:1b",
    "granite4:3b",
    "llama3.2",
]

# Dimensiuni de rezervă (GB). Se folosesc doar dacă Ollama nu poate fi interogat;
# în mod normal dimensiunea se citește automat (vezi get_model_size_gb).
MODEL_SIZE_GB = {
    "gemma3:1b": 0.82,
    "granite4:3b": 2.1,
    "llama3.2": 2.0,
}

GEN_OPTIONS = {
    "temperature": 0.2,
    "top_p": 0.9,
    "repeat_penalty": 1.1,
    "num_ctx": 4096,
}

SYSTEM_PROMPT = (
    "Ești un asistent educațional. Răspunde concis și exact. "
    "Pentru întrebări factuale, scrie pe ultima linie exact "
    "'RĂSPUNS FINAL: <răspuns>'. "
    "Pentru probleme de matematică, arată pe scurt pașii, apoi scrie pe ultima linie exact "
    "'RĂSPUNS FINAL: <valoare>'."
)

# 20 de întrebări: 6 istorie, 6 limba română, 8 matematică
# ref     = răspunsul de referință
# alt     = variante acceptate ca răspuns corect complet (opțional)
# partial = fragmente care aduc scor parțial (opțional)
# ref_num = valoarea numerică de referință (doar matematică)
DATASET = [
    {"id": 1, "cat": "istorie", "q": "Cine a fost ales domnitor al Moldovei și al Țării Românești în 1859?", "ref": "Alexandru Ioan Cuza", "alt": ["Cuza"]},
    {"id": 2, "cat": "istorie", "q": "În ce oraș a fost votată Unirea Transilvaniei cu România la 1 Decembrie 1918?", "ref": "Alba Iulia"},
    {"id": 3, "cat": "istorie", "q": "În ce an a fost anexată Basarabia de către Imperiul Rus?", "ref": "1812"},
    {"id": 4, "cat": "istorie", "q": "Care domnitor a realizat în 1600 prima unire politică a Țării Românești, Moldovei și Transilvaniei?", "ref": "Mihai Viteazul"},
    {"id": 5, "cat": "istorie", "q": "Pe ce dată a proclamat Republica Moldova independența?", "ref": "27 august 1991", "alt": ["27 august"], "partial": ["1991"]},
    {"id": 6, "cat": "istorie", "q": "În ce oraș a fost semnat, în 1878, tratatul care a recunoscut independența României?", "ref": "Berlin"},

    {"id": 7, "cat": "română", "q": "Care este pluralul substantivului «ou»?", "ref": "ouă"},
    {"id": 8, "cat": "română", "q": "Care este forma articulată de genitiv-dativ singular a substantivului «fată»?", "ref": "fetei"},
    {"id": 9, "cat": "română", "q": "Care este pluralul substantivului «băiat»?", "ref": "băieți"},
    {"id": 10, "cat": "română", "q": "Care este participiul verbului «a face»?", "ref": "făcut"},
    {"id": 11, "cat": "română", "q": "Ce parte de vorbire este cuvântul «lângă» în propoziția «Stau lângă fereastră.»?", "ref": "prepoziție"},
    {"id": 12, "cat": "română", "q": "Care este antonimul adjectivului «bogat»?", "ref": "sărac"},

    {"id": 13, "cat": "matematica", "q": "Calculează: 847 + 1596 =", "ref": "2443", "ref_num": 2443},
    {"id": 14, "cat": "matematica", "q": "Calculează: 23 × 47 =", "ref": "1081", "ref_num": 1081},
    {"id": 15, "cat": "matematica", "q": "Calculează: 1728 ÷ 12 =", "ref": "144", "ref_num": 144},
    {"id": 16, "cat": "matematica", "q": "Rezolvă pentru x: 5x - 7 = 3x + 9", "ref": "8", "ref_num": 8},
    {"id": 17, "cat": "matematica", "q": "Rezolvă pentru x: 4(x + 3) = 36", "ref": "6", "ref_num": 6},
    {"id": 18, "cat": "matematica", "q": "Un tren merge cu viteză constantă și parcurge 240 km în 3 ore. Câți kilometri parcurge în 5 ore?", "ref": "400", "ref_num": 400},
    {"id": 19, "cat": "matematica", "q": "Un produs costă 250 de lei și se ieftinește cu 20%. Cât costă după reducere (în lei)?", "ref": "200", "ref_num": 200},
    {"id": 20, "cat": "matematica", "q": "Calculează: 3² × 4 - 10 ÷ 2 =", "ref": "31", "ref_num": 31},
]

OUT_DIR = Path("rezultate")
OUT_DIR.mkdir(exist_ok=True)

client = Client(host=OLLAMA_HOST)


def get_model_size_gb(model):
    """Dimensiunea modelului descărcat, citită de la Ollama; altfel valoarea de rezervă."""
    try:
        for m in client.list().models:
            name = getattr(m, "model", None) or m.get("name")
            if name in (model, f"{model}:latest"):
                size = getattr(m, "size", None) or m.get("size")
                return round(size / 1e9, 2)
    except Exception:
        pass
    return MODEL_SIZE_GB.get(model, np.nan)


MODEL_SIZES = {m: get_model_size_gb(m) for m in MODELS}
print("Dimensiuni modele (GB):", MODEL_SIZES)


# -----------------------------
# Normalizare și evaluare
# -----------------------------
def remove_diacritics(text):
    return "".join(
        c for c in unicodedata.normalize("NFD", str(text))
        if unicodedata.category(c) != "Mn"
    )


def normalize_string(text):
    text = remove_diacritics(text).lower()
    text = re.sub(r"[^\w\s+-]", " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


# Marcajul „RĂSPUNS FINAL", tolerant la diacritice, majuscule și markdown (**RĂSPUNS FINAL:**)
FINAL_MARKER_RE = re.compile(r"raspuns\s+final\W*", re.IGNORECASE)


def split_final(text):
    """Împarte răspunsul în (înainte de marcaj, după marcaj).
    Dacă marcajul lipsește, întoarce (text, None). Se folosește ultimul marcaj."""
    original = str(text)
    norm = remove_diacritics(original)
    source = original if len(norm) == len(original) else norm
    matches = list(FINAL_MARKER_RE.finditer(norm))
    if not matches:
        return source, None
    m = matches[-1]
    return source[:m.start()], source[m.end():]


def extract_final_answer(text):
    _, after = split_final(text)
    return (after if after is not None else str(text)).strip()


def token_set(text):
    return set(re.findall(r"\w+", normalize_string(text)))


def jaccard(a, b):
    if not a and not b:
        return 1.0
    if not a or not b:
        return 0.0
    return len(a & b) / len(a | b)


def factual_scores(model_answer, item):
    """exact   = 1 dacă răspunsul final coincide (după normalizare) cu ref sau cu o variantă din alt.
    partial = 1.0 dacă exact; altfel max(Jaccard față de ref/alt) sau 0.5 dacă ref/alt/partial
              apar ca cuvinte întregi în răspuns."""
    final_answer = extract_final_answer(model_answer)
    norm_final = normalize_string(final_answer)

    candidates = [item["ref"]] + list(item.get("alt", []))
    norm_cands = [normalize_string(c) for c in candidates]

    if norm_final in norm_cands:
        return 1, 1.0, final_answer

    partial = max(jaccard(token_set(final_answer), token_set(c)) for c in candidates)

    fragments = norm_cands + [normalize_string(p) for p in item.get("partial", [])]
    padded = f" {norm_final} "
    if any(f and f" {f} " in padded for f in fragments):
        partial = max(partial, 0.5)

    return 0, partial, final_answer


# Numere: 2443, 12,5, 1.5 și cu separatori de mii (2.443 / 1,081).
# Toate răspunsurile de referință sunt întregi, deci un grup de exact 3 cifre după
# punct/virgulă este tratat ca separator de mii.
NUMBER_PATTERN = r"[+-]?(?:\d{1,3}(?:[.,]\d{3})+(?!\d)|\d+(?:[.,]\d+)?)"
FINAL_NUM_RE = re.compile(
    rf"r[ăa]spuns\s+final[^\d+\-]*({NUMBER_PATTERN})",
    re.IGNORECASE
)


def to_float(s):
    s = s.strip()
    if re.fullmatch(r"[+-]?\d{1,3}(?:[.,]\d{3})+", s):
        s = re.sub(r"[.,]", "", s)
    else:
        s = s.replace(",", ".")
    return float(s)


def parse_final_number(text):
    text = str(text)
    matches = list(FINAL_NUM_RE.finditer(text))

    if matches:
        value = matches[-1].group(1)
    else:
        candidates = re.findall(NUMBER_PATTERN, text)
        if not candidates:
            return np.nan
        value = candidates[-1]

    try:
        return to_float(value)
    except ValueError:
        return np.nan


def math_scores(model_answer, ref_num):
    num = parse_final_number(model_answer)
    correct = 0 if np.isnan(num) else int(abs(num - ref_num) <= 1e-6)

    before_final, _ = split_final(model_answer)

    # Euristică: „pași" = text suficient de lung înaintea răspunsului final, cu „=" sau rânduri noi
    has_steps = int(
        len(before_final.strip()) >= 10
        and ("=" in before_final or "\n" in before_final)
    )

    return correct, num, has_steps


# -----------------------------
# Pseudo-perplexitate cu GPT-2
# -----------------------------
print("Se încarcă GPT-2 pentru pseudo-perplexitate...")
print("La prima rulare, GPT-2 va fi descărcat automat de pe Hugging Face.")

REF_LM = "gpt2"
tokenizer = AutoTokenizer.from_pretrained(REF_LM)
ref_model = AutoModelForCausalLM.from_pretrained(REF_LM)
ref_model.eval()


def ref_perplexity(text):
    text = str(text).strip()

    if not text:
        return np.nan

    enc = tokenizer(text, return_tensors="pt")
    input_ids = enc["input_ids"]

    if input_ids.size(1) < 2:
        return np.nan

    max_length = getattr(ref_model.config, "n_positions", 1024)
    stride = min(512, max_length)

    nlls = []
    total_target_tokens = 0

    for i in range(0, input_ids.size(1), stride):
        begin_loc = max(i + stride - max_length, 0)
        end_loc = min(i + stride, input_ids.size(1))
        trg_len = end_loc - i

        input_slice = input_ids[:, begin_loc:end_loc]
        target_ids = input_slice.clone()
        target_ids[:, :-trg_len] = -100

        with torch.no_grad():
            out = ref_model(input_slice, labels=target_ids)

        nlls.append(out.loss * trg_len)
        total_target_tokens += trg_len

        if end_loc == input_ids.size(1):
            break

    if total_target_tokens == 0:
        return np.nan

    ppl = torch.exp(torch.stack(nlls).sum() / total_target_tokens)
    return float(ppl)


# -----------------------------
# Interogarea modelelor Ollama
# -----------------------------
def ask_model(model, prompt):
    start = time.perf_counter()
    first_token_time = None
    parts = []
    last_chunk = None

    stream = client.chat(
        model=model,
        messages=[
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": prompt},
        ],
        stream=True,
        options=GEN_OPTIONS,
    )

    for chunk in stream:
        last_chunk = chunk
        piece = chunk.message.content or ""

        if piece and first_token_time is None:
            first_token_time = time.perf_counter()

        parts.append(piece)

    end = time.perf_counter()
    answer = "".join(parts)

    if first_token_time is None:
        first_token_time = end

    ttft_ms = (first_token_time - start) * 1000.0
    total_ms = (end - start) * 1000.0

    eval_duration_ns = getattr(last_chunk, "eval_duration", 0) or 0
    eval_count = int(getattr(last_chunk, "eval_count", 0) or 0)
    prompt_eval_count = int(getattr(last_chunk, "prompt_eval_count", 0) or 0)
    load_duration_ns = getattr(last_chunk, "load_duration", 0) or 0
    prompt_eval_duration_ns = getattr(last_chunk, "prompt_eval_duration", 0) or 0

    tps = (
        eval_count / (eval_duration_ns / 1e9)
        if eval_duration_ns > 0
        else np.nan
    )

    perf = {
        "ttft_ms": ttft_ms,
        "total_ms": total_ms,
        "tps": tps,
        "gen_tokens": eval_count,
        "prompt_tokens": prompt_eval_count,
        "load_ms": load_duration_ns / 1e6,
        "prompt_eval_ms": prompt_eval_duration_ns / 1e6,
        "eval_ms": eval_duration_ns / 1e6,
    }

    return answer, perf


# -----------------------------
# Benchmark
# -----------------------------
rows = []

for model in MODELS:
    print("\n" + "=" * 70)
    print(f"MODEL: {model}")
    print("=" * 70)

    # Încălzire: încarcă modelul în RAM ca prima întrebare să nu includă timpul de încărcare
    try:
        ask_model(model, "Salut!")
    except Exception as e:
        print(f"   Avertisment (încălzire): {e}")

    for item in DATASET:
        print(f"[{item['id']:02d}/20] {item['q']}")

        try:
            answer, perf = ask_model(model, item["q"])
            ppl = ref_perplexity(answer)

            row = {
                "model": model,
                "model_size_gb": MODEL_SIZES[model],
                "external_api_cost_usd": 0.0,
                "id": item["id"],
                "cat": item["cat"],
                "question": item["q"],
                "reference": item["ref"],
                "answer": answer,
                "final_answer": "",
                "exact": np.nan,
                "partial": np.nan,
                "math_correct": np.nan,
                "has_steps": np.nan,
                "extracted_number": np.nan,
                "ttft_ms": perf["ttft_ms"],
                "total_ms": perf["total_ms"],
                "tps": perf["tps"],
                "gen_tokens": perf["gen_tokens"],
                "prompt_tokens": perf["prompt_tokens"],
                "load_ms": perf["load_ms"],
                "prompt_eval_ms": perf["prompt_eval_ms"],
                "eval_ms": perf["eval_ms"],
                "ref_ppl": ppl,
            }

            if item["cat"] == "matematica":
                correct, extracted, has_steps = math_scores(
                    answer, item["ref_num"]
                )
                row["math_correct"] = correct
                row["has_steps"] = has_steps
                row["extracted_number"] = extracted
                row["final_answer"] = str(extracted)
            else:
                exact, partial, final_answer = factual_scores(
                    answer, item
                )
                row["exact"] = exact
                row["partial"] = partial
                row["final_answer"] = final_answer

            rows.append(row)

            print(
                f"   TTFT={perf['ttft_ms']:.1f} ms | "
                f"TPS={perf['tps']:.2f} | "
                f"Ref-PPL={ppl:.2f}"
            )

        except Exception as e:
            print(f"   EROARE: {e}")
            rows.append({
                "model": model,
                "model_size_gb": MODEL_SIZES[model],
                "external_api_cost_usd": 0.0,
                "id": item["id"],
                "cat": item["cat"],
                "question": item["q"],
                "reference": item["ref"],
                "answer": f"EROARE: {e}",
            })


# -----------------------------
# Salvarea rezultatelor
# -----------------------------
df = pd.DataFrame(rows)

df.to_csv(
    OUT_DIR / "rezultate_detaliate.csv",
    index=False,
    encoding="utf-8-sig"
)

df.to_json(
    OUT_DIR / "rezultate_detaliate.json",
    orient="records",
    indent=2,
    force_ascii=False,
)

agg = (
    df.groupby("model", as_index=False)
    .agg(
        model_size_gb=("model_size_gb", "first"),
        external_api_cost_usd=("external_api_cost_usd", "first"),
        factual_exact=("exact", "mean"),
        factual_partial=("partial", "mean"),
        math_acc=("math_correct", "mean"),
        steps_rate=("has_steps", "mean"),
        ttft_ms=("ttft_ms", "mean"),
        total_ms=("total_ms", "mean"),
        tps=("tps", "mean"),
        ref_ppl=("ref_ppl", "mean"),
        gen_tokens=("gen_tokens", "mean"),
        # Întrebări eșuate: mediile de mai sus le ignoră, deci trebuie raportate separat
        errors=("answer", lambda s: int(s.astype(str).str.startswith("EROARE").sum())),
    )
)

agg.to_csv(
    OUT_DIR / "rezultate_agregate.csv",
    index=False,
    encoding="utf-8-sig"
)

agg.to_json(
    OUT_DIR / "rezultate_agregate.json",
    orient="records",
    indent=2,
    force_ascii=False,
)

print("\nREZULTATE AGREGATE")
print(agg.to_string(index=False))


# -----------------------------
# Grafice
# -----------------------------
def save_bar(column, title, ylabel, filename):
    ax = agg.plot(
        kind="bar",
        x="model",
        y=column,
        legend=False,
        figsize=(8, 5)
    )
    ax.set_title(title)
    ax.set_xlabel("Model")
    ax.set_ylabel(ylabel)
    plt.xticks(rotation=15)
    plt.tight_layout()
    plt.savefig(OUT_DIR / filename, dpi=160)
    plt.close()


save_bar(
    "factual_exact",
    "Acuratețe factuală exactă",
    "Scor (0-1)",
    "01_factual_exact.png"
)

save_bar(
    "factual_partial",
    "Acuratețe factuală parțială",
    "Scor (0-1)",
    "02_factual_partial.png"
)

save_bar(
    "math_acc",
    "Acuratețe la matematică",
    "Scor (0-1)",
    "03_math_acc.png"
)

save_bar(
    "tps",
    "Viteză de generare",
    "Tokeni/secundă",
    "04_tps.png"
)

save_bar(
    "ttft_ms",
    "Time-To-First-Token",
    "Milisecunde",
    "05_ttft.png"
)

save_bar(
    "ref_ppl",
    "Pseudo-perplexitate GPT-2",
    "Ref-PPL (mai mic = mai bine)",
    "06_ref_ppl.png"
)

print("\nGATA.")
print(f"Rezultatele au fost salvate în: {OUT_DIR.resolve()}")
print("Fișiere principale:")
print(" - rezultate_detaliate.csv")
print(" - rezultate_agregate.csv")
print(" - rezultate_detaliate.json")
print(" - rezultate_agregate.json")
print(" - 6 grafice PNG")