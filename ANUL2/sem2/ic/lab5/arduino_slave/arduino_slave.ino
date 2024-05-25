/* Codul board-ului Slave */
#define NUM_OF_PINS 3

int pins[NUM_OF_PINS];

void setup() 
{
  pins[0] = A0;
  pins[1] = A1;
  pins[2] = A2;
  Serial.begin(9600);
}

void loop() 
{
  /* Verifica daca a primit semnal de la master */
  if (Serial.available() > 0) 
  {
    /* In dependenta de indicele primit */
    int cod = Serial.read();
    
    /* Citeste valoarea de la potentiometrul respectiv */
    int value = analogRead(pins[cod]);
    
    /* Trimite datele citite inapoi la master */
    Serial.write(value);
  }
}
