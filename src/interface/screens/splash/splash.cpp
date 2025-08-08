#include "splash.h"

void splashScreen(int duration, TFT_eSPI &tft) {
    unsigned long startTime = millis();

    while(millis() - startTime <= duration) { // so we can adjust splash duration from main file
        // We want to make a "breathing" effect
        // So we are gonn tweak the opacity of the text following a sine wave
        float timeElapsed = (float)(millis() - startTime) / 1000.0;             // Convert to seconds
        float breathingCycle = sin(timeElapsed *2.0) *.5 +.5;                   // between 0 and 1
        uint16_t textColor = tft.color565(256 * breathingCycle, 255 * breathingCycle, 255 * breathingCycle);

        tft.setCursor(75, 120);
        tft.setTextColor(textColor, 0x0000);
        tft.println("Welcome.");

        delay(50);                                                              // limits updates
    }
}
