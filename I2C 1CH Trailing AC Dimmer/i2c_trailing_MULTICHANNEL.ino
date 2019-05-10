#include <Wire.h> 

#define DEVICE_01 0x10   // slave address of #1 device
#define DEVICE_02 0x11   // slave address of #2 device
#define DEVICE_03 0x12   // slave address of #3 device
#define DEVICE_04 0x13   // slave address of #4 device
#define DEVICE_05 0x14   // slave address of #5 device
#define DEVICE_06 0x15   // slave address of #6 device
#define DEVICE_07 0x16   // slave address of #7 device
#define DEVICE_08 0x17   // slave address of #8 device

unsigned char i;

void setup() 
{ 
 Wire.begin();        
 Serial.begin(9600);  
 
} 


void set_level (unsigned char address, unsigned char level){

  Wire.beginTransmission(address);        // select i2c slave device address 
  Wire.write(level);                      // set dimmer output power level
  Wire.endTransmission();                 // stop transmitting
}

void loop() 
{ 

  
 set_level(DEVICE_01, 200); 
 set_level(DEVICE_02, 80); 
 set_level(DEVICE_03, 200); 
 set_level(DEVICE_04, 80);
 set_level(DEVICE_05, 200); 
 set_level(DEVICE_06, 80);
 set_level(DEVICE_07, 200); 
 set_level(DEVICE_08, 80);
 delay(1000);

 set_level(DEVICE_01, 80); 
 set_level(DEVICE_02, 200); 
 set_level(DEVICE_03, 80); 
 set_level(DEVICE_04, 200);
 set_level(DEVICE_05, 80); 
 set_level(DEVICE_06, 200);
 set_level(DEVICE_07, 80); 
 set_level(DEVICE_08, 200);
 delay(1000);

 
 

  
 

} 
