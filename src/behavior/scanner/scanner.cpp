#include "scanner.h"
#include "../../interface/screens/radar/radar.h"

// Scanner request !! what should we do?
// 1 -> Send packet through LoRa
// 2 -> show radar on TFT
// 3 -> wait for response
// 4 -> if response, process data then place markers on TFT
// 5 -> if no response, show "Scan failed" message on TFT


void startNewScan(TFT_eSPI &tft) {
    // 1-3 -> include ../../communication/communication.h

    // 2
    radarBackground(tft);



}
