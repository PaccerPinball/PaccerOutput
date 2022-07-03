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
#include <PaccerSound.h>
#include <LiquidCrystal_I2C.h>

int startupMelody[] = {
        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
        NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
        NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

        NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
        NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
        NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8,

        MELODY_END
};

int plingMelody[] = {
        NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8,

        MELODY_END
};

PaccerOutput::PaccerOutput(LiquidCrystal_I2C *lcd, PaccerSound *sound, Adafruit_NeoPixel *leds) {
    this->lcd = lcd;
    this->leds = leds;
    this->soundManager = sound;
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

void PaccerOutput::sound(const int &type) {
    switch (type) {
        case SOUND_STARTUP:
            soundManager->melody(startupMelody);
            break;
        case SOUND_PLING:
            soundManager->melody(plingMelody);
            break;
        default:
            serial("Unknown sound type " + String(type));
    }
}

void PaccerOutput::led(const int &type) {
    switch (type) {
        case LED_STARTUP:
            leds->rainbow();
            break;
        case LED_PACMAN:
            leds->fill(Adafruit_NeoPixel::Color(255, 255, 0));
            break;
        case LED_OFF:
            leds->clear();
            break;
        default:
            serial("Unknown led effect type " + String(type));
    }
    leds->show();
}

void PaccerOutput::serial(const String &msg) {
    Serial.println( "OUTPUT | " + msg);
}
