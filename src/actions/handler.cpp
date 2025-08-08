#include "handler.h"


void initActionHandler() {
    // Init each button pin
    pinMode(SCAN, INPUT_PULLUP);
    pinMode(MENU, INPUT_PULLUP);
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);
    pinMode(VALIDER, INPUT_PULLUP);

}
