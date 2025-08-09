#include "splash.h"

void splashScreen(int duration, TFT_eSPI &tft) {
    unsigned long startTime = millis();

    // Array of texts to cycle through
    const char* texts[] = {"LeyTrack", "By Aweirdwhale"};
    int numTexts = sizeof(texts) / sizeof(texts[0]);
    int currentTextIndex = 0;

    while(millis() - startTime <= duration) { // so we can adjust splash duration from main file
        // We want to make a "breathing" effect
        // So we are gonn tweak the opacity of the text following a sine wave
        float timeElapsed = (float)(millis() - startTime) / 1000.0;             // Convert to seconds
        float breathingCycle = sin(timeElapsed *2.0) *.5 +.5;                   // between 0 and 1
        uint16_t textColor = tft.color565(256 * breathingCycle, 255 * breathingCycle, 255 * breathingCycle);

        // Change text based on breathing cycle peaks (when breathingCycle is near 0)
        static float lastBreathingCycle = 0.0;
        if (lastBreathingCycle > 0.1 && breathingCycle <= 0.1) {
            tft.fillScreen(0x0000);                                            // Clear the screen
            currentTextIndex = (currentTextIndex + 1) % numTexts;
        }
        lastBreathingCycle = breathingCycle;

        tft.setTextSize(2);                                                    // Set text size

        tft.setCursor(75, 120);
        tft.setTextColor(textColor, 0x0000);
        tft.println(texts[currentTextIndex]);

        delay(50);                                                              // limits updates
    }
}
