#include <stdint.h>

#ifndef STEERING_H
    #define STEERING_H

    typedef struct {
        uint8_t cellVoltage;
        uint8_t cellTemperature;
    } IncomingACUCellData; // Do not reorder

    typedef struct {
        IncomingACUCellData cellData[160];
        char debugMessage[64];   // Treat as a string, if first bit '\0' then no message, clear in steering
    } IncomingData;

    extern volatile IncomingData incomingData;

    void sendStatus();
    void initLVGL();
#endif
