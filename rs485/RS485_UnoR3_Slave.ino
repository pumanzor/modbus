#include <SimpleModbusSlave.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int sensorValue = 0;  
int outputValue = 0; 


#define  LED 8  

//////////////// registers of your slave ///////////////////
enum 
{
  ADC_VAL,     
  PWM_VAL,        
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void setup()
{
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    lcd.print("Receiving from Master...");
  
  modbus_configure(&Serial, 9600, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  modbus_update_comms(9600, SERIAL_8N2, 1);
  
  pinMode(LED, OUTPUT);
}

void loop()
{

  modbus_update();
  holdingRegs[ADC_VAL] = analogRead(A0);
  sensorValue = holdingRegs[PWM_VAL];

  outputValue = map(sensorValue, 0, 1023, 0, 255);

 if ( holdingRegs[PWM_VAL] > 600)
 {digitalWrite(LED, HIGH);
 delay(250);
 digitalWrite(LED, LOW);
 delay(250);
 }
 
 else {digitalWrite(LED, HIGH);}

lcd.setCursor(0, 1);
lcd.print(outputValue);  
lcd.setCursor(5, 1);
lcd.print(holdingRegs[PWM_VAL]>>4);  
lcd.setCursor(10, 1);
lcd.print(holdingRegs[PWM_VAL]);  

}
