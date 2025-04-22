#include "gui.h"
#include "lvgl/lvgl.h"
#include "utils.h"
#include "steering.h"

const size_t SCREEN_WIDTH_PX = 800;
const size_t SCREEN_HEIGHT_PX = 480;

void initGrid2(lv_obj_t* screen) {
    LV_DRAW_BUF_DEFINE_STATIC(drawBuffer, GRID_WIDTH_PX, GRID_HEIGHT_PX, LV_COLOR_FORMAT_RGB565);
    LV_DRAW_BUF_INIT_STATIC(drawBuffer);

    lv_obj_t * canvas = lv_canvas_create(screen);
    lv_canvas_set_draw_buf(canvas, &drawBuffer);

    lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_COVER);
    lv_obj_center(canvas);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rectDesc;
    lv_draw_rect_dsc_init(&rectDesc);
    rectDesc.bg_color = lv_color_hex(0x00ff00);
    rectDesc.border_color = lv_color_hex(GR_COLOR_PURPLE);
    rectDesc.border_width = 3;
    rectDesc.radius = 5;

    lv_area_t coords = {10, 10, 200, 200};

    lv_draw_rect(&layer, &rectDesc, &coords);

    lv_canvas_finish_layer(canvas, &layer);
}

void initGrid(lv_obj_t* screen, lv_obj_t * cells[])
{

    lv_obj_t * p_bg;

    for (size_t i = 0; i < GRID_ROWS * GRID_COLUMNS; i++) {
        p_bg = lv_obj_create(screen);
        if (p_bg == 0) {
            lv_obj_set_style_bg_color(p_bg, lv_color_hex(0xff0000), LV_PART_MAIN);
            return;
        }
        cells[i] = p_bg;
        lv_obj_set_size(p_bg, 30, 30);

        lv_obj_set_pos(p_bg, 100 + (i%GRID_COLUMNS)*(GRID_WIDTH_PX / GRID_COLUMNS), 60 + (i / GRID_COLUMNS)*(GRID_HEIGHT_PX / GRID_ROWS));
        lv_obj_set_style_bg_color(p_bg, lv_color_hex(0x00ff00), LV_PART_MAIN);
    }

    // lv_obj_t * grid = lv_obj_create(screen);
    // lv_obj_set_size(grid, GRID_WIDTH_PX, GRID_HEIGHT_PX);
    // lv_obj_center(grid);
    // lv_obj_set_style_bg_color(grid, lv_color_hex(0x9AA3B0), LV_PART_MAIN);

    // lv_obj_t * p_bg;

    // const int32_t padding = lv_obj_get_style_pad_top(grid, LV_PART_MAIN);
    // for (size_t i = 0; i < GRID_ROWS * GRID_COLUMNS; i++) {
    //     p_bg = lv_obj_create(grid);
    //     cells[i] = p_bg;
    //     lv_obj_set_size(p_bg, 30, 30);

    //     lv_obj_set_pos(p_bg, (i%GRID_COLUMNS)*((GRID_WIDTH_PX - 2*padding) / GRID_COLUMNS), (i / GRID_COLUMNS)*((GRID_HEIGHT_PX - 2*padding) / GRID_ROWS));
    //     lv_obj_set_style_bg_color(p_bg, lv_color_hex(0x00ff00), LV_PART_MAIN);
    // }
}

static void draw_event_cb(lv_event_t * e)
{
    lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t * base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

    if(base_dsc->part != LV_PART_ITEMS) {
        return;
    }

    lv_draw_fill_dsc_t * fill_dsc = lv_draw_task_get_fill_dsc(draw_task);
    if(fill_dsc) {
        // lv_obj_t * chart = lv_event_get_target_obj(e);
        //int32_t * y_array = lv_chart_get_series_y_array(chart, lv_chart_get_series_next(chart, NULL));
        //int32_t v = y_array[base_dsc->id2];

        uint8_t ratio = (uint8_t)(50 * 255 / 100);
        fill_dsc->color = lv_color_mix(lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_RED), ratio);
    }
}

void updateCellVoltages(IncomingACUCellData *cellData, LvglChart chart) {
    lv_chart_set_next_value(chart.chart, chart.ser, 100);
    lv_chart_set_next_value(chart.chart, chart.ser, cellData[40].cellVoltage);
    uint32_t i;
    for(i = 2; i < chart.len; i++) {
        lv_chart_set_next_value(chart.chart, chart.ser, cellData[0].cellVoltage);
    }
}

void buildDebug() {
    lv_obj_t * panel = lv_obj_create(lv_screen_active());
    lv_obj_set_size(panel, 800, 70);
    lv_obj_center(panel);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x7920FF), LV_PART_MAIN);

    lv_obj_t * text = lv_label_create(panel);
    lv_label_set_text(text, "thanks a lot");
    lv_obj_center(text);
}

/**
 * Recolor the bars of a chart based on their value
 */
LvglChart drawCellVoltages(IncomingACUCellData *cellData, size_t dataLen, int32_t y)
{
    LV_UNUSED(y);

    /*Create a chart1*/
    lv_obj_t * chart = lv_chart_create(lv_screen_active());
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(chart, dataLen);
    lv_obj_set_style_pad_column(chart, 2, 0);
    lv_obj_set_size(chart, 260*3, 160);
    lv_obj_set_pos(chart, 0, 0);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_color_hex(0xff0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_flag(chart, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

    LvglChart c = {
        .chart = chart,
        .ser = ser,
        .len = dataLen,
    };

    updateCellVoltages(cellData, c);
    return c;
}
