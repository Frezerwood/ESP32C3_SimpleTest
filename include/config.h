#pragma once

#include <Arduino.h>

constexpr uint8_t NUM_SERVOS = 4;

constexpr uint8_t SERVO_PINS[NUM_SERVOS] = {
    3, 4, 5, 6
};

constexpr int CLOSED_ANGLES[NUM_SERVOS] = {
    85, 87, 78, 85
};

constexpr int OPEN_DELTA = 30;

constexpr int MOTION_STEPS = 30;
constexpr int STEP_DELAY_MS = 10;

constexpr uint32_t DELAY_OPENED_MS = 2000;
constexpr uint32_t DELAY_CLOSED_MS = 2000;

constexpr uint16_t SERVO_MIN_US = 500;
constexpr uint16_t SERVO_MAX_US = 2400;