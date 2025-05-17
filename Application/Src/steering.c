#include <string.h>

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
volatile LvglChart chart = {0};
volatile bool isDataChanged = false;

void updatedDataRecieved(void)
{
    outgoingData.steeringStatusMsg.CMEandTME = (globalEncoderPercentages.current << 4) | globalEncoderPercentages.torque;
    incomingData.cellData[40].cellVoltage = 50;
    isDataChanged = true;

    // TODO: You have new data, update screen with stuff
}

void initLVGL(void)
{
    strncpy((char*)incomingData.debugMessage, "Booting -> No data recieved yet", 32);

    /* Change Active Screen's background color */
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

    chart = drawCellVoltages(incomingData.cellData, 24*4, 0);

    // lv_obj_set_style_bg_color(cells[30], lv_color_hex(0xff0000), LV_PART_MAIN);
}
