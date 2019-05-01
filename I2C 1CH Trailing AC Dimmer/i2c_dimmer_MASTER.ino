

#include <Wire.h> 

#define ADDRESS 0x10

unsigned char i;

void setup() 
{ 
 Wire.begin();        
 Serial.begin(9600);  
 
} 

void loop() 
{ 

  for (i=40; i<255; i++){
  
  Wire.beginTransmission(ADDRESS);    // transmit to device 0x10
  Wire.write(i);                      // sends ONE bytes
  Wire.endTransmission();             // stop transmitting
  delay(50); 
  }

   for (i=254; i>40; i--){
  
  Wire.beginTransmission(ADDRESS);    // transmit to device 0x10
  Wire.write(i);                      // sends ONE bytes
  Wire.endTransmission();             // stop transmitting
  delay(50); 
  }

  
 

} 
