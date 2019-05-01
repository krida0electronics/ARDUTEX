// 
// ARDUTEX TRAILING EDGE MOSFET I2C AC LED DIMMER FOR 50HZ AND 60HZ AC LINES
//
// FULLY COMPATIBLE WITH ARDUINO PLATFORM
//
// BASED ON ARDUINO UNO BOOTLOADER @ATMEGA328P 16.000MHz
//
// USB-COM DRIVER CH340G
//
// Dimmer output power levels from 0 to 255. 0 - off, 255 full output power.
//
// Available for sale here - https://www.tindie.com/stores/bugrovs2012/
//
// More information - krida.electronics@gmail.com
//


#include <Wire.h>
#include <TimerOne.h>
#include <EEPROM.h>

#define ADDRESS 0x10  // Slave I2C address. Can be changeable!
#define GATE 3        // PORD.3 | D3 
#define FREQ 10000    // for 50HZ - 10000, for 60HZ - 8330

unsigned char NewEvent;
unsigned long int inByte, timer;

void setup() {
  
  pinMode(GATE, OUTPUT);
  Wire.begin(ADDRESS); 
  Wire.onReceive(receiveEvent);
  attachInterrupt(0, Zero_Cross_interrupt, FALLING);    // zero-cross external interupt on INT0 | D2
  Timer1.attachInterrupt( timerIsr );
  timer=EEPROM.read(0);
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  inByte = Wire.read();         // read one incoming byte from the master I2C device
  NewEvent=1;                   // set new event flag
}  

void Zero_Cross_interrupt() {
  
  digitalWrite(GATE, HIGH);
  Timer1.initialize(timer);    
}

void timerIsr() {
  
  Timer1.stop();   
  digitalWrite(GATE, LOW);
}

void loop() {

  if (NewEvent){
   
    Serial.print("<> Slave received - ");
    Serial.println(inByte);

    timer=(inByte*FREQ)/255;
    EEPROM.write(0, timer);

    Serial.print("<> TIMER - ");
    Serial.println(timer);
    Serial.println("");
    NewEvent=0;                            // reset event flag
  }
}
