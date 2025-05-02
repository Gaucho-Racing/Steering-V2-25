/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port_display.h"
#include "main.h"
#include "ltdc.h"
#include "dma2d.h"
#include "stm32u5xx_hal_dma2d.h"
#include "cmsis_os2.h"

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_flush(lv_display_t *, const lv_area_t *, uint8_t *color_p);
static void disp_flush_complete(DMA2D_HandleTypeDef *);
static void throwaway(DMA2D_HandleTypeDef *);
static void disp_flush_wait(lv_display_t * disp);

/**********************
 *  STATIC VARIABLES
 **********************/

volatile bool flushed = true;
volatile lv_display_t *display;


volatile uint16_t buf_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_display_init(void)
{
  /* display initialization */
  ; /* display is already initialized by cubemx-generated code */

  /* display buffer initialization */
  // lv_disp_draw_buf_init (&disp_buf,
  //                        (void*) buf_1,
  //                        NULL,
  //                        MY_DISP_HOR_RES * MY_DISP_VER_RES);

  /* register the display in LVGL */
  // lv_disp_drv_init(&disp_drv);
  display = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
  lv_display_set_flush_cb(display, disp_flush);
  //lv_display_set_flush_wait_cb(display, disp_flush_wait);
  lv_display_set_buffers(display, buf_1, NULL, sizeof(buf_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

  /* set the resolution of the display */
  // disp_drv.hor_res = MY_DISP_HOR_RES;
  // disp_drv.ver_res = MY_DISP_VER_RES;

  /* set callback for display driver */
  // disp_drv.flush_cb = disp_flush;
  // disp_drv.full_refresh = 0;
  // disp_drv.direct_mode = 1;

  /* interrupt callback for DMA2D transfer */
  HAL_DMA2D_RegisterCallback(&hdma2d, HAL_DMA2D_TRANSFERCOMPLETE_CB_ID, throwaway);

  /* set a display buffer */
  // disp_drv.draw_buf = &disp_buf;

  /* finally register the driver */
  // lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void disp_flush(lv_display_t *drv, const lv_area_t *area, uint8_t *color_p)
{
  // TODO: update such that drv --> lv_display_t
  // TODO: update such that color_p --> uint8_t
  UNUSED(drv);
  flushed = false;

  lv_coord_t width = lv_area_get_width(area);
  lv_coord_t height = lv_area_get_height(area);

  DMA2D->CR = 0x0U << DMA2D_CR_MODE_Pos;
  DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;
  DMA2D->FGMAR = (uint32_t)color_p;
  DMA2D->FGOR = 0;
  DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;
  uint32_t test = hltdc.LayerCfg[0].FBStartAdress + 2 * (area->y1 * MY_DISP_HOR_RES + area->x1);
  DMA2D->OMAR = hltdc.LayerCfg[0].FBStartAdress + 2 * (area->y1 * MY_DISP_HOR_RES + area->x1);
  DMA2D->OOR = MY_DISP_HOR_RES - width;
  DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos);
  DMA2D->IFCR = 0x3FU;
  DMA2D->CR |= DMA2D_CR_TCIE;
  DMA2D->CR |= DMA2D_CR_START;

  osDelay(10);
  disp_flush_complete(&hdma2d);
}

static void disp_flush_wait(lv_display_t * disp) {
  while (!flushed) {
    osDelay(10);
  }
}

static void throwaway(DMA2D_HandleTypeDef *) {

}

static void disp_flush_complete(DMA2D_HandleTypeDef *hdma2d)
{
  //flushed = true;
  HAL_GPIO_WritePin(USR_LED_GPIO_Port, USR_LED_Pin, GPIO_PIN_SET);
  lv_display_flush_ready(display);
  // UNUSED(hdma2d);
  // TODO: remove unused
}
