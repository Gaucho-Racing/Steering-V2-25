#ifndef CANDLER_H
#define CANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define LOCAL_GR_ID GR_STEERING_WHEEL

extern volatile int numberOfBadMessages;

void handleCANMessage(uint16_t msgID, uint8_t srcID, uint8_t *data, uint32_t length, uint32_t timestamp);

typedef struct {
    uint8_t CMEandTME;
    uint8_t RME;
    uint8_t buttonMap;
} SteeringStatusMsg;

// EMTPY FOR NOW
typedef struct {
    bool DONOTUSE;
} SteeringConfigMsg;

typedef struct {
    uint8_t signalBits;
    uint16_t ping;
    uint32_t cacheSize;
    uint8_t reserved;
} TCMStatusMsg;

typedef struct {
    uint8_t cpuUsage;
    uint8_t gpuUsage;
    uint8_t memoryUsage;
    uint8_t storageUsage;
    uint8_t powerConsumption;
    uint8_t cpuTemp;
    uint8_t gpuTemp;
} TCMResourceUtilizationMsg;

#endif
