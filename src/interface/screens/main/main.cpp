#include "main.h"

// temp main screen : cépalaprio

void drawMainScreen(TFT_eSPI &tft) {
    // suppose that the tft is initialized
    tft.fillScreen(0x0000);
    tft.setCursor(100, 50);
    tft.setTextSize(2);
    tft.setTextColor(0xFFFF, 0x0000);

    tft.println("Main");
}
