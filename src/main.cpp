#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>
#include <math.h>

#define SERVO_COUNT 4
#define START_ANGLE 0

#define MAX_ANGLE 135.0
#define MIN_ANGLE 45.0
#define L 1.0
#define W 1.0

enum class Direction {
	NEGATIVE = 0,
	POSITIVE = 1
};

Servo g_servos[SERVO_COUNT];  // Create servos
const int g_servoPins[SERVO_COUNT] = {9, 10, 6, 5};

void setup() {
	Serial.begin(9600);  // Start serial communication
	for (int i = 0; i < SERVO_COUNT; i++) { // Attach the servo to the defined pin
		g_servos[i].attach(g_servoPins[i]);
		g_servos[i].write(START_ANGLE);
	}
	Serial.println("Enter an angle [-1,1]:");
}

void writeToServos(const int valInner, const int valOuter, Direction swap) {
	if (swap == Direction::POSITIVE) {
		g_servos[0].write(90+valInner);
		g_servos[1].write(90+valOuter);
		g_servos[2].write(90-valInner);
		g_servos[3].write(90-valOuter);
	}
	else {
		g_servos[0].write(90-valOuter);
		g_servos[1].write(90-valInner);
		g_servos[2].write(90+valOuter);
		g_servos[3].write(90+valInner);
	}
}

float lerp(float t) {
	float normalizedT = (t + 1.0)/2;
	return ((1 - normalizedT)*MIN_ANGLE + normalizedT*MAX_ANGLE);
}

void loop() {
	static float R = 0; 
    if (Serial.available()>0) {
        String received = Serial.readStringUntil('\n');  // Read until newline
        float input = received.toFloat();  // 1 to -1

		Serial.print("Input: ");
		Serial.println(input);

		float thetaInner = abs((lerp(input) - 90)*(PI/180));

		Serial.print("Theta Inner: ");
		Serial.println(thetaInner);

		float thetaOuter;
		float denominator = (L/tan(thetaInner)) + W;

		Serial.print("Denominator: ");
		Serial.println(denominator);
		if (denominator == INFINITY) {
			thetaOuter = 0.0;
		}
		else if (denominator == NAN) {
			thetaOuter = 0.0;
		}
		else {
			thetaOuter = atan(L / denominator);
		}
		Serial.print("Theta Outer: ");
		Serial.println(thetaOuter);

		Direction direction = input >= 0 ? Direction::POSITIVE : Direction::NEGATIVE;

        writeToServos(thetaInner*(180/PI), thetaOuter*(180/PI), direction);
    }   
}