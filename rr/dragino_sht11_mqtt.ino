#include <Process.h>
#include "MQTTclient.h"
#include "DHT.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SHT1x.h>
#define dataPin  2
#define clockPin 3
SHT1x sht1x(dataPin, clockPin);


#define ONE_WIRE_BUS_PIN A3
float  tempC2 = 0;
float  tempC3 = 0;
unsigned long time;

OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);


#define MQTT_HOST "190.97.168.236" 
#define DHTPIN A0     
//#define DHTPIN2 A1

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
//DHT dht2(DHTPIN2, DHTTYPE);


char message_buff[100];
char message_buff2[100];
char message[256];
String id_sensor = "prueba12";


float t2;



void setup() {
 
  Serial.begin(9600);
  Bridge.begin();
  mqtt.begin(MQTT_HOST, 1883);
  dht.begin();
  sensors.begin(); 
  //sensors.setResolution(probe01, 10);
  
  mqtt.subscribe("rr/temp", someEvent);


}


void loop() {
 delay(2000);
  float h = sht1x.readHumidity() * 100;
  float t = sht1x.readTemperatureC() * 100;

 sensors.requestTemperatures();
 
 tempC2 = sensors.getTempCByIndex(0),4;
 tempC3 = tempC2 * 100;
 
 //tempC2 = sensors.getTempC(probe01);
 
 if (isnan(t) || isnan(h)) {
    Serial.println("Failed to from DHT");
    mqtt.publish("error/temp/SHT","error de lectura NAN SHT" );
  }
  
  else if (t == 0.00 && h == 0.00)
  
  {
    Serial.println("Failed to from DHT");
    mqtt.publish("error/temp/SHT","error de lectura SHT" );
  }
  
    else if (tempC2 == -127.00)
  
  {
    Serial.println("Failed to from DHT");
    mqtt.publish("error/temp/ds18b20","error de lectura ds18b20 -127.00" );
  }
  
  
  else {
 
 
   if (millis() > (time + 15000)) {
       time = millis();
  
 String pubString = "" + String(t) + "," + String(tempC3) + "," + String(h) + "," + id_sensor + "";
   pubString.toCharArray(message_buff, pubString.length()+1);
   mqtt.publish("rr/temp",message_buff );

   }
   else{
   
  mqtt.monitor();
   }
  }

}

void someEvent(const String& topic, const String& subtopic, const String& message) {

}
