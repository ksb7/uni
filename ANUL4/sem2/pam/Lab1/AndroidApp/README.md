# MyApp – Android Project

## 📋 Cerințe îndeplinite

### UI Elements
| Element | ID | Descriere |
|---|---|---|
| EditText (TextBox) | `editTextSearch` | Input pentru cuvânt cheie |
| Button 1 | `btnNotification` | Declanșează notificare după 10s |
| Button 2 | `btnSearch` | Caută în Google browserul intern |
| Button 3 | `btnAddItem` | Adaugă element în listă |
| Button 4 | `btnClearList` | Golește lista |
| ListView | `listViewItems` | Listă cu obiecte custom |

### Funcționalități

#### 1. 🔔 Push Notification (Button 1)
- La apăsare, după exact **10 secunde** apare o notificare push pe ecran
- Folosește `Handler.postDelayed()` cu 10.000ms
- Notificarea e tip `BigTextStyle` cu titlu și conținut extins
- Pe Android 13+ se cere permisiunea `POST_NOTIFICATIONS`

#### 2. 🌐 Căutare Google (Button 2)
- Preia textul din EditText
- Deschide **browserul intern** al dispozitivului cu URL-ul:  
  `https://www.google.com/search?q=<cuvant_cheie>`
- Folosește `Intent.ACTION_VIEW` cu URI

#### 3. 📋 Custom Object List
Fiecare element din listă conține:
- **Head Title** (`tvHeadTitle`) – numele general al obiectului, bold, albastru
- **Content Option** (`tvContentOption`) – conținut detaliat al elementului
- **Badge colorat** cu numărul indexului (culori ciclice)
- Layout tip **CardView** cu umbră și colțuri rotunde

#### 4. ➕ Adăugare element (Button 3)
- Adaugă un element nou cu titlul din TextBox (sau auto-generat dacă e gol)

#### 5. 🗑️ Golire listă (Button 4)
- Curăță toate elementele din ListView

---

## 🛠️ Cum deschizi proiectul în Android Studio

1. Deschide **Android Studio**
2. `File > Open` → selectează folderul `AndroidApp`
3. Așteaptă sincronizarea Gradle
4. Selectează un emulator sau dispozitiv fizic
5. Apasă **Run ▶**

## 📁 Structura proiectului

```
AndroidApp/
├── app/src/main/
│   ├── AndroidManifest.xml          ← permisiuni + activitate
│   ├── java/com/example/myapp/
│   │   ├── MainActivity.kt          ← logica principală
│   │   ├── MyItem.kt                ← data class pentru obiecte
│   │   └── MyItemAdapter.kt         ← adapter custom pentru ListView
│   └── res/
│       ├── layout/
│       │   ├── activity_main.xml    ← UI principal
│       │   └── list_item.xml        ← layout element din listă
│       ├── drawable/
│       │   ├── circle_badge.xml     ← badge circular colorat
│       │   └── edittext_background.xml
│       └── values/
│           ├── strings.xml
│           └── themes.xml
├── build.gradle
└── settings.gradle
```

## 📦 Dependențe (build.gradle)
- `androidx.core:core-ktx:1.12.0`
- `androidx.appcompat:appcompat:1.6.1`
- `com.google.android.material:material:1.11.0`
- `androidx.cardview:cardview:1.0.0`

**minSdk: 24 | targetSdk: 34 | Kotlin 1.9**
