/* Codul board-ului Master */
#include <LiquidCrystal.h>

#define NUM_OF_BUTTONS 3

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int dataBuffer[NUM_OF_BUTTONS];
int pins[NUM_OF_BUTTONS];

void setup() 
{
  /* Setarea pinilor pentru buton */
  pins[0] = 8;
  pins[1] = 7;
  pins[2] = 6; 
  pinMode(pins[0], INPUT);
  pinMode(pins[1], INPUT);
  pinMode(pins[2], INPUT);

  /* Initializarea LCD-ului */
  lcd.begin(16, 2);

  /* Initializarea comunicarii prin UART */
  Serial.begin(9600);
}

void loop() 
{
  /* Pentru fiecare buton */
  for(int iter = 0u; iter < NUM_OF_BUTTONS; iter++)
  {
    /* Verifica daca a fost apasat */
    if (digitalRead(pins[iter]) == HIGH)
    {
      /* Trimite semnal board-ului slave */
      Serial.write(iter);

      /* Verifica daca a primit raspuns */
      if (Serial.available() > 0) 
      {
        lcd.clear(); /* Curata ecranul */

        int value = Serial.read(); /* Citeste valoarea raw */
        float convertedValue = (value * 5.0) / 1023; /* Formula de conversie a semnalului voltaj */

        /* Afisarea datelor primite */
        lcd.setCursor(0, 0);
        lcd.print("Voltaj buton ");
        lcd.print(iter+1);
        lcd.setCursor(0, 1);
        lcd.print(convertedValue);
      }
    }
  }
  
}
