/*
 * PaccerOutput
 * =========
 *
 * Library for the output code for the Paccer Pinball.
 * -> either simulated or real
 *
 * This lib gets data from PaccerCommon, e.g. the score, which will then get displayed on the LCD
 *
 * Created 2022-05-21
 *
 * https://github.com/PaccerPinball/PaccerOutput
 */


#ifndef PaccerOutput_H
#define PaccerOutput_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <PaccerSound.h>
#include <avr/power.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define BROADCAST_TIMEOUT 3000
#define fori(x) for (unsigned int i = 0; i<x; i++)

// Sounds
#define SOUND_STARTUP 0
#define SOUND_PLING 1
#define SOUND_PLONG 2

// LED effects
#define LED_STARTUP 0
#define LED_PACMAN 1
#define LED_OFF 2

#define SERVO_MAX 54
#define SERVO_MIN 15
#define SERVO_INTERVAL 50

class PaccerOutput {
    private:
        String currentBroadcast;
        unsigned long currentBroadcastStart{};
        LiquidCrystal_I2C* lcd;
        PaccerSound* soundManager;
        Adafruit_NeoPixel* leds;
        Servo* mServo;
        uint16_t motorPin;
        void clearScore();
        void clearBroadcast();
        static void serial(const String &msg);
        int servoDirection;
        unsigned int servoPos = SERVO_MAX;
        unsigned long lastServoMove{};
public:
        explicit PaccerOutput(LiquidCrystal_I2C *lcd, PaccerSound *sound, Adafruit_NeoPixel *leds, const uint16_t& motorPin, Servo *servo);
        void updateScore(const uint32_t &score);
        void broadcast(const String &msg);
        void sound(const int &type);
        void led(const int &type);
        /** move the mServo to MIN position and back to MAX */
        void servo();
        void motor(const int &speed) const;
        /** Called from the main arduino sketch every loop() */
        void tick();
};

#endif
