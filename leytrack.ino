
#include "leytrack.h"

#include <TFT_eSPI.h>

void setup() {
    Serial.begin(115200);
    _setup();
}

void loop() {
    _loop();
}
