
#include <SimpleModbusMaster.h>
#include "I2Cdev.h"
#include "MPU6050.h"


#include "Wire.h"

#define baud 9600
#define timeout 1000
#define polling 100 // the scan rate
#define retry_count 10

// used to toggle the receive/transmit pin on the driver
#define TxEnablePin 2 

#define LED 9

// The total amount of available memory on the master to store data
#define TOTAL_NO_OF_REGISTERS 16


enum
{
  PACKET1,
  PACKET2,
  TOTAL_NO_OF_PACKETS // leave this last entry
};

// Create an array of Packets to be configured
Packet packets[TOTAL_NO_OF_PACKETS];

// Masters register array
unsigned int regs[TOTAL_NO_OF_REGISTERS];



int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
long values []= {0,0,0,0};

int accel_angle1;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define LED_PIN 13
bool blinkState = false;

// accelerometer values
int accel_reading;
int accel_corrected;
int accel_readingy;
int accel_correctedy;
int accel_offset = 200;
float accel_angle;
float accel_angley;
float accel_scale = 1; // set to 0.01

// gyro values
int gyro_offset = 151; // 151
int gyro_corrected;
int gyro_reading;
float gyro_rate;
float gyro_scale = 0.02; // 0.02 by default - tweak as required
float gyro_angle;
float loop_time = 0.05; // 50ms loop
float angle = 0.00; // value to hold final calculated gyro angle

// time stamp variables
int last_update;
int cycle_time;
long last_cycle = 0;





void setup() {

        Wire.begin();
// initialize serial communication
Serial.begin(9600);


modbus_construct(&packets[PACKET1], 1, READ_HOLDING_REGISTERS, 0, 1, 0);
  modbus_construct(&packets[PACKET2], 1, PRESET_MULTIPLE_REGISTERS, 0, 2, 0);
  
  // Initialize the Modbus Finite State Machine
  modbus_configure(&Serial, baud, SERIAL_8N2, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);
  

// initialize device
Serial.println("Initializing I2C devices...");
accelgyro.initialize();

// verify connection
Serial.println("Testing device connections...");
Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");




    
}


byte old_level = 0;

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // accelerometer_X_Axis angle calc
  accel_reading = ax;
  accel_corrected = accel_reading - accel_offset;
  accel_corrected = map(accel_corrected, -16800, 16800, -90, 90);
  accel_corrected = constrain(accel_corrected, -90, 90);
  accel_angle = (float)(accel_corrected * accel_scale);
  Serial.print(accel_angle);
  Serial.print("\t");
  
  
  // accelerometer_Y_Axis angle calc
  accel_readingy = ay;
  accel_correctedy = accel_readingy - accel_offset;
  accel_correctedy = map(accel_correctedy, -16800, 16800, -90, 90);
  accel_correctedy = constrain(accel_correctedy, -90, 90);
  accel_angley = (float)(accel_correctedy * accel_scale);
  Serial.print(accel_angley);
  Serial.print("\t");
  
   
  // gyro_Y_Axis angle calc  
  gyro_reading = gy;
  gyro_corrected = (float)((gyro_reading/131) - gyro_offset);  // 131 is sensivity of gyro from data sheet
  gyro_rate = (gyro_corrected * gyro_scale) * -loop_time;      // loop_time = 0.05 ie 50ms        
  gyro_angle = angle + gyro_rate;
  
  // print values to serial monitor for checking 
  Serial.print(accel_angley);
  Serial.print("\t");
  Serial.print(gyro_corrected);
  Serial.print("\t");
  Serial.print(gyro_angle);
  Serial.print("\t");
  Serial.println(" ");
    
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  
//timestamp
time_stamp();




if (accel_angle < -1)

{accel_angle = accel_angle*-10;
modbus_update();
regs[0] = accel_angle;
regs[1] = accel_angley; 

}

else if (accel_angley < -1)
{accel_angley = accel_angley*-10;
modbus_update();
regs[0] = accel_angle;
regs[1] = accel_angley; 
}



else
{
modbus_update();
regs[0] = accel_angle;
regs[1] = accel_angley;  
}
}

void time_stamp(){
  while ((millis() - last_cycle) < 50){
  delay(1);
  }
  // once loop cycle reaches 50ms, reset timer value and continue
  cycle_time = millis() - last_cycle;
  last_cycle = millis();
}
