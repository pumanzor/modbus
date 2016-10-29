#include <SimpleModbusSlave.h>

#include <Wire.h>
#include "rgb_lcd.h"


#define baud 38400
#define timeout 1000
#define polling 200 // the scan rate
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

  
void setup()
{Serial.begin(38400);



  modbus_configure(&Serial, 115200, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs);

  // modbus_update_comms(baud, byteFormat, id) is not needed but allows for easy update of the
  // port variables and slave id dynamically in any function.
  modbus_update_comms(9600, SERIAL_8N2, 1);


pinMode(8, OUTPUT); //dir
pinMode(9, OUTPUT); //pul
pinMode(7, OUTPUT); //pul
digitalWrite(8, LOW);
digitalWrite(9, LOW);
//digitalWrite(7, HIGH);
digitalWrite(7, LOW);


 lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
   lcd.print("XYZ");
}

void loop()
{
modbus_update();
lcd.setCursor(5, 0);

if (holdingRegs[0] > 100)

{int data1 = (holdingRegs[0]/100)*-1;

lcd.print(data1);  

}

else
{lcd.print(holdingRegs[0]);}



lcd.setCursor(5, 1);
if (holdingRegs[1] > 100)

{int data2 = (holdingRegs[1]/10)*-1;

lcd.print(data2); 

}

else

{
lcd.print(holdingRegs[1]); 
}



  
int vueltas1 = holdingRegs[0]*20;    
int vueltas = holdingRegs[0]*10;



digitalWrite(9, HIGH);
delayMicroseconds(2500); // change value for speed fast 33 to 10000 slow
digitalWrite(9, LOW);
delayMicroseconds(2500); // change value for speed fast 33 to 10000 slow

//if (Distance >= vueltas || Distance >= (vueltas - 10))

//{digitalWrite(7, HIGH);
//Distance = vueltas;
//}

if
(holdingRegs[0] < 25)

{digitalWrite(7, HIGH);
digitalWrite(8, HIGH);
}

else if (holdingRegs[0] > 80)

{digitalWrite(7, HIGH);
digitalWrite(8, LOW);
}

else

{digitalWrite(7, LOW);
Distance = Distance + 1;
}  

}
