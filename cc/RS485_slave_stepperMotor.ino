#include <SimpleModbusSlave.h>
#include <AccelStepper.h>
#include <Wire.h>
#include "rgb_lcd.h"


#define baud 38400
#define timeout 1000
#define polling 1000 // the scan rate
#define retry_count 10


int Distance = 0;

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

#define TxEnablePin 2
#define  LED 10

enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  ADC_VAL,     
  PWM_VAL,        
  HOLDING_REGS_SIZE // leave this one
  // total number of registers for function 3 and 16 share the same register array
  // i.e. the same address space
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array

 AccelStepper stepper3(2, 8, 9); 
void setup()
{Serial.begin(38400);



  modbus_configure(&Serial, 38400, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs);

  // modbus_update_comms(baud, byteFormat, id) is not needed but allows for easy update of the
  // port variables and slave id dynamically in any function.
  modbus_update_comms(9600, SERIAL_8N2, 1);


 lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
   lcd.print("XYZ");
   
     stepper3.setMaxSpeed(5600.0);
    stepper3.setAcceleration(8000.0);
}

void loop()
{


  
  modbus_update();
  
  //holdingRegs[ADC_VAL] = analogRead(A0); // update data to be read by the master to adjust the PWM
  
 //analogWrite(LED, holdingRegs[1]);
   
 
  //lcd.setCursor(5, 1);
    //lcd.print(holdingRegs[1]); 
    
int value = holdingRegs[0];  
 
if (value > 120)
 
 {int value1 = -abs(value/10);
     lcd.setCursor(5, 0);
    lcd.print(value1);   
    
stepper3.moveTo(value1*12);
    stepper3.run();

 
 }
   else {
    
    lcd.setCursor(5, 0);
    lcd.print(holdingRegs[0]);   
    
stepper3.moveTo(holdingRegs[0]*25);
    stepper3.run();
   }

}
