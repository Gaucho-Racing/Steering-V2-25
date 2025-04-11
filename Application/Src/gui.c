#include "gui.h"
#include "lvgl/lvgl.h"

const size_t SCREEN_WIDTH_PX = 800;
const size_t SCREEN_HEIGHT_PX = 480;

int32_t col_dsc[GRID_COLUMNS + 1];
int32_t row_dsc[GRID_ROWS + 1];

void initGrid(lv_obj_t* screen, lv_obj_t * cells[]) {
    for (size_t i = 0; i < GRID_COLUMNS; i++) {
        col_dsc[i] = SCREEN_WIDTH_PX / 2 / GRID_COLUMNS;
    }
    col_dsc[GRID_COLUMNS] = LV_GRID_TEMPLATE_LAST;

    for (size_t i = 0; i < GRID_ROWS; i++) {
        row_dsc[i] = SCREEN_HEIGHT_PX / 2 /  GRID_ROWS;
    }
    row_dsc[GRID_ROWS] = LV_GRID_TEMPLATE_LAST;

    lv_obj_t * grid = lv_obj_create(screen);
    lv_obj_set_size(grid, SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);
    lv_obj_center(grid);
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

    lv_obj_t * p_bg;

    for (size_t i = 0; i < GRID_ROWS * GRID_COLUMNS; i++) {
        p_bg = lv_obj_create(grid);
        cells[i] = p_bg;
        lv_obj_set_size(p_bg, 15, 15);

        lv_obj_set_style_bg_color(p_bg, lv_color_hex(0x00ff00), LV_PART_MAIN);
        lv_obj_center(p_bg);
        lv_obj_set_grid_cell(p_bg, LV_GRID_ALIGN_STRETCH, i % GRID_COLUMNS, 1, LV_GRID_ALIGN_STRETCH, i / GRID_COLUMNS, 1);
    }
}