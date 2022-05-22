/*
 * PaccerOutput
 * =========
 * 
 * Library for the output code for the Paccer Pinball.
 * -> either simulated or real
 * 
 * Created 2022-05-21
 * 
 * https://github.com/PaccerPinball/PaccerOutput
 */


#include "PaccerOutput.h"
#include <LiquidCrystal.h>

PaccerOutput::PaccerOutput(LiquidCrystal *lcd, const int &cols, const int &rows) {
    this->lcd = lcd;
    lcd->begin(cols, rows);
    updateScore(0);
}

void PaccerOutput::updateScore(const int &score) {
    clearRow(0);
    lcd->print(score);
}

void PaccerOutput::broadcast(const String& msg) {
    clearRow(1);
    lcd->print(msg); // TODO blinking + scroll left to remove?
}

void PaccerOutput::clearRow(int row) {
    lcd->setCursor(0, row);
    lcd->print("                ");
    lcd->setCursor(0, row);
}

void PaccerOutput::tick() {
    Serial.println("OUTPUT TICK");
}
