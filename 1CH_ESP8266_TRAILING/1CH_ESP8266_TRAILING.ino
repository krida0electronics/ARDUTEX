/*
 *  ARDUTEX WIRELESS ESP8266 MOSFET TRAILING EDGE AC DIMMER
 *  WORKING MAIN VOLTAGE 100...240VAC
 *  FREQUENCY 50HZ / 60HZ
 *  MAX OUTPUT POWER 200W
 *  
 *  BEST DIMMER SOLUTION FOR DIMMABLE LED BULBS!
 *  
 *  WIFI MODULE - NODEMCU, WEMOS, ESP8266
 *  
 *  DEVELOPED BY KRIDA ELECTRONICS - krida.electronics@gmail.com
 */

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#define FREQ 500  // 500 for 50HZ, 415 for 60HZ
#define MAX 254

#define GATE 5      // pin for GATE    5
#define ZRC 14      // pin for ZeroCross 14

unsigned int buf_dimm, imp_delay, value1;

unsigned char work;

// Set web server port number to 80
AsyncWebServer server(80);

// Replace with your network credentials
const char* ssid = "STYLUS_ID";
const char* password = "marlboro1986";



String processor(const String& var)
{
  if(var == "PAGE_NAME")
    return F("TRAILING EDGE DIMMER ESP8266");
  return String();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void ICACHE_RAM_ATTR onTimerISR(){

digitalWrite(GATE, LOW);
timer1_disable();
}

void ZerocrossInterrupt() {

if (work || buf_dimm>=3)
 { 
  if (value1>=buf_dimm) {buf_dimm++;}     // soft function dimm up. if don't needed, it can be removed 
  if (value1<=buf_dimm) {buf_dimm--; }    // soft function dimm down. if don't needed, it can be removed. 
                                          // then, here write string buf_dimm=value1;
  imp_delay = ((buf_dimm*FREQ)/255)*100;  
  digitalWrite(GATE, HIGH);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  timer1_write(imp_delay);
 }
  else {digitalWrite(GATE, LOW); value1=0;}
}


void setup() {

 pinMode(ZRC, INPUT_PULLUP);     // zero-cross interrupt on digital pin 13
 pinMode(GATE, OUTPUT);          // Gate signal on digital pin 12
 attachInterrupt(digitalPinToInterrupt(ZRC), ZerocrossInterrupt, FALLING);

 timer1_attachInterrupt(onTimerISR);
 timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  
  // Start filing subsystem
  if (SPIFFS.begin()) {
      Serial.println("SPIFFS Active");
      Serial.println();
  } else {
      Serial.println("Unable to activate SPIFFS");
  }
  
  // Connect to Wi-Fi network with SSID and password
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
  });

  // Route for program 1
  server.on("/program1", HTTP_GET, [](AsyncWebServerRequest *request){  
    int paramsNr = request->params(); //Get request params
 
    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);

        if(p->name() == "slider1") {
          
          value1=p->value().toInt();
          if (value1>MAX) {value1=MAX;}
          if (value1==0) {work=0;}
           else {work=1;}
          
        }
    }
    request->send(SPIFFS, "/program1.html", "text/html", false); //Send in response html to client
  });


  server.onNotFound(notFound);
  
  server.begin();
}



void loop(){

}
