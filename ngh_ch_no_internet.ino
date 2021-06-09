// MiniCar2020
// ESP8266 GPIO 4, 5, 12, 13, 14, 16
// ESP32 GPIO 6, 7, 8, 9, 10, 11, 13, 14, 16->33, 37, 38

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library         
#else
#include <WiFi.h>      //ESP32 Core WiFi Library    
#endif
#include <Servo.h>  

Servo ServoGa,ServoLai;
//Change wifi
const char* ssid = "<Your WiFi SSID";
const char* password = "Password of WiFi";   

int goc=0,input=0;
int LedPin = 27; // esp8266 12 D6 & esp32 27

WiFiServer server(80);

void setup()
  {
  ServoGa.attach(13); // D7 on ESP8266
  ServoLai.attach(14); // D5 on ESP8266
  pinMode(LedPin, OUTPUT); // ESP8266 G2 ESP32 G1
  
  Serial.begin(115200);
  Serial.println();
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    Serial.print("MAC:");
    Serial.println(WiFi.macAddress());
    digitalWrite(LedPin, LOW);
  }
  Serial.println();
  Serial.print("IP: ");
  server.begin();
  Serial.println(WiFi.localIP());
  Serial.print("MAC:");
  Serial.println(WiFi.macAddress());
  digitalWrite(LedPin, HIGH); 
  if (WiFi.status() != WL_CONNECTED)
    {
      ESP.restart(); 
    }
  }
void loop() 
{ 
    if (WiFi.status() != WL_CONNECTED)
    {
      ESP.restart();
    }
  while (WiFi.status() == WL_CONNECTED)    // Restart ESP32 if WiFi connection lost
  {
      WiFiClient client = server.available();

      while(client.connected())
      {
        while(client.available())
        { 
            input = client.read();
            if(input == 118)
            {
              ServoGa.write(goc);
              Serial.println();
              Serial.print(goc);
              goc = 0;
            }
            if(input == 114)
            {
              ServoLai.write(goc);
              Serial.println();
              Serial.print(goc);
              goc = 0;
            }
            if(input != 118 && input != 114)
            {
              goc = (input - 48) + goc*10;
              input = 0;
            }
            //delay(10);
        }
      }
    }


}
