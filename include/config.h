#pragma once

#include <Arduino.h>

constexpr uint8_t NUM_SERVOS = 4;
const uint8_t snakeOrderOp[NUM_SERVOS] = {0, 1, 3, 2};
const uint8_t snakeOrderCl[NUM_SERVOS] = {2, 3, 1, 0};

constexpr uint8_t SERVO_PINS[NUM_SERVOS] = {
    3, 4, 5, 6
};

constexpr int CLOSED_ANGLES[NUM_SERVOS] = {
    90, 90, 90, 90
};

constexpr int OPEN_DELTA = 35;

constexpr int MOTION_STEPS = 30;
constexpr int STEP_DELAY_MS = 15;

constexpr uint32_t DELAY_OPENED_MS = 100;
constexpr uint32_t DELAY_CLOSED_MS = 100;

constexpr uint16_t SERVO_MIN_US = 500;
constexpr uint16_t SERVO_MAX_US = 2400;