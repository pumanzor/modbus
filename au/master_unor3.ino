#include "RS485_protocol.h"
#include <SoftwareSerial.h>

const byte ENABLE_PIN = 4;
const byte LED_PIN = 13;

SoftwareSerial rs485 (2, 3);  // receive pin, transmit pin

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
{
  rs485.begin (38400);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
 pinMode (LED_PIN, OUTPUT);  // built-in LED
}  // end of setup
  
byte old_level = 0;

void loop()
{

  // read potentiometer
 // byte level = analogRead (0) / 4;
  long level = random(20,32); 
  
 
  // no change? forget it
  if (level == old_level)
    return;
      
  // assemble message
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
    old_level = level;

}  // end of loop
