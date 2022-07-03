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

#define BROADCAST_TIMEOUT 3000
#define fori(x) for (unsigned int i = 0; i<x; i++)

// Sounds
#define SOUND_STARTUP 0
#define SOUND_PLING 1

// LED effects
#define LED_STARTUP 0
#define LED_PACMAN 1
#define LED_OFF 2

class PaccerOutput {
    private:
        String currentBroadcast;
        unsigned long currentBroadcastStart{};
        LiquidCrystal_I2C* lcd;
        PaccerSound* soundManager;
        Adafruit_NeoPixel* leds;
        void clearScore();
        void clearBroadcast();
        static void serial(const String &msg);
public:
        explicit PaccerOutput(LiquidCrystal_I2C *lcd, PaccerSound *sound, Adafruit_NeoPixel *leds);
        void updateScore(const uint32_t &score);
        void broadcast(const String &msg);
        void sound(const int &type);
        void led(const int &type);
        /** Called from the main arduino sketch every loop() */
        void tick();
};

#endif
