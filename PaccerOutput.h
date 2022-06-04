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

#define BROADCAST_TIMEOUT 3000
#define fori(x) for (unsigned int i = 0; i<x; i++)

class PaccerOutput {
    private:
        String currentBroadcast;
        unsigned long currentBroadcastStart{};
        LiquidCrystal_I2C* lcd;
        void clearScore();
        void clearBroadcast();
    public:
        explicit PaccerOutput(LiquidCrystal_I2C *lcd);
        void updateScore(const uint32_t &score);
        void broadcast(const String &msg);
        /** Called from the main arduino sketch every loop() */
        void tick();
};

#endif
