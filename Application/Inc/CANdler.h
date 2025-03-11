#include <stdint.h>

#ifndef CANDLER_H
#define CANDLER_H

#define LOCAL_GR_ID GR_STEERING_WHEEL

extern int numberOfBadMessages;

void handleCANMessage(uint16_t msgID, uint8_t srcID, uint8_t *data, uint32_t length, uint32_t timestamp);

void writeToECU(uint16_t msgID, uint8_t data[], uint32_t len);
void writeMessage(uint16_t msgID, uint8_t destID, uint8_t data[], uint32_t len);

typedef struct {
    uint8_t CMEandTME;
    uint8_t RME;
    uint8_t buttonMap;
} SteeringStatusMsg;

// EMTPY FOR NOW
typedef struct {
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
