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
#include <LiquidCrystal_I2C.h>

PaccerOutput::PaccerOutput(LiquidCrystal_I2C *lcd) {
    this->lcd = lcd;
}

void PaccerOutput::updateScore(const uint32_t &score) {
    clearScore();

    lcd->print(score);
}

void PaccerOutput::broadcast(const String& msg) {
    currentBroadcastStart = millis(); // Reset time even when the broadcast is already shown.
    if (currentBroadcast == msg) return;

    clearBroadcast();
    currentBroadcast = msg;
    lcd->print(msg); // TODO blinking + scroll left to remove?
}

void PaccerOutput::clearBroadcast() {
    lcd->setCursor(0, 1);
    fori(currentBroadcast.length()) {
        lcd->print(' ');
    }
    lcd->setCursor(0, 1);
}

void PaccerOutput::clearScore() {
    lcd->setCursor(0, 0);
    lcd->print("                ");
    lcd->setCursor(0, 0);
}

void PaccerOutput::tick() {
    // Update broadcasts
    if (millis() - currentBroadcastStart > BROADCAST_TIMEOUT && currentBroadcastStart != 0) {
        broadcast("");
        currentBroadcastStart = 0;
        currentBroadcast = "";
    }
}
