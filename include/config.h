#pragma once

#include <Arduino.h>

constexpr uint8_t NUM_SERVOS = 4;

constexpr uint8_t snakeOrder[NUM_SERVOS] = {0, 1, 3, 2};

const uint8_t START_DELAY_STEPS = 5;

constexpr uint8_t SERVO_PINS[NUM_SERVOS] = {
    3, 4, 5, 6
};

constexpr int CLOSED_ANGLES[NUM_SERVOS] = {
    90, 90, 90, 90
};

constexpr int OPEN_DELTA = 35;

constexpr int MOTION_STEPS = 40;
constexpr int STEP_DELAY_MS = 20;

constexpr uint32_t DELAY_OPENED_MS = 100;
constexpr uint32_t DELAY_CLOSED_MS = 100;

constexpr uint16_t SERVO_MIN_US = 500;
constexpr uint16_t SERVO_MAX_US = 2400;