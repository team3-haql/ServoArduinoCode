#pragma once

// Max angle servos can turn to
#define MAX_ANGLE 180.0
// Min angle servos can turn to
#define MIN_ANGLE 0.0
// Trackwidth of rover in meters
#define T 0.5969
// Wheelbase of rover in meters
#define W 0.6858

// Angle servos are initialized to.
#define START_ANGLE 90

// Size of input buffer
#define BUFFER_SIZE 32

// Min chars in message
#define MIN_CHARS_IN_MESSAGE 2

#define TIME_BETWEEN_SERVO_UPDATES_MS 20