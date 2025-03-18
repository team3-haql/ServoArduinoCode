// #include <stdio.h>
// #include <Servo.h>
// #include <math.h>

// Servo servo1;  // Create a servo object
// Servo servo2;
// Servo servo3;
// Servo servo4;

// const int servoPin1 = 9; 
// const int servoPin2 = 2;
// const int servoPin3 = 3;
// const int servoPin4 = 4;

// const int L = 1;
// const int W = 1; 


// void setup() {
//     myServo.attach(servoPin);  // Attach the servo to the defined pin
//     Serial.begin(9600);  // Start serial communication
//     Serial.println("Enter an angle (0-180):");
//     myServo.write(0);
// }


// void loop() {
//     if (Serial.available()) {
//         String received = Serial.readStringUntil('\n');  // Read until newline
//         int num = received.toInt();  // Convert to integer
//         myServo.write(num);
//     }
// }




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


// #include <Servo.h>
// #include <math.h>

// Servo servo1;  // Front left servo
// Servo servo2;  // Front right servo
// Servo servo3;  // Rear left servo
// Servo servo4;  // Rear right servo

// const int servoPin1 = 9;
// const int servoPin2 = 2;
// const int servoPin3 = 3;
// const int servoPin4 = 4;

// const float L = 1.0;  // Wheelbase
// const float W = 1.0;  // Track width
// const float pi = 3.141592653589793; // Use float/double precision

// void setup() {
//     Serial.begin(9600);
//     Serial.println("Enter an angle (0-180):");

//     servo1.attach(servoPin1);
//     servo2.attach(servoPin2);
//     servo3.attach(servoPin3);
//     servo4.attach(servoPin4);

//     // Initialize all servos to the neutral position
//     servo1.write(90);
//     servo2.write(90);
//     servo3.write(90);
//     servo4.write(90);
// }

// void loop() {
//   // need to convert turn radius to angle -- the angle to angle is a bit weird
//     if (Serial.available()) {
//         String received = Serial.readStringUntil('\n');  // Read serial input
//         int turn_angle = received.toInt();  // Convert input to integer

//         if (turn_angle < 0 || turn_angle > 180) {
//             Serial.println("Invalid angle! Enter a value between 0 and 180.");
//             return;
//         }

//         Serial.print("Received turn angle: ");
//         Serial.println(turn_angle);

//         // Convert turn angle to turning radius R
//         float R = turn_angle * pi / 180.0;  // Ensure correct float division

//         // Compute Ackerman steering angles
//         float theta_inner = atan(L / (R - (W / 2.0))) * (180.0 / pi);
//         float theta_outer = atan(L / (R + (W / 2.0))) * (180.0 / pi);

//         Serial.print("Inner wheel angle: ");
//         Serial.println(theta_inner);
//         Serial.print("Outer wheel angle: ");
//         Serial.println(theta_outer);

//         // Send commands to servos
//         servo1.write(90 - theta_inner);  // Adjust as needed
//         servo2.write(90 + theta_outer);
//         servo3.write(90 - theta_inner);  // Rear wheels counter-steer
//         servo4.write(90 - theta_outer);

//         // Prompt again for input
//         Serial.println("Enter an angle (0-180):");
//     }
// }
