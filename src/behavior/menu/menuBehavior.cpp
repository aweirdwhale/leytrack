#include "menuBehavior.h"
#include "../../../config/config.h"
#include "../../interface/screens/menu/menu.h"
#include <Arduino.h>


static const unsigned long debounceDelay = 50; // ms
static int lastUpState = HIGH, lastDownState = HIGH, lastOkState = HIGH;
static unsigned long lastUpTime = 0, lastDownTime = 0, lastOkTime = 0;

// FreeRTOS
TaskHandle_t menuTaskHandle = NULL;
bool menuRunning = false;

// === Tâche Menu ===
void menuTask(void *pvParameters) {
    TFT_eSPI *tft = (TFT_eSPI *)pvParameters;

    tft->fillScreen(0x0000);
    drawMenu(*tft); // Affichage initial

    bool menuNeedsRefresh = true;

    while (menuRunning) {
        unsigned long currentMillis = millis();

        // Bouton UP
        int upState = digitalRead(UP);
        if (upState != lastUpState && (currentMillis - lastUpTime) > debounceDelay) {
            lastUpTime = currentMillis;
            if (upState == LOW) {
                selectedItem--;
                if (selectedItem < 0) selectedItem = menuLength - 1;
                menuNeedsRefresh = true;
                Serial.println("Haut dans le menu");
            }
        }
        lastUpState = upState;

        // Bouton DOWN
        int downState = digitalRead(DOWN);
        if (downState != lastDownState && (currentMillis - lastDownTime) > debounceDelay) {
            lastDownTime = currentMillis;
            if (downState == LOW) {
                selectedItem++;
                if (selectedItem >= menuLength) selectedItem = 0;
                menuNeedsRefresh = true;
                Serial.println("Bas dans le menu");
            }
        }
        lastDownState = downState;

        // Bouton OK
        int okState = digitalRead(VALIDER);
        if (okState != lastOkState && (currentMillis - lastOkTime) > debounceDelay) {
            lastOkTime = currentMillis;
            if (okState == LOW) {
                Serial.printf("OK pressed on %d\n", selectedItem + 1);
            }
        }
        lastOkState = okState;

        // Rafraîchissement uniquement si nécessaire
        if (menuNeedsRefresh) {
            drawMenu(*tft);
            menuNeedsRefresh = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // bouclage fluide
    }


    vTaskDelete(NULL);
}

// === Lancer le menu ===
void startMenu(TFT_eSPI &tft) {
    if (menuRunning) return; // Déjà en cours

    menuRunning = true;
    xTaskCreatePinnedToCore(
        menuTask,          // Fonction
        "MenuTask",        // Nom
        4096,              // Taille stack
        &tft,              // Paramètre
        1,                 // Priorité
        &menuTaskHandle,   // Handle
        1                  // Core 1 (affichage)
    );
}

// === Arrêter le menu ===
void stopMenu(TFT_eSPI &tft) {
    if (!menuRunning) return;

    menuRunning = false;
    while (menuTaskHandle != NULL && eTaskGetState(menuTaskHandle) != eDeleted) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    menuTaskHandle = NULL;

    //drawMainScreen(tft); // Retour écran principal
}
