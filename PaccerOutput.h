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

class PaccerOutput {
    private:
        LiquidCrystal* lcd;
        void clearRow(int row);
    public:
        explicit PaccerOutput(LiquidCrystal*, const int &cols, const int &rows);
        void updateScore(const int &score);
        void broadcast(const String &msg);
};

#endif
