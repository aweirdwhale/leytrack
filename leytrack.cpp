#include "leytrack.h"
#include "src/interface/screens/splash/splash.h"
#include "src/interface/screens/main/main.h"

#include "src/actions/handler.h"


TFT_eSPI tft = TFT_eSPI(); // Create TFT object

void _setup() {
    // Initialize the TFT display
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(0x0000);

    // debug
    // tft.setTextSize(2);
    // tft.setTextColor(0xFFFF, 0x0000); // Set text color to white with black background
    // tft.setCursor(75, 120);
    // tft.println("Leytrack");

    splashScreen(5000, tft);    // Show splash screen for 5 seconds
    // tft.fillScreen(0x0000);     // Clear the screen after splash

    // // Initialise the user experience
    initActionHandler();

    drawMainScreen(tft);
}

void _loop() {
    handleActions(tft);            // Handle user actions
}
