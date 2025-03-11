#include <stdint.h>

#include "CANdler.h"
#include "msgIDs.h"
#include "grIDs.h"
#include "fdcan.h"

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

void writeToECU(uint16_t msgID, uint8_t* data, uint32_t len) {
    writeMessage(msgID, GR_ECU, data, len);
}

FDCAN_TxHeaderTypeDef TxHeader = {
    .IdType = FDCAN_STANDARD_ID,
    .TxFrameType = FDCAN_DATA_FRAME,
    .ErrorStateIndicator = FDCAN_ESI_ACTIVE, // honestly this might be a value you have to read from a node
                                             // FDCAN_ESI_ACTIVE is just a state that assumes there are minimal errors
    .BitRateSwitch = FDCAN_BRS_ON,
    .FDFormat = FDCAN_FD_CAN,
    .TxEventFifoControl = FDCAN_NO_TX_EVENTS, // change to FDCAN_STORE_TX_EVENTS if you need to store info regarding transmitted messages
    .MessageMarker = 0 // also change this to a real address if you change fifo control
};

void writeMessage(uint16_t msgID, uint8_t destID, uint8_t data[], uint32_t len) {
    TxHeader.Identifier = (LOCAL_GR_ID << 20) | (msgID << 8) | destID;
    TxHeader.DataLength = len;

    if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, data) != HAL_OK) {
        Error_Handler();
    }
}
