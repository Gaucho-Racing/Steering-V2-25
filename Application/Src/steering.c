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

volatile IncomingData incomingData = {0};

SteeringStatusMsg constructStatus()
{
    SteeringStatusMsg data;

    data.CMEandTME = (globalEncoderPercentages.current << 4) | globalEncoderPercentages.torque;
    data.RMEandButtonMap = 0 |
      (globalEncoderPercentages.regen << 4) |
      (HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin) << 3) |
      (HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin) << 2) |
      (HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin) << 1) | 
      HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port, BUTTON_4_Pin);

    return data;
}
  
void sendStatus() {
    SteeringStatusMsg status = constructStatus();
    writeToECU(MSG_STEERING_STATUS, (uint8_t*)(&status), 4);
}

lv_obj_t* cells[160];

void initLVGL()
{
  /* Change Active Screen's background color */
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x00ff00), LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

  initGrid(lv_screen_active(), cells);

  //lv_obj_set_style_bg_color(cells[30], lv_color_hex(0xff0000), LV_PART_MAIN);
}
