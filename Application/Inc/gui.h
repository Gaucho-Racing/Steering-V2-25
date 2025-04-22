#include <stdint.h>

#include "lvgl/lvgl.h"
#include "steering.h"

#ifndef STEERING_GUI_H
#define STEERING_GUI_H

#define GRID_COLUMNS 10
#define GRID_ROWS 10

void initGrid(lv_obj_t* screen, lv_obj_t* cells[]);
void drawCellVoltages(IncomingACUCellData *cellData, size_t dataLen, int32_t y);

#endif