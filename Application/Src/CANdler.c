#include <stdint.h>
#include <string.h>

#include "CANdler.h"
#include "fdcan.h"
#include "msgIDs.h"
#include "steering.h"

volatile int numberOfBadMessages = 0;

void handleCANMessage(uint16_t msgID, uint8_t srcID, uint8_t *data, uint32_t length, uint32_t timestamp) {
    UNUSED(timestamp);
    UNUSED(srcID);

    switch(msgID) {
        case MSG_DEBUG_FD:
            if (length > 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            strncpy(incomingData.debugMessage, (char*)data, length);

            break;
        case MSG_STEERING_CONFIG:
            // RESERVED
            break;
        case MSG_ACU_CELL_DATA_1:
            if (length != 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            memcpy(incomingData.cellData, data, length);

            break;
        case MSG_ACU_CELL_DATA_2:
            if (length != 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            memcpy(incomingData.cellData + length, data, length);

            break;
        case MSG_ACU_CELL_DATA_3:
            if (length != 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            memcpy(incomingData.cellData + 2 * length, data, length);

            break;
        case MSG_ACU_CELL_DATA_4:
            if (length != 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            memcpy(incomingData.cellData + 3 * length, data, length);

            break;
        case MSG_ACU_CELL_DATA_5:
            if (length != 64) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            memcpy(incomingData.cellData + 4 * length, data, length);

            break;
    }
}
