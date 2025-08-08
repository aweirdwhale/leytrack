#ifndef _H_RADAR_H_
#define _H_RADAR_H_

#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void radarBackground(TFT_eSPI &tft);
void placeMarker(TFT_eSPI &tft, int x, int y, uint16_t color);

#endif
