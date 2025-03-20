#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>
#include <math.h>

#define SERVO_COUNT 4
#define START_ANGLE 90

#define L 1
#define W 1

Servo g_servos[SERVO_COUNT];  // Create servos

void setup() {
	Serial.begin(9600);  // Start serial communication
	const int servoPins[SERVO_COUNT] = {9, 10, 6, 5};
	for (int i = 0; i < SERVO_COUNT; i++) { // Attach the servo to the defined pin
		g_servos[i].attach(servoPins[i]);
		g_servos[i].write(START_ANGLE);
	}
	Serial.println("Enter an angle (0-180):");
}

void writeToServos(const int val) {
	for (int i = 0; i < SERVO_COUNT; i++) {
		// If i < 2 is true sign is -1 otherwise its 1.
		// Prevents branching
		// float sign = 1.0 - (2.0*static_cast<float>(i < 2));

		g_servos[i].write(val);
	}
}

void loop() {
	static float R = 0; 
    if (Serial.available()>0) {
        String received = Serial.readStringUntil('\n');  // Read until newline
        int turn_angle = received.toInt();  // Convert to integer
        Serial.println(PI);
        writeToServos(turn_angle);
    }   
}