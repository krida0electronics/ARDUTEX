// 
// ARDUTEX TRAILING EDGE MOSFET AC LED DIMMER FOR 50HZ AND 60HZ AC LINES
//
// Dimmer output power levels from 0 to 255. 0 - off, 255 full output power.
//
// Available for sale here - https://www.tindie.com/stores/bugrovs2012/
//
// More information - krida.electronics@gmail.com
//
// Please note wiring with arduino uno: zerocross on D2, gate on D3
//


#include <TimerOne.h>

#define GATE 3        // PORD.3 | D3 
#define FREQ 10000    // for 50HZ - 10000, for 60HZ - 8330

unsigned char i;
unsigned long int inByte, timer;

void setup() {
  
  pinMode(GATE, OUTPUT);
  attachInterrupt(0, Zero_Cross_interrupt, FALLING);    // zero-cross external interupt on INT0 | D2
  Timer1.attachInterrupt( timerIsr );
}


void Zero_Cross_interrupt() {
   
  digitalWrite(GATE, HIGH);
  timer=(inByte*FREQ)/255;
  Timer1.initialize(timer);    
}

void timerIsr() {
  
  Timer1.stop();   
  digitalWrite(GATE, LOW);
}

void loop() {


  for (i=0; i<255; i++){

    inByte++;
    delay(10);
  }


  
}
