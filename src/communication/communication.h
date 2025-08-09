#ifndef _H_COMMUNICATION_H_
#define _H_COMMUNICATION_H_

#include <Arduino.h>
#include "../position/position.h"
// ==============================
// LoRa Const
// ==============================
#define LORA_BROADCAST_ADDR 0xFF   // broadcast LoRa addr
#define LORA_SYNC_WORD      0x34   // Sync word
#define LORA_FREQ           868E6  // LoRa freq (Europe)

// ==============================
// Structures
// ==============================

// recherche qlq
struct positionRequest_s {
    int UID;    // -1 => ignorer
    int target; // -1 => recherche dans tout les amis
    int TTL;
} __attribute__((packed));

// if I recieve a search request from someone that I know I answer with this
struct response_s {
    int UID;
    int target;
    position pos;
    int TTL;
} __attribute__((packed));


typedef positionRequest_s request ;
typedef response_s response ;

// default values :
const request defaultRequest = {
    -1, // UID
    -1, // target
    -1  // TTL
};

const response defaultResponse = {
    -1,-1,{0.0f, 0.0f, 0.0f, 0},-1
};

// ==============================
// Fonctions
// ==============================

// Initialise le module LoRa
void initLora();

request packRequest(int uid, int target, int ttl); // pack a request

response packResponse(int uid, int target, position pos, int ttl); // pack a response from uid target pos and a ttl

// Broadcast un message ()=> true si ça a fonctionné false sinon
// ignorer les valeurs par défaut
bool broadcast(const request &request = defaultRequest, const response &response = defaultResponse);

void listen();

void handleResponse();


#endif
