#include <SimpleModbusSlave.h>

#define  LED 8  

//////////////// registers of your slave ///////////////////
enum 
{
  reg0_VAL,     
  reg1_VAL,        
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void setup()
{
  modbus_configure(&Serial, 9600, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  modbus_update_comms(9600, SERIAL_8N2, 1);
  
  pinMode(LED, OUTPUT);
}

void loop()
{

  modbus_update();
 // holdingRegs[ADC_VAL] = analogRead(A0);
  
 digitalWrite(LED, HIGH);
 delay(holdingRegs[reg0_VAL]);
 digitalWrite(LED, LOW);
 delay(holdingRegs[reg0_VAL]);
 
}
