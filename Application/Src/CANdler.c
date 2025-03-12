#include <stdint.h>

#include "CANdler.h"
#include "fdcan.h"
#include "msgIDs.h"

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

            char* debug2String = (char*)data;
            UNUSED(debug2String);

            break;
        case MSG_STEERING_CONFIG:
            // RESERVED
            break;
        case MSG_TCM_STATUS:
            if (length != 8) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            TCMStatusMsg* tcmStatusMsg = (TCMStatusMsg*)data;
            UNUSED(tcmStatusMsg);

            break;
        case MSG_TCM_RESOURCE_UTILIZATION:
            if (length != 7) {
                numberOfBadMessages++;
                return;
            } else {
                numberOfBadMessages += (numberOfBadMessages > 0) ? -1 : 0;
            }

            TCMResourceUtilizationMsg* tcmResUtilMsg = (TCMResourceUtilizationMsg*)data;
            UNUSED(tcmResUtilMsg);
            break;
    }
}
