#ifndef _H_HANDLER_H_
#define _H_HANDLER_H_

#include "../../config/config.h"
#include <Arduino.h>

#include <TFT_eSPI.h>

void initActionHandler();    // Init butons
void handleActions(TFT_eSPI &tft);        // Read and handle inputs

#endif
