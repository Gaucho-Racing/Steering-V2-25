#include <stdint.h>

#include "lvgl/lvgl.h"
#include "steering.h"

#ifndef STEERING_GUI_H
    #define STEERING_GUI_H

    #define GRID_COLUMNS 10
    #define GRID_ROWS 10

    #define GRID_WIDTH_PX 600
    #define GRID_HEIGHT_PX 360

    // See Brand Guidelines
    #define GR_COLOR_PINK 0xEF0DA1
    #define GR_COLOR_PURPLE 0x7920FF
    #define GR_COLOR_NAVY 0x195297
    #define GR_COLOR_GRAY 0x9AA3B0
    #define GR_COLOR_WHITE 0xFFFFFF

    void updateCellVoltages(volatile IncomingACUCellData *cellData, LvglChart chart);
    LvglChart drawCellVoltages(volatile IncomingACUCellData *cellData, size_t dataLen, int32_t y);
    void initGrid(lv_obj_t* screen, lv_obj_t* cells[]);
    void initGrid2(lv_obj_t* screen);

    void buildDebug();
#endif
