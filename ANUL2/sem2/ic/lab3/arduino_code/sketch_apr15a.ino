#include <Keypad.h>

#define ROWS  4
#define COLS  4

/* Structura keypad-ului 4x4 */
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};

/* Maparea la pinii arduino */
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Serial.println("Serba Cristina CR-221FR");
}

void loop() 
{
  char key = keypad.getKey(); /* Primeste date de la tastatura */
  if (key != NO_KEY) 
  { 
    /* Verifica daca datele primite nu sunt goale */
    Serial.print("A fost apasata tasta: ");
    Serial.println(key); 
  }
}
