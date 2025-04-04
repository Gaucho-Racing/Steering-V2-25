#include <stdint.h>

#include "lvgl/lvgl.h"

#ifndef STEERING_GUI_H
#define STEERING_GUI_H

#define GRID_COLUMNS 16
#define GRID_ROWS 10

void initGrid(lv_obj_t* screen, lv_obj_t ** cells);

#endif