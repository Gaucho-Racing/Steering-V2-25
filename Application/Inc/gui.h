#include <stdint.h>

#include "lvgl/lvgl.h"

#ifndef STEERING_GUI_H
    #define STEERING_GUI_H

    #define GRID_COLUMNS 9
    #define GRID_ROWS 9

    // See Brand Guidelines
    #define GR_COLOR_PINK 0xEF0DA1
    #define GR_COLOR_PURPLE 0x7920FF
    #define GR_COLOR_NAVY 0x195297
    #define GR_COLOR_GRAY 0x9AA3B0

    void initGrid(lv_obj_t* screen, lv_obj_t* cells[]);
#endif
