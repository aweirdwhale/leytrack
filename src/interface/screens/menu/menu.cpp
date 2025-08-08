
#include "menu.h"

const char* menuItems[] = {
    "opt 1",
    "opt 2",
    "opt 3",
    "opt 4",
    "opt 5"
};

const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);

int selectedItem = 0; // active option index
int currentIndex = 0;
int lastIndex = -1;

void initMenu(TFT_eSPI &tft) {
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(0x0000);
    tft.setTextSize(2);

}

void drawMenu(TFT_eSPI &tft) {
    initMenu(tft);

    for (int i = 0; i < menuLength; i++) {
        if (i== selectedItem) {
            tft.setTextColor(0xffff, 0x001f); // Highlight color
        } else {
            tft.setTextColor(0xffff, 0x0000);
        }
        tft.setCursor(50, 40 + i *30); // offset for each item
        tft.println(menuItems[i]);
    }
}
