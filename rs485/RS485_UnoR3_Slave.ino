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
  
 digitalWrite(LED, HIGH);
 delay(holdingRegs[PWM_VAL]);
 digitalWrite(LED, LOW);
 delay(holdingRegs[PWM_VAL]);
 
 
 lcd.setCursor(0, 1);
 lcd.print(holdingRegs[PWM_VAL]);
 lcd.print("  "); 
 lcd.setCursor(5, 1);
 lcd.print(holdingRegs[PWM_VAL]>>2); 
 lcd.print("  ");  
 lcd.setCursor(10, 1);
 lcd.print(holdingRegs[PWM_VAL]>>4);
 lcd.print("  "); 


}
