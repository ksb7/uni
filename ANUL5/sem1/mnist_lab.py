"""
Laborator: Clasificarea imaginilor cu TensorFlow și Keras
Set de date: MNIST (cifre scrise de mână, 0-9)

Structura urmează activitățile din enunț:
  1. Configurarea mediului de lucru
  2. Încărcarea și preprocesarea datelor
  3. Construirea modelului
  4. Compilarea modelului
  5. Antrenarea modelului
  6. Evaluarea modelului
  7. Interpretarea rezultatelor
"""

import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

print("Versiune TensorFlow:", tf.__version__)
print("Versiune Keras:", keras.__version__)

# ============================================================
# 1. Configurarea mediului de lucru
# ============================================================
# (Doar informativ: confirmă că TensorFlow/Keras sunt instalate și funcționale.
#  În Colab, aceste biblioteci sunt deja preinstalate.)

SEED = 42
np.random.seed(SEED)
tf.random.set_seed(SEED)


# ============================================================
# 2. Încărcarea și preprocesarea datelor
# ============================================================
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

print(f"\nSet de antrenament: {x_train.shape[0]} imagini de {x_train.shape[1]}x{x_train.shape[2]} pixeli")
print(f"Set de test: {x_test.shape[0]} imagini")
print(f"Etichete posibile: {sorted(set(y_train.tolist()))}")

# Normalizarea valorilor pixelilor din [0, 255] în [0, 1].
# Rețelele neuronale converg mai rapid și mai stabil cu intrări mici, apropiate de 0.
x_train = x_train.astype("float32") / 255.0
x_test = x_test.astype("float32") / 255.0

# Etichetele rămân numere întregi (0-9), NU one-hot encoding, pentru că modelul
# este compilat cu sparse_categorical_crossentropy (vezi pasul 4), care acceptă
# direct etichete întregi. Dacă am fi folosit categorical_crossentropy, ar fi
# fost nevoie de: y_train = keras.utils.to_categorical(y_train, num_classes=10)

# Câteva exemple, pentru verificare vizuală
fig, axes = plt.subplots(1, 6, figsize=(10, 2))
for i, ax in enumerate(axes):
    ax.imshow(x_train[i], cmap="gray")
    ax.set_title(str(y_train[i]))
    ax.axis("off")
plt.suptitle("Exemple din setul de antrenament MNIST")
plt.tight_layout()
plt.savefig("exemple_mnist.png", dpi=150)
plt.close()
print("\nSalvat: exemple_mnist.png (6 cifre din setul de antrenament)")


# ============================================================
# 3. Construirea modelului
# ============================================================
# Model simplu, complet conectat (Dense): imaginea 28x28 este "aplatizată"
# într-un vector de 784 de valori, apoi trece prin două straturi ascunse.
model = keras.Sequential([
    layers.Input(shape=(28, 28)),
    layers.Flatten(name="aplatizare_28x28_in_784"),
    layers.Dense(128, activation="relu", name="strat_ascuns_1"),
    layers.Dropout(0.2, name="dropout_regularizare"),
    layers.Dense(64, activation="relu", name="strat_ascuns_2"),
    layers.Dense(10, activation="softmax", name="strat_iesire_10_clase"),
])

model.summary()


# ============================================================
# 4. Compilarea modelului
# ============================================================
model.compile(
    optimizer="adam",
    loss="sparse_categorical_crossentropy",   # etichete întregi, nu one-hot
    metrics=["accuracy"],
)


# ============================================================
# 5. Antrenarea modelului
# ============================================================
EPOCHS = 10
BATCH_SIZE = 32

# validation_split rezervă 10% din datele de antrenament pentru a urmări
# supraantrenarea în timpul antrenării, fără să atingem setul de test.
history = model.fit(
    x_train, y_train,
    epochs=EPOCHS,
    batch_size=BATCH_SIZE,
    validation_split=0.1,
    verbose=2,
)


# ============================================================
# 6. Evaluarea modelului
# ============================================================
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
print(f"\nRezultate pe setul de TEST:")
print(f"  Pierdere (loss): {test_loss:.4f}")
print(f"  Acuratețe (accuracy): {test_acc:.4f} ({test_acc*100:.2f}%)")

# Grafice: evoluția acurateței și a pierderii pe parcursul antrenării
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(11, 4))

