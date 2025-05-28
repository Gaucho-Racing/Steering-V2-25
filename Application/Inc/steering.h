#include <stdint.h>

#include "CANdler.h"
#include "lvgl/lvgl.h"

#ifndef STEERING_H
    #define STEERING_H

    typedef struct {
        uint8_t cellVoltage;
        uint8_t cellTemperature;
    } IncomingACUCellData; // Do not reorder

    typedef struct {
        IncomingACUCellData cellData[160];
        char debugMessage[64];              // Treat as a string, if first bit '\0' then no message, clear in steering
        uint8_t ecuPingMap[3];      // Literal copy of ECU Status bits
    } IncomingData;

    typedef struct {
        SteeringStatusMsg steeringStatusMsg;
        SteeringConfigMsg steeringConfigMsg;
    } OutgoingData;

    extern volatile IncomingData incomingData;
    extern volatile OutgoingData outgoingData;

    void updatedDataRecieved(void);
#endif
