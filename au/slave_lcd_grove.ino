#include <SoftwareSerial.h>
#include "RS485_protocol.h"
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

SoftwareSerial rs485 (2, 3);  // receive pin, transmit pin
const byte ENABLE_PIN = 4;

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
{
  rs485.begin (38400);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
  lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");
}

void loop()
{
  byte buf [100];
  
  byte received = recvMsg (fAvailable, fRead, buf, sizeof (buf));
  
  if (received)
    {
    if (buf [0] != 1)
      return;  // not my device
      
    if (buf [1] != 2)
      return;  // unknown command
    
    byte msg [] = {
       0,  // device 0 (master)
       3,  // turn light on command received
    };
    
    delay (100);  // give the master a moment to prepare to receive
    digitalWrite (ENABLE_PIN, HIGH);  // enable sending
    sendMsg (fWrite, msg, sizeof msg);
    digitalWrite (ENABLE_PIN, LOW);  // disable sending
    
  //  analogWrite (11, buf [2]);  // set light level
    
    
lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(buf [2]);    
    
    lcd.setCursor(10, 1);
    lcd.print(buf [1]); 
    
   }  // end if something received
   
}  // end of loop
