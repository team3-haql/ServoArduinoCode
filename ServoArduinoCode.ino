#include <stdio.h>
#include <Servo.h>
#include <math.h>

Servo servo1;  // Create a servo object
Servo servo2;
Servo servo3;
Servo servo4;

const int servoPin1 = 9; 
const int servoPin2 = 2;
const int servoPin3 = 3;
const int servoPin4 = 4;

const float L = 1;
const float W = 1; 
const float pi = 3.14; 

void setup() {
    servo1.attach(servoPin1);  // Attach the servo to the defined pin
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo4.attach(servoPin4);
    Serial.begin(9600);  // Start serial communication
    Serial.println("Enter an angle (0-180):");
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);

}

float R = 0; 

void loop() {
    if (Serial.available()>0) {
        String received = Serial.readStringUntil('\n');  // Read until newline
        int turn_angle = received.toInt();  // Convert to integer
        R = turn_angle * pi / 180;
      
        float radians = atan((L/ (R - (W/2))));
        servo1.write((radians * 180 / pi));
    }   
}