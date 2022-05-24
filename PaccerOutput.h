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
#include <LiquidCrystal.h>

#define BROADCAST_TIMEOUT 3000
#define fori(x) for (unsigned int i = 0; i<x; i++)

class PaccerOutput {
    private:
        String currentBroadcast;
        unsigned long currentBroadcastStart;
        LiquidCrystal* lcd;
        void clearScore();
        void clearBroadcast();
    public:
        explicit PaccerOutput(LiquidCrystal*, const int &cols, const int &rows);
        void updateScore(const uint32_t &score);
        void broadcast(const String &msg);
        /** Called from the main arduino sketch every loop() */
        void tick();
};

#endif
