#define BLYNK_TEMPLATE_ID "TMPL6YHWG7_cW"
#define BLYNK_TEMPLATE_NAME "Gomulu Proje"
#define BLYNK_AUTH_TOKEN "960PVewOVWF4fo40GuuDramJwW-LL28r"

#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"     

#define DHTPIN 2    
#define DHTTYPE DHT11   
#define BLYNK_PRINT Serial 
#define LED_NEM D1
#define LED_SICAKLIK D2


char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Sami's Galaxy A50"; 
char pass[] = "birdensekizekadar"; 

BlynkTimer timer; 
DHT dht(DHTPIN, DHTTYPE); 


void sendData()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();  

  
   if (isnan(h) || isnan(t)) {
    Serial.println("DHT Sensor okuma hatasi!");
    return;
  }
  
  Blynk.virtualWrite(V1, h); 
  Blynk.virtualWrite(V2, t);

  if(t<26.0 || t>30.0){
    digitalWrite(LED_SICAKLIK, HIGH);
    Blynk.virtualWrite(V4, 255);
delay(1000);
  }else{
    digitalWrite(LED_SICAKLIK, LOW);
    Blynk.virtualWrite(V4, 0);
    delay(1000);
  }
  if(h<60.0 || h>80.0){
    digitalWrite(LED_NEM, HIGH);
    Blynk.virtualWrite(V3, 255);
delay(1000);
  }else{
    digitalWrite(LED_NEM, LOW);
    Blynk.virtualWrite(V3, 0);
    delay(1000);
  }
}

void setup()
{
pinMode(LED_SICAKLIK, OUTPUT);
pinMode(LED_NEM, OUTPUT);

  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);

  
  timer.setInterval(1000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}
