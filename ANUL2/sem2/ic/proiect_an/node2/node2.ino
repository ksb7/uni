#include <painlessMesh.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Arduino_JSON.h>

#define   MQ2_PIN             7u
#define   RELEPIN             0u
#define   MESH_PREFIX         "MYMESH"
#define   MESH_PASSWORD       "password"
#define   MESH_PORT           5555
#define   NODE_NUMBER         2u
#define   GAS_LOWER_THRESHOLD 200u
#define   GAS_UPPER_THRESHOLD 800u

LiquidCrystal lcd(6, 5, 4, 3, 2, 1);
Scheduler userScheduler; 
painlessMesh  mesh;
                                                                                                                                            
void sendMessage(); 
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void validateData(int gasLevel)
{
  if ((gasLevel < GAS_LOWER_THRESHOLD) || (gasLevel > GAS_UPPER_THRESHOLD))
  {
    analogWrite(RELEPIN, HIGH);
  }
  else
  {
    analogWrite(RELEPIN, LOW);
  }
}

String getData() 
{
  JSONVar jsonReadings;
  String data;
  jsonReadings["node"] = NODE_NUMBER;
  jsonReadings["gas"] = analogRead(MQ2_PIN);
  validateData(jsonReadings["gas"]);
  data = JSON.stringify(jsonReadings);
  return data;
}
void sendMessage () 
{
  String msg = getData();
  mesh.sendBroadcast(msg);
}

void receivedCallback(uint32_t source, String &msg) 
{
  JSONVar data = JSON.parse(msg.c_str());
  int nodeType = data["node"]; 
  
  if (1u == nodeType) 
  {
    double temp = data["temp"];
    double hum = data["hum"];
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(hum);
  } 
  else if (2u == nodeType) 
  {
    double gasLevel = data["gas"];
    
    lcd.clear();
    lcd.print("Gas Level:");
    lcd.print(gasLevel);
  } 
  else 
  {
    lcd.clear();
    lcd.print("Invalid data received");
  }
}

void newConnectionCallback(uint32_t nodeId) 
{
  lcd.clear();
  lcd.print("New nodeId = ");
  lcd.print(nodeId);
}

void changedConnectionCallback() 
{
  lcd.clear();
  lcd.print("Changed connections");
}

void nodeTimeAdjustedCallback(int32_t offset) 
{
  lcd.clear();
  lcd.print("Adjusted time, offset = ");
  lcd.print(offset);
}

void setup() 
{
  pinMode(MQ2_PIN, INPUT);
  lcd.begin(16, 2);

  mesh.setDebugMsgTypes( ERROR | STARTUP ); 

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();

  lcd.clear();
}

void loop() 
{
  mesh.update();
}