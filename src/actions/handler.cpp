
#include "handler.h"
#include "../behavior/scanner/scanner.h"

static const unsigned long debounceDelay = 50; // ms

// États des switchs
static bool radarOn = false;
static bool menuOn  = false;

// Variables pour debounce
static int lastRadarState = HIGH, lastMenuState = HIGH, lastUpState = HIGH, lastDownState = HIGH, lastOkState = HIGH;
static unsigned long lastRadarTime = 0, lastMenuTime = 0, lastUpTime = 0, lastDownTime = 0, lastOkTime = 0;

void initActionHandler() {
    // Init each button pin
    pinMode(SCAN, INPUT_PULLUP);
    pinMode(MENU, INPUT_PULLUP);
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);
    pinMode(VALIDER, INPUT_PULLUP);
}

void handleActions(TFT_eSPI &tft) {
    unsigned long currentMillis = millis();

    // === Bouton RADAR (switch) ===
    int radarState = digitalRead(SCAN);
    if (radarState != lastRadarState && (currentMillis - lastRadarTime) > debounceDelay) {
        lastRadarTime = currentMillis;
        if (radarState == LOW) { // clic
            if (menuOn) {
                menuOn = false; // Turn off menu if radar is started
                Serial.println("Force Menu OFF");
            }
            radarOn = !radarOn;
            Serial.println(radarOn ? "Radar ON" : "Radar OFF");

            // action

            startNewScan(tft);


        }
    }
    lastRadarState = radarState;

    // === Bouton MENU (switch) ===
    int menuState = digitalRead(MENU);
    if (menuState != lastMenuState && (currentMillis - lastMenuTime) > debounceDelay) {
        lastMenuTime = currentMillis;
        if (menuState == LOW) {
            if (radarOn) {
                radarOn = false; // Turn off radar if menu is opened
                Serial.println("Force Radar OFF");
            }
            menuOn = !menuOn;
            Serial.println(menuOn ? "Menu ON" : "Menu OFF");
        }
    }
    lastMenuState = menuState;

    // === Bouton UP (momentary) ===
    int upState = digitalRead(UP);
    if (upState != lastUpState && (currentMillis - lastUpTime) > debounceDelay) {
        lastUpTime = currentMillis;
        if (upState == LOW) {
            Serial.println("Haut");
        }
    }
    lastUpState = upState;

    // === Bouton DOWN (momentary) ===
    int downState = digitalRead(DOWN);
    if (downState != lastDownState && (currentMillis - lastDownTime) > debounceDelay) {
        lastDownTime = currentMillis;
        if (downState == LOW) {
            Serial.println("Bas");
        }
    }
    lastDownState = downState;

    // === Bouton OK (momentary) ===
    int okState = digitalRead(VALIDER);
    if (okState != lastOkState && (currentMillis - lastOkTime) > debounceDelay) {
        lastOkTime = currentMillis;
        if (okState == LOW) {
            Serial.println("OK");
        }
    }
    lastOkState = okState;
}
