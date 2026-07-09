#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"
#include <math.h>

Servo servos[NUM_SERVOS];

bool isRunning = false;

void attachServos()
{
    for (uint8_t i = 0; i < NUM_SERVOS; i++)
    {
        if (!servos[i].attached())
        {
            servos[i].attach(
                SERVO_PINS[i],
                SERVO_MIN_US,
                SERVO_MAX_US);
        }
    }
}

void detachServos()
{
    for (uint8_t i = 0; i < NUM_SERVOS; i++)
    {
        servos[i].detach();
    }
}

void checkSerial()
{
    if (!Serial.available())
        return;

    String cmd = Serial.readStringUntil('\n');

    cmd.trim();
    cmd.toLowerCase();

    if (cmd == "s")
    {
        isRunning = true;
        Serial.println("START");
    }
    else if (cmd == "e")
    {
        isRunning = false;
        detachServos();
        Serial.println("STOP");
    }
}

void smartDelay(uint32_t ms)
{
    uint32_t start = millis();

    while (millis() - start < ms)
    {
        checkSerial();

        if (!isRunning)
            return;

        delay(10);
    }
}

void moveServoOpen(uint8_t index)
{
    for (int step = 0; step <= MOTION_STEPS && isRunning; step++)
    {
        // float ratio = step / (float)MOTION_STEPS;
        float t = step / (float)MOTION_STEPS;
        float ratio = 0.5f - 0.5f * cosf(PI * t);

        int angle =
            CLOSED_ANGLES[index] +
            OPEN_DELTA * ratio;

        servos[index].write(angle);

        smartDelay(STEP_DELAY_MS);
    }
}

void moveServoClose(uint8_t index)
{
    for (int step = MOTION_STEPS; step >= 0 && isRunning; step--)
    {
        // float ratio = step / (float)MOTION_STEPS;
        float t = step / (float)MOTION_STEPS;
        float ratio = 0.5f - 0.5f * cosf(PI * t);

        int angle =
            CLOSED_ANGLES[index] +
            OPEN_DELTA * ratio;

        servos[index].write(angle);

        smartDelay(STEP_DELAY_MS);
    }
}

void openSnake()
{
    // const uint8_t START_DELAY_STEPS = 5;

    for (int globalStep = 0;
         globalStep <= MOTION_STEPS + START_DELAY_STEPS * (NUM_SERVOS - 1);
         globalStep++)
    {
        for (uint8_t s = 0; s < NUM_SERVOS; s++)
        {
            int localStep = globalStep - s * START_DELAY_STEPS;

            if (localStep < 0)
                continue;

            if (localStep > MOTION_STEPS)
                localStep = MOTION_STEPS;

            float t = localStep / (float)MOTION_STEPS;
            float ratio = 0.5f - 0.5f * cosf(PI * t);

            // uint8_t servo = snakeOrderOpen[s];
            uint8_t servo = snakeOrder[s];

            int angle =
                CLOSED_ANGLES[servo] +
                OPEN_DELTA * ratio;

            servos[servo].write(angle);
        }

        smartDelay(STEP_DELAY_MS);
    }
}

void closeSnake()
{
    // const uint8_t START_DELAY_STEPS = 5;

    for (int globalStep = 0;
         globalStep <= MOTION_STEPS + START_DELAY_STEPS * (NUM_SERVOS - 1);
         globalStep++)
    {
        for (uint8_t s = 0; s < NUM_SERVOS; s++)
        {
            int localStep = globalStep - s * START_DELAY_STEPS;

            if (localStep < 0)
                continue;

            if (localStep > MOTION_STEPS)
                localStep = MOTION_STEPS;

            float t = 1.0f - localStep / (float)MOTION_STEPS;
            float ratio = 0.5f - 0.5f * cosf(PI * t);

            // uint8_t servo = snakeOrderClose[NUM_SERVOS - 1 - s];
            uint8_t servo = snakeOrder[s];

            int angle =
                CLOSED_ANGLES[servo] +
                OPEN_DELTA * ratio;

            servos[servo].write(angle);
        }

        smartDelay(STEP_DELAY_MS);
    }
}

void setup()
{
    Serial.begin(115200);

    delay(5000);

    for (uint8_t i = 0; i < NUM_SERVOS; i++)
    {
        pinMode(SERVO_PINS[i], OUTPUT);
        servos[i].setPeriodHertz(50);
    }

    attachServos();

    for (uint8_t i = 0; i < NUM_SERVOS; i++)
    {
        servos[i].write(CLOSED_ANGLES[i]);
    }

    delay(1000);

    detachServos();

    Serial.println("Ready. Send 's' to start and 'e' to stop.");
}

void loop()
{
    checkSerial();

    if (!isRunning)
    {
        delay(50);
        return;
    }

    Serial.println("Opening...");

    attachServos();

    openSnake();

    if (!isRunning)
    {
        detachServos();
        return;
    }

    Serial.println("Opened");
    smartDelay(DELAY_OPENED_MS);

    if (!isRunning)
    {
        detachServos();
        return;
    }

    Serial.println("Closing...");

    closeSnake();

    detachServos();

    if (isRunning)
    {
        Serial.println("Closed");
        smartDelay(DELAY_CLOSED_MS);
    }
}