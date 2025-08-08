#ifndef _H_MENU_H_
#define _H_MENU_H_

#include <TFT_eSPI.h>

extern TFT_eSPI tft;

extern const int menuLength;
extern int selectedItem;
extern int lastIndex;
extern int currentIndex;

extern const char* menuItems[];

void initMenu(TFT_eSPI &tft);
void drawMenu(TFT_eSPI &tft, int selectedItem);


#endif
