#include <SimpleModbusMaster.h>

#define baud 9600
#define timeout 1000
#define polling 200
#define retry_count 10

#define TxEnablePin 2 

#define LED 9

#define TOTAL_NO_OF_REGISTERS 1

enum
{
  PACKET1,
  PACKET2,
  TOTAL_NO_OF_PACKETS // leave this last entry
};

Packet packets[TOTAL_NO_OF_PACKETS];

unsigned int regs[TOTAL_NO_OF_REGISTERS];

void setup()
{
     modbus_construct(&packets[PACKET1], 1, READ_HOLDING_REGISTERS, 0, 1, 0);
     modbus_construct(&packets[PACKET2], 1, PRESET_MULTIPLE_REGISTERS, 1, 1, 0); 
// modbus_construct(&packets[PACKET2], slaveID: 1, PRESET_MULTIPLE_REGISTERS, address_of_register: 1 , quantity_registers: 1, 0)
  
  modbus_configure(&Serial, baud, SERIAL_8N2, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);
  
  pinMode(LED, OUTPUT);
}

void loop()
{
  modbus_update();
  regs[0] = analogRead(0)/4;
  //analogWrite(LED, regs[0]>>2); 
}
