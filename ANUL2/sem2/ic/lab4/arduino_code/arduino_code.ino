#include <LiquidCrystal.h>

/* Initializarea LCD-ului cu pinii corespunzatori conectati la microcontroller */
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int charactersDisplayed = 0; /* folosita ulterior pentru a determina cate caractere sunt afisate */
bool firstRowCompleted = false; /* folosita pentru a determina pe al catalea rand se scrie */

void setup() 
{
  /* LCD 16x2 */
  lcd.begin(16, 2);
  /* Terminal */
  Serial.begin(9600);
}

void loop() 
{
  while (Serial.available() == 0) 
  {
    /* permite programului sa astepte date de la terminal */
  }
  
  String data = "";
  while (Serial.available() > 0) 
  {
    /* Daca sunt date disponibile, umple buffer-ul data */
    char receivedChar = Serial.read();
    data += receivedChar;
  }
  
  if (charactersDisplayed + data.length() > 16) 
  {
    /* Primul rand este plin, va incepe pe al doilea */
    if (false == firstRowCompleted)
    {
      firstRowCompleted = true;
      lcd.setCursor(0, 1);
    }

    /* Al doilea rand este plin, va reseta tot */
    if (charactersDisplayed + data.length() > 32)
    {
      lcd.clear();
      charactersDisplayed = 0;
      firstRowCompleted = false;
    }
  }
  
  lcd.print(data);
  Serial.print(data);
  
  /* Actualizeaza nr total de caractere afisate */
  charactersDisplayed += data.length();
}