ax1.plot(history.history["accuracy"], label="antrenament")
ax1.plot(history.history["val_accuracy"], label="validare")
ax1.set_title("Acuratețe pe parcursul antrenării")
ax1.set_xlabel("Epocă")
ax1.set_ylabel("Acuratețe")
ax1.legend()

ax2.plot(history.history["loss"], label="antrenament")
ax2.plot(history.history["val_loss"], label="validare")
ax2.set_title("Pierdere pe parcursul antrenării")
ax2.set_xlabel("Epocă")
ax2.set_ylabel("Pierdere (loss)")
ax2.legend()

plt.tight_layout()
plt.savefig("evolutie_antrenare.png", dpi=150)
plt.close()
print("Salvat: evolutie_antrenare.png (curbele de acuratețe și pierdere)")

# Matrice de confuzie, utilă pentru a vedea ce cifre confundă modelul
predictii = np.argmax(model.predict(x_test, verbose=0), axis=1)
matrice_confuzie = tf.math.confusion_matrix(y_test, predictii).numpy()

plt.figure(figsize=(6, 5))
plt.imshow(matrice_confuzie, cmap="Blues")
plt.title("Matrice de confuzie (set de test)")
plt.xlabel("Etichetă prezisă")
plt.ylabel("Etichetă reală")
plt.colorbar()
for i in range(10):
    for j in range(10):
        culoare = "white" if matrice_confuzie[i, j] > matrice_confuzie.max() / 2 else "black"
        plt.text(j, i, str(matrice_confuzie[i, j]), ha="center", va="center", color=culoare, fontsize=8)
plt.xticks(range(10))
plt.yticks(range(10))
plt.tight_layout()
plt.savefig("matrice_confuzie.png", dpi=150)
plt.close()
print("Salvat: matrice_confuzie.png")


# ============================================================
# 7. Interpretarea rezultatelor
# ============================================================
acc_antrenare_finala = history.history["accuracy"][-1]
acc_validare_finala = history.history["val_accuracy"][-1]
diferenta = acc_antrenare_finala - acc_validare_finala

print("\n" + "=" * 60)
print("INTERPRETARE")
print("=" * 60)
print(f"Acuratețe finală antrenament: {acc_antrenare_finala:.4f}")
print(f"Acuratețe finală validare:    {acc_validare_finala:.4f}")
print(f"Diferență (antrenament - validare): {diferenta:.4f}")

if diferenta > 0.05:
    print(
        "\nDiferența este mare (> 5 puncte procentuale): posibilă SUPRAANTRENARE "
        "(overfitting). Modelul memorează datele de antrenament mai bine decât "
        "generalizează. Verificați graficul 'evolutie_antrenare.png': dacă pierderea "
        "de validare crește în timp ce cea de antrenament scade, este un semn clar."
    )
elif acc_antrenare_finala < 0.9:
    print(
        "\nAcuratețea de antrenament este relativ scăzută: posibilă SUBANTRENARE "
        "(underfitting). Modelul nu are suficientă capacitate sau nu s-a antrenat "
        "suficient de mult pentru a învăța bine datele."
    )
else:
    print(
        "\nDiferența dintre antrenament și validare este mică, iar acuratețea de "
        "antrenament este ridicată: modelul pare bine calibrat pentru acest set de date."
    )

print(
    "\nÎmbunătățiri posibile de discutat în raport:\n"
    "  - Arhitectură: straturi convoluționale (Conv2D + MaxPooling) în loc de\n"
    "    straturi Dense, care exploatează structura spațială a imaginii și, de\n"
    "    obicei, ajung la acuratețe mai mare pe MNIST.\n"
    "  - Hiperparametri: alt număr de epoci, alt batch_size, alt learning rate\n"
    "    pentru optimizer (ex. keras.optimizers.Adam(learning_rate=0.0005)).\n"
    "  - Regularizare: mai mult/mai puțin Dropout, sau L2, dacă apare overfitting.\n"
    "  - Augmentare de date: rotații/translații mici ale cifrelor, pentru un set\n"
    "    de antrenament mai variat.\n"
    "  - Early stopping: oprirea antrenării când acuratețea de validare nu mai\n"
    "    crește, pentru a evita overfitting-ul (keras.callbacks.EarlyStopping)."
)
