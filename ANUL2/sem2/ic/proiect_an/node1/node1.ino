#include <painlessMesh.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Arduino_JSON.h>

#define   DHTPIN                7u
#define   DHTTYPE               DHT22
#define   RELEPIN               0u
#define   MESH_PREFIX           "MYMESH"
#define   MESH_PASSWORD         "password"
#define   MESH_PORT             5555
#define   NODE_NUMBER           2u
#define   TEMP_LOWER_THRESHOLD  0u
#define   TEMP_UPPER_THRESHOLD  30u
#define   HUM_LOWER_THRESHOLD   20u
#define   HUM_UPPER_THRESHOLD   80u

LiquidCrystal lcd(6, 5, 4, 3, 2, 1);
Scheduler userScheduler; 
painlessMesh  mesh;
DHT dht(DHTPIN, DHTTYPE);
                                                                                                                                            
void sendMessage(); 
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void validateData(double temperature, double humidity)
{
  if ((temperature < TEMP_LOWER_THRESHOLD) || (temperature > TEMP_UPPER_THRESHOLD))
  {
    analogWrite(RELEPIN, HIGH);
  }
  else
  {
    analogWrite(RELEPIN, LOW);
  }

  if ((humidity < HUM_LOWER_THRESHOLD) || (humidity > HUM_UPPER_THRESHOLD))
  {
    analogWrite(RELEPIN, HIGH);
  }
  else
  {
    analogWrite(RELEPIN, LOW);
  }
}

String getData () 
{
  JSONVar jsonReadings;
  String data;

  jsonReadings["node"] = NODE_NUMBER;
  jsonReadings["temp"] = dht.readTemperature();
  jsonReadings["hum"] = dht.readHumidity();

  validateData(jsonReadings["temp"], jsonReadings["hum"]);

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
  String nodeType = data["node"]; 
  
  if (nodeType == "temperature_humidity") 
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
  else if (nodeType == "gas_level") 
  {
    double gasLevel = data["gas_level"];
    
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
  lcd.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() 
{
  lcd.clear();
  lcd.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) 
{
  lcd.clear();
  lcd.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() 
{
  lcd.begin(16, 2);
  dht.begin();

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