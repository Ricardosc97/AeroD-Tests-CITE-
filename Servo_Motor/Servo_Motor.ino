// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
int botonPin = 2;
int val = 0;
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin);
   Serial.begin(9600); 
   pinMode(botonPin,INPUT);
}
void loop(){ 
   val = digitalRead(botonPin);
   Serial.print(val);
   if (val == 1){
    Servo1.write(0); 
    delay(500); 
    } else {
        Servo1.write(90);
        delay(500); 
    }
    
}
