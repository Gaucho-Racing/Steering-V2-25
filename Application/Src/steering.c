#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl_port_display.h"
#include "msgIDs.h"
#include "CANdler.h"
#include "grIDs.h"
#include "steering.h"
#include "main.h"
#include "fdcan.h"
#include "stm32u5xx_hal.h"
#include "encoders.h"
#include "tim.h"
#include "gui.h"

// TODO Confirm scaling is appropriate (so far lgtm)
volatile OutgoingData outgoingData = {0};
volatile IncomingData incomingData = {0};
volatile bool isDataChanged = false;

void updatedDataRecieved(void)
{
    outgoingData.steeringStatusMsg.CMEandTME = (globalEncoderPercentages.current << 4) | globalEncoderPercentages.torque;
    incomingData.cellData[40].cellVoltage = 50;
    isDataChanged = true;

    // TODO: You have new data, update screen with stuff
}
