#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>
#include <math.h>

#define SERVO_COUNT 4
#define START_ANGLE 0

Servo g_servos[SERVO_COUNT];  // Create servos
const int g_servoPins[SERVO_COUNT] = {9, 10, 6, 5}; // 
int g_L = 1;
int g_W = 1;

void setup() {
	Serial.begin(9600);  // Start serial communication
	for (int i = 0; i < SERVO_COUNT; i++) { // Attach the servo to the defined pin
		g_servos[i].attach(g_servoPins[i]);
		g_servos[i].write(START_ANGLE);
	}
	Serial.println("Enter an angle (0-180):");
}

void writeToServos(const int val) {
	g_servos[0].write(val);
	g_servos[1].write(val);
	g_servos[2].write(val);
	g_servos[3].write(val);
}

void loop() {
	static float R = 0; 
    if (Serial.available()>0) {
        String received = Serial.readStringUntil('\n');  // Read until newline
        int turn_angle = received.toInt();  // Convert to integer

        writeToServos(turn_angle);
    }   
}