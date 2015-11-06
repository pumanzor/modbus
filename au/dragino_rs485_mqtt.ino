#include "RS485_protocol.h"
#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <Process.h>
#include "MQTTclient.h"

const byte ENABLE_PIN = 4;
const byte LED_PIN = 3;

#define MQTT_HOST "190.97.168.236" 
char message_buff[100];

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
long values []= {0,0,0,0};

SoftwareSerial rs485 (9, 10);  // receive pin, transmit pin

// callback routines
  
void fWrite (const byte what)
  {
  rs485.write (what);  
  }
  
int fAvailable ()
  {
  return rs485.available ();  
  }

int fRead ()
  {
  return rs485.read ();  
  }

void setup()
{ Serial.begin(9600);
  Bridge.begin();
  mqtt.begin(MQTT_HOST, 1883);
  rs485.begin (38400);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
 pinMode (LED_PIN, OUTPUT);  // built-in LED
 mqtt.publish("test/uno", "OK dragino");
 mqtt.subscribe("rr/temp", someEvent);
}  // end of setup
  
byte old_level = 0;

void loop()
{ mqtt.monitor();
/*
  long level = random(20,32); 
  
  if (level == old_level)
    return;
      
  
  byte msg [] = { 
     1,    // device 1
     2,    // turn light on
     level // to what level
  };

  // send to slave  
  digitalWrite (ENABLE_PIN, HIGH);  // enable sending
  sendMsg (fWrite, msg, sizeof msg);
  digitalWrite (ENABLE_PIN, LOW);  // disable sending

  // receive response  
  byte buf [10];
  byte received = recvMsg (fAvailable, fRead, buf, sizeof buf);
  
  digitalWrite (LED_PIN, received == 0);  // turn on LED if error    
  
  // only send once per successful change
  if (received)
    old_level = level;*/

}  // end of loop


void someEvent(const String& topic, const String& subtopic, const String& message) {
  
int i = 0;
  for(i=0; i<32; i++) {
    message_buff[i] = message[i];
  }
  message_buff[i] = '\0';
  
  
  String pubString = "" + String(message) + "";
   pubString.toCharArray(message_buff, pubString.length()+1);
  
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: "); 
  Serial.println(message); 
  
  //int integer = 25;
 // String integer = hola;

parse();

//String msgStringi = String(message_buff);  
//int x = msgStringi.toInt();

  
  mqtt.publish("test/dos", val3);
long level = random(20,32); 
 byte msg [] = { 
     1,    // device 1
     val1,    // turn light on
     val2,
     val3,
     val4 // to what level
  };

  // send to slave  
  digitalWrite (ENABLE_PIN, HIGH);  // enable sending
  sendMsg (fWrite, msg, sizeof msg);
  
 //sendMsg (fWrite,(byte *) &message, sizeof msg);
  
  
  digitalWrite (ENABLE_PIN, LOW);  // disable sending

  // receive response  
  byte buf [10];
  byte received = recvMsg (fAvailable, fRead, buf, sizeof buf);
  
  digitalWrite (LED_PIN, received == 0);  // turn on LED if error    
  
  // only send once per successful change
  if (received)
    old_level = level;
    

  
}

void parse()
{
     
     char separator[] = ","; 

     char *result = NULL;
     int index = 0;

     result = strtok( message_buff, separator ); 
     while( (result != NULL) && (index < 4) ) {
       Serial.print(  result );
       Serial.println( );
     values[index++] = atol(result);    // become to values

     result = strtok( NULL, separator );  
     }

      
      val1 = values[0];
      val2 = values[1];
      val3 = values[2];
      val4 = values[3];

Serial.print("valor 1: "); Serial.println(val1);
Serial.print("valor 2: "); Serial.println(val2);
Serial.print("valor 3: "); Serial.println(val3);
Serial.print("valor 4: "); Serial.println(val4);
  
    
}
