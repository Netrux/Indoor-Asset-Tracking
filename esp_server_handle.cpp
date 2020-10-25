#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


//RH_ASK rf_driver;

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
const char* ssid = "DRONE_NETWORK";  // Enter SSID here
const char* password = "aeromodelling";  //Enter Password here

ESP8266WebServer server(80);

// DHT Sensor
//uint8_t DHTPin = D8; 
               
// Initialize DHT sensor.
//DHT dht(DHTPin, DHTTYPE);                

int device1;
int device2;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  
           

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  //rf_driver.init();

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {

  device1 = digitalRead(D0); // Gets the values of the temperature
  device2 = digitalRead(D1);
  Serial.println(device1);
  Serial.println(device2); 
  server.send(200, "text/html", SendHTML(device1,device2)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(int Temperaturestat,int Humiditystat){
  String f1;
  String f2;
  if(Temperaturestat == 1)
    f1 = "Found";
    
  if (Temperaturestat != 1) 
    f1 = "Not Found";

  if(Humiditystat == 1)
    f2 = "Found";
  if(Humiditystat != 1)
    f2 = "Not Found";      
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>IoT DIY Asset Tracking</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>IoT DIY Asset Tracking</h1>\n";
  
  ptr +="<p>Device 1: ";
  ptr +=(String)f1;
  ptr +="</p>";
  ptr +="<p>Device 2: ";
  ptr +=(String)f2;
  ptr +="</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
