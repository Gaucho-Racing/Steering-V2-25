#include "gui.h"
#include "lvgl/lvgl.h"
#include "utils.h"
#include "steering.h"
#include <math.h>

volatile LvglObjects lvglObjects = {0};

const size_t SCREEN_WIDTH_PX = 800;
const size_t SCREEN_HEIGHT_PX = 480;

LV_DRAW_BUF_DEFINE_STATIC(drawBuffer, GRID_WIDTH_PX, GRID_HEIGHT_PX, LV_COLOR_FORMAT_RGB565);

void initLVGL(void)
{
    /* Change Active Screen's background color */
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

    initCellChart((IncomingACUCellData*)incomingData.cellData, 24*4, 0);
    initGrid2(lv_screen_active());
    initDebugMsg();
    // lv_obj_set_style_bg_color(cells[30], lv_color_hex(0xff0000), LV_PART_MAIN);
}

int refreshScreen(void)
{
    updateCellVoltages((IncomingACUCellData*)incomingData.cellData);

    if (incomingData.debugMessage[0] != '\0') {
        lv_label_set_text_static(lvglObjects.label.text, (const char*)incomingData.debugMessage);
        lv_obj_clear_flag(lvglObjects.label.panel, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(lvglObjects.label.panel, LV_OBJ_FLAG_HIDDEN);
    }

    lv_layer_t layer;
    lv_canvas_init_layer(lvglObjects.canvas, &layer);

    lv_draw_rect_dsc_t rectDesc;
    lv_draw_rect_dsc_init(&rectDesc);
    rectDesc.bg_color = lv_color_hex(0x00ff00);
    rectDesc.border_color = lv_color_hex(GR_COLOR_PURPLE);
    rectDesc.border_width = 3;
    rectDesc.radius = 5;

    lv_area_t coords = {0, 0, 200, 200};

    lv_draw_rect(&layer, &rectDesc, &coords);

    lv_canvas_finish_layer(lvglObjects.canvas, &layer);
    return 1;
}

void initGrid2(lv_obj_t* screen)
{
    LV_DRAW_BUF_INIT_STATIC(drawBuffer);

    lvglObjects.canvas = lv_canvas_create(screen);
    lv_obj_set_size(lvglObjects.canvas, GRID_WIDTH_PX, GRID_HEIGHT_PX);
    lv_canvas_set_draw_buf(lvglObjects.canvas, &drawBuffer);

    lv_canvas_fill_bg(lvglObjects.canvas, lv_color_hex(0xff00ff), LV_OPA_COVER);
    lv_obj_center(lvglObjects.canvas);
}

double k = 0;

void updateCellVoltages(IncomingACUCellData *cellData)
{
    LV_UNUSED(cellData);

    k += 1./96.;
    uint32_t i;
    for(i = 0; i < 20; i++) {
        lv_chart_set_next_value(lvglObjects.chart.chart, lvglObjects.chart.ser, (int) ((sin(k + (double) i / (double) lvglObjects.chart.len ) + 1.) * 50.));
    }
}

void initDebugMsg()
{
    lvglObjects.label.panel = lv_obj_create(lv_screen_active());
    lv_obj_set_size(lvglObjects.label.panel, 800, 70);
    lv_obj_center(lvglObjects.label.panel);
    lv_obj_set_style_bg_color(lvglObjects.label.panel, lv_color_hex(0x7920FF), LV_PART_MAIN);
    lv_obj_add_flag(lvglObjects.label.panel, LV_OBJ_FLAG_HIDDEN);

    lvglObjects.label.text = lv_label_create(lvglObjects.label.panel);
    lv_label_set_text(lvglObjects.label.text, "");
    lv_obj_center(lvglObjects.label.text);
}

void initCellChart(IncomingACUCellData *cellData, size_t dataLen, int32_t y)
{

    LV_UNUSED(y);

    /*Create a chart1*/
    lv_obj_t * chart = lv_chart_create(lv_screen_active());
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(chart, dataLen);
    lv_obj_set_style_pad_column(chart, 2, 0);
    lv_obj_set_size(chart, 260*3, 160);
    lv_obj_set_pos(chart, 0, 200);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_color_hex(0xff0000), LV_CHART_AXIS_PRIMARY_Y);
    //lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_flag(chart, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

    lvglObjects.chart.chart = chart;
    lvglObjects.chart.ser = ser;
    lvglObjects.chart.len = dataLen;

    updateCellVoltages(cellData);
}
