
#include "scanner.h"
#include "../../interface/screens/radar/radar.h"

#include <Arduino.h> // Pour FreeRTOS sur ESP32

// Handle de la tâche radar
TaskHandle_t radarTaskHandle = NULL;
bool radarRunning = false;

// ==== Tâche radar ====
void radarTask(void *pvParameters) {
    TFT_eSPI *tft = (TFT_eSPI *)pvParameters;

    while (radarRunning) {
        radarBackground(*tft); // Affiche le radar
        for (int i = 0; i < 300; i++) { // 300 x 10 ms = 3 secondes
            if (!radarRunning) break;   // Si on a demandé l'arrêt, on sort tout de suite
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    // Fin de la tâche
    vTaskDelete(NULL);
}

void startNewScan(TFT_eSPI &tft) {
    if (radarRunning) return; // Déjà en cours

    radarRunning = true;

    // Création d'une tâche FreeRTOS sur le core 1
    xTaskCreatePinnedToCore(
        radarTask,         // Fonction
        "RadarTask",       // Nom
        4096,              // Taille de la pile (bytes)
        &tft,              // Paramètre
        1,                 // Priorité
        &radarTaskHandle,  // Handle
        1                  // Core (1 recommandé pour l'affichage)
    );
}

void stopScan(TFT_eSPI &tft) {
    if (!radarRunning) return;

    radarRunning = false;

    // Optionnel : attendre que la tâche se termine
    while (radarTaskHandle != NULL && eTaskGetState(radarTaskHandle) != eDeleted) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    radarTaskHandle = NULL;

    //drawMainScreen(tft); // Retour écran principal
}
