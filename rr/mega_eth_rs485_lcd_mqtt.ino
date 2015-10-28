#include <SimpleModbusMaster.h>

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
 
/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x20  // Direccion I2C para PCF8574A que es el que lleva nuestra placa diseñada por MJKDZ
//definimos las constantes para esta placa
 
#define  LED_OFF  0
#define  LED_ON  1
 
//mjkdz i2c LCD board
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define baud 153600
#define timeout 200
#define polling 100 
#define retry_count 10
unsigned long time;
char message_buff[100];

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
long values []= {0,0,0,0};


byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 30, 129);
IPAddress netmask(255, 255,255, 0);
IPAddress gateway(192, 168, 30, 1);
IPAddress server(190, 97, 168, 236);


void callback(char* topic, byte* payload, unsigned int length);


EthernetClient ethClient;
PubSubClient client(server,1883,callback,ethClient);



// used to toggle the receive/transmit pin on the driver
#define TxEnablePin 2 

// The total amount of available memory on the master to store data
#define TOTAL_NO_OF_REGISTERS 32

// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.
enum
{
  PACKET1,
  PACKET2,
  PACKET3,
  TOTAL_NO_OF_PACKETS // leave this last entry
};

// Create an array of Packets to be configured
Packet packets[TOTAL_NO_OF_PACKETS];

// Masters register array
unsigned int regs[TOTAL_NO_OF_REGISTERS];

void setup()
{
  Serial.begin(9600);
  // Initialize each packet
  modbus_construct(&packets[PACKET1], 1, READ_HOLDING_REGISTERS, 0, 1, 0);
  modbus_construct(&packets[PACKET2], 1, PRESET_MULTIPLE_REGISTERS, 0, 16, 0);
 // modbus_construct(&packets[PACKET3], 1, PRESET_MULTIPLE_REGISTERS, 200, 4, 0);
  // Initialize the Modbus Finite State Machine
  modbus_configure(&Serial, baud, SERIAL_8N2, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);
  
  lcd.begin (20,4);  // inicializar lcd 
// Activamos la retroiluminacion
  lcd.setBacklight(LED_ON);

  lcd.setCursor(0,1);


Ethernet.begin(mac, ip);
  if (client.connect("arduinoClient")) {
    client.publish("test/temp2","hello world");
    client.subscribe("rr/temp");
  }


}


void callback(char* topic, byte* payload, unsigned int length) {


  
  

  int i = 0;
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
//String msgString = String(message_buff);  
//Serial.println("Payload: " + msgString);

parse();


  



  
}


void loop()
{

client.loop();

if (val4 == 1) 
{
modbus_update(); 
regs[0] = val1;
regs[1] = val2;
regs[2] = val3;
regs[3] = val4;


/*  lcd.setCursor(0,0);
 lcd.print("SA:");
 lcd.setCursor(3,0);
float val11 = val1 / 100.0;
lcd.print(val11, 1);
lcd.setCursor(7,0);
lcd.print("\337");
  
  lcd.setCursor(9,0);
  float val22 = val2 / 100.0;
  lcd.print(val22, 1);
  lcd.setCursor(13,0);
lcd.print("\337");
  
  lcd.setCursor(15,0);
  float val33 = val3 / 100.0;
    String cent = "" + (char)223 ;
  lcd.print(val33, 1);
  lcd.setCursor(19,0);
  lcd.print("%");
  */

}
 else if (val4 == 2)
{
modbus_update(); 
regs[4] = val1;
regs[5] = val2;
regs[6] = val3;
regs[7] = val4;



  lcd.setCursor(0,1);
 lcd.print("SB:");
 lcd.setCursor(3,1);
float val11 = val1 / 100.0;
lcd.print(val11, 1);
lcd.setCursor(7,1);
lcd.print("\337");
  
  lcd.setCursor(9,1);
  float val22 = val2 / 100.0;
  lcd.print(val22, 1);
  lcd.setCursor(13,1);
lcd.print("\337");
  
  lcd.setCursor(15,1);
  float val33 = val3 / 100.0;
    String cent = "" + (char)223 ;
  lcd.print(val33, 1);
  lcd.setCursor(19,1);
  lcd.print("%");
  
  

}

 else if (val4 == 3)
{
modbus_update(); 
regs[8] = val1;
regs[9] = val2;
regs[10] = val3;
regs[11] = val4;



  lcd.setCursor(0,2);
 lcd.print("SC:");
 lcd.setCursor(3,2);
float val11 = val1 / 100.0;
lcd.print(val11, 1);
lcd.setCursor(7,2);
lcd.print("\337");
  
  lcd.setCursor(9,2);
  float val22 = val2 / 100.0;
  lcd.print(val22, 1);
  lcd.setCursor(13,2);
lcd.print("\337");
  
  lcd.setCursor(15,2);
  float val33 = val3 / 100.0;
    String cent = "" + (char)223 ;
  lcd.print(val33, 1);
  lcd.setCursor(19,2);
  lcd.print("%");
  

}

 else if (val4 == 4)
{
modbus_update(); 
regs[12] = val1;
regs[13] = val2;
regs[14] = val3;
regs[15] = val4;


  lcd.setCursor(0,3);
 lcd.print("SD:");
 lcd.setCursor(3,3);
float val11 = val1 / 100.0;
lcd.print(val11, 1);
lcd.setCursor(7,3);
lcd.print("\337");
  
  lcd.setCursor(9,3);
  float val22 = val2 / 100.0;
  lcd.print(val22, 1);
  lcd.setCursor(13,3);
lcd.print("\337");
  
  lcd.setCursor(15,3);
  float val33 = val3 / 100.0;
    String cent = "" + (char)223 ;
  lcd.print(val33, 1);
  lcd.setCursor(19,3);
  lcd.print("%");
  
  
}

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
