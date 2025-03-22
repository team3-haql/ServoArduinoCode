#include <Servo.h>
#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define TEST
// #define DEBUG

#define SERVO_COUNT 4
#define START_ANGLE 0

#define BUFFER_SIZE 32

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
#ifdef TEST
	Serial.println("Enter an angle [-1,1]:");
#endif
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

void read(char* buffer) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = Serial.read();
		if (buffer[i] == '\n') {
			buffer[i] = '\0';
			break;
		}
	} 
}

void loop() {
    if (Serial.available()>1) {
		static char buffer[BUFFER_SIZE];
		delay(10);
		read(buffer);
        
        float input = atof(buffer);  // 1 to -1
	
	#ifdef DEBUG
		Serial.print("Input: ");
		Serial.println(input);
	#endif

		float thetaInner = abs((lerp(input) - 90)*(PI/180));

	#ifdef DEBUG
		Serial.print("Theta Inner: ");
		Serial.println(thetaInner);
	#endif

		float thetaOuter;
		float denominator = (L/tan(thetaInner)) + W;
	#ifdef DEBUG
		Serial.print("Denominator: ");
		Serial.println(denominator);
	#endif
		if (denominator == INFINITY) {
			thetaOuter = 0.0;
		}
		else if (denominator == NAN) {
			thetaOuter = 0.0;
		}
		else {
			thetaOuter = atan(L / denominator);
		}
	#ifdef DEBUG
		Serial.print("Theta Outer: ");
		Serial.println(thetaOuter);
	#endif

		Direction direction = input >= 0 ? Direction::POSITIVE : Direction::NEGATIVE;

        writeToServos(thetaInner*(180/PI), thetaOuter*(180/PI), direction);

		Serial.flush();
    }   
}