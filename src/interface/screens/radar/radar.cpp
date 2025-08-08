
#include "radar.h"


// Radar background => aesthetic + each circle is a range
void radarBackground(TFT_eSPI &tft) {

      tft.setRotation(0);

      uint16_t bgColor = 0x00E0; // Couleur verte foncée
      tft.fillScreen(bgColor);

      int centerX = tft.width() / 2;
      int centerY = tft.height() / 2;


      uint16_t circleColor = 0x01A0;

      for (int i = 1; i <= 5; i++) {
        int radius = i * 20;
        tft.drawCircle(centerX, centerY, radius, circleColor);
      }

      // point central
      tft.fillCircle(centerX, centerY, 2, 0x01A0);

}

// Place a marker on the radar screen
// each marker is a friend
void placeMarker(TFT_eSPI &tft, int x, int y, uint16_t color) {
    tft.fillCircle(x, y, 5, color);
}
