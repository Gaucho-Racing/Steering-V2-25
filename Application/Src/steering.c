#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl_port_display.h"
#include "msgIDs.h"
#include "CANdler.h"
#include "grIDs.h"
#include "steering.h"

volatile IncomingData incomingData = {0};

SteeringStatusMsg constructStatus() {
    SteeringStatusMsg data;
    data.buttonMap = 0 |
      (HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin) << 7) |
      (HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin) << 6) |
      (HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin) << 5) | 
      (HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port, BUTTON_4_Pin) << 4);
    // TODO: update encoder values for current, torque map, and regen encoders

    return data;
}
  
void sendStatus() {
    SteeringStatusMsg status = constructStatus();
    writeToECU(MSG_STEERING_STATUS, (uint8_t*)(&status), 4);
}

void initLVGL() {
  if (HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1) != HAL_OK) {
    /* PWM Generation Error */
    Error_Handler();
  }

  /* reset display */
  HAL_GPIO_WritePin(LCD_DISP_RESET_GPIO_Port, LCD_DISP_RESET_Pin, GPIO_PIN_SET);

  /* initialize LVGL framework */
  lv_init();

  /* initialize display and touchscreen */
  lvgl_display_init();
  
  /* Change Active Screen's background color */
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xff0000), LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

  // /* Create a spinner */
  // lv_obj_t * spinner = lv_spinner_create(lv_screen_active()/*, 1000, 60*/);
  // lv_obj_set_size(spinner, 64, 64);
  


  /*
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_radius(&style, 5);

  lv_style_set_width(&style, 150);
  lv_style_set_height(&style, LV_SIZE_CONTENT);

  lv_style_set_pad_ver(&style, 20);
  lv_style_set_pad_left(&style, 5);

  lv_style_set_x(&style, lv_pct(50));
  lv_style_set_y(&style, 80);

  lv_obj_t * obj = lv_obj_create(lv_scr_act());
  lv_obj_add_style(obj, &style, 0);

  lv_obj_t * label = lv_label_create(obj);
  lv_label_set_text(label, "Hello");

  */

  // lv_obj_t * flexCol1 = lv_obj_create(scr);
  // lv_obj_set_layout(flexCol1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexCol1, LV_FLEX_FLOW_COLUMN);

  // lv_obj_t * flexRow1 = lv_obj_create(flexCol1);
  // lv_obj_t * flexRow2 = lv_obj_create(flexCol1);
  // lv_obj_set_layout(flexRow1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow1, LV_FLEX_FLOW_ROW);
  // lv_obj_set_layout(flexRow2, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2, LV_FLEX_FLOW_ROW);

  // // Dummy screen test

  // lv_obj_t * label1 = lv_obj_create(flexRow1);
  // lv_obj_t * label2 = lv_obj_create(flexRow2);

  // lv_label_set_text(label1, "Skibidi toilet rizz.");
  // lv_label_set_text(label2, "Courtesy of Gaucho Racing");

  // Real code 

  /*
   * https://docs.lvgl.io/master/details/widgets/label.html - for changing label texts
   * https://forum.lvgl.io/t/backgroud-colour/2036 - for changing color
   * 
   * 
   * 
   * 
  */

  // Top Row

  // lv_obj_t * flexRow1Col1 = lv_obj_create(flexRow1);
  // lv_obj_set_layout(flexRow1Col1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow1Col1, LV_FLEX_FLOW_COLUMN);
  // lv_obj_t * flexRow1Col2 = lv_obj_create(flexRow1);
  // lv_obj_set_layout(flexRow1Col2, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow1Col2, LV_FLEX_FLOW_COLUMN);
  // lv_obj_t * flexRow1Col3 = lv_obj_create(flexRow1);
  // lv_obj_set_layout(flexRow1Col3, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow1Col3, LV_FLEX_FLOW_COLUMN);

  // // Bottom Row

  // lv_obj_t * flexRow2Col1 = lv_obj_create(flexRow2);
  // lv_obj_set_layout(flexRow2Col1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2Col1, LV_FLEX_FLOW_COLUMN);
  // lv_obj_t * flexRow2Row1 = lv_obj_create(flexRow2);
  // lv_obj_set_layout(flexRow2Row1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2Row1, LV_FLEX_FLOW_ROW);

  // // Power - voltage, SOC, and total power

  // lv_obj_t * voltageWidget = lv_obj_create(flexRow1Col1);
  // lv_obj_t * socWidget = lv_obj_create(flexRow1Col1);
  // lv_obj_t * totalPowerWidget = lv_obj_create(flexRow1Col1);

  // // Main - speed, state, and warning

  // lv_obj_t * speedWidget = lv_obj_create(flexRow1Col2);
  // lv_obj_t * stateWidget = lv_obj_create(flexRow1Col2);
  // lv_obj_t * warningWidget = lv_obj_create(flexRow1Col2);

  // // Dials 

  // lv_obj_t * regenEncoder = lv_obj_create(flexRow1Col3);
  // lv_obj_t * currentEncoder = lv_obj_create(flexRow1Col3);
  // lv_obj_t * torqueMapEncoder = lv_obj_create(flexRow1Col3);


  // // Car diagram

  // lv_obj_t * flexRow2Col1Row1 = lv_obj_create(flexRow2Col1);
  // lv_obj_set_layout(flexRow2Col1Row1, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2Col1Row1, LV_FLEX_FLOW_ROW);
  // lv_obj_t * flexRow2Col1Row2 = lv_obj_create(flexRow2Col1);
  // lv_obj_set_layout(flexRow2Col1Row2, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2Col1Row2, LV_FLEX_FLOW_ROW);
  // lv_obj_t * flexRow2Col1Row3 = lv_obj_create(flexRow2Col1);
  // lv_obj_set_layout(flexRow2Col1Row3, LV_LAYOUT_FLEX);
  // lv_obj_set_flex_flow(flexRow2Col1Row3, LV_FLEX_FLOW_ROW);

  // lv_obj_t * wheelFLWidget = lv_obj_create(flexRow2Col1Row1);
  // lv_obj_t * wheelFRWidget = lv_obj_create(flexRow2Col1Row1);
  // lv_obj_t * wheelRLWidget = lv_obj_create(flexRow2Col1Row3);
  // lv_obj_t * wheelRRWidget = lv_obj_create(flexRow2Col1Row3);

  // lv_obj_t * carDirectionWidget = lv_obj_create(flexRow2Col1Row2);

  // // Temperature, battery, inverter, motor, water coolant, tire, brake

  // lv_obj_t * batteryTempWidget = lv_obj_create(flexRow2Row1);
  // lv_obj_t * inverterTempWidget = lv_obj_create(flexRow2Row1);
  // lv_obj_t * motorTempWidget = lv_obj_create(flexRow2Row1);
  // lv_obj_t * waterCoolantTempWidget = lv_obj_create(flexRow2Row1);
  // lv_obj_t * tireTempWidget = lv_obj_create(flexRow2Row1);
  // lv_obj_t * brakeTempWidget = lv_obj_create(flexRow2Row1);
}