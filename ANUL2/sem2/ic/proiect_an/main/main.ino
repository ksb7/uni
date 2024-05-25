#include <LiquidCrystal.h>
#include <painlessMesh.h>
#include <Arduino_JSON.h>

#define   SSID            "Ailin"
#define   PASSWORD        "22042016"
#define   MESH_PREFIX     "MYMESH"
#define   MESH_PASSWORD   "password"
#define   MESH_PORT       5555
#define   NODE_NUMBER     0u

Scheduler userScheduler; 
painlessMesh  mesh;
WiFiServer server(80);
LiquidCrystal lcd(6, 5, 4, 3, 2, 1);

void sendMessage(void);
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

double temp; 
double hum;
double gasLevel;

void sendMessage(void)
{
  /* avoid compiler warnings */
}

void receivedCallback(uint32_t source, String &msg) 
{
  JSONVar data = JSON.parse(msg.c_str());
  int nodeType = data["node"]; 
  
  if (1u == nodeType) 
  {
    temp = data["temp"];
    hum = data["hum"];
    
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
    gasLevel = data["gas"];
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Level: ");
    lcd.print(gasLevel);
  } 
  else 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid data received");
  }
}
void newConnectionCallback(uint32_t nodeId) 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New nodeId = ");
  lcd.print(nodeId);
}

void changedConnectionCallback() 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Adjusted time");
}

void setup() 
{
  lcd.begin(16, 2);
  
  mesh.setDebugMsgTypes( ERROR | STARTUP ); 

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
    
  connectToWiFi();

  server.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HTTP server started");
}

void loop() 
{
  WiFiClient client = server.available();
  if (client) 
  {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print("<!DOCTYPE html><html><head><title>Monitorizarea aerului</title></head><body>");
    client.print("<h1>Temperatura: ");
    client.print(temp);
    client.print(" °C</h1>");
    client.print("<h1>Umiditatea: ");
    client.print(hum);
    client.print(" %</h1>");
    client.print("<h1>Nivelul de gaze: ");
    client.print(gasLevel);
    client.print("</h1");
    client.print("</body></html>");
    delay(100);
    client.stop();
  }
  mesh.update();
}

void connectToWiFi() 
{
  lcd.clear();
  lcd.print("Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    lcd.clear();
    lcd.print("Connecting...");
  }
  lcd.clear();
  lcd.print("Connected to WiFi");
}
