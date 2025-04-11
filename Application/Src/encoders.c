#include <stdint.h>

#include "encoders.h"
#include "main.h"
#include "stm32u5xx_hal.h"

typedef struct {
    uint8_t current;
    uint8_t regen;
    uint8_t torque;
} EncoderPositions;

EncoderPositions percentage = {0};
EncoderPositions startingAbsolutePosition = {0};

uint16_t getStatus(Encoder encoder)
{
    uint8_t value = 0;
    switch(encoder) {
        case ENC_CURRENT:
            value = HAL_GPIO_ReadPin(CME_P1_GPIO_Port, CME_P1_Pin) | (HAL_GPIO_ReadPin(CME_P2_GPIO_Port, CME_P2_Pin) << 1) | (HAL_GPIO_ReadPin(CME_P3_GPIO_Port, CME_P3_Pin) << 2) | (HAL_GPIO_ReadPin(RME_P4_GPIO_Port, RME_P4_Pin) << 3);
        case ENC_REGEN:
            value = HAL_GPIO_ReadPin(RME_P1_GPIO_Port, RME_P1_Pin) | (HAL_GPIO_ReadPin(RME_P2_GPIO_Port, RME_P2_Pin) << 1) | (HAL_GPIO_ReadPin(RME_P3_GPIO_Port, RME_P3_Pin) << 2) | (HAL_GPIO_ReadPin(RME_P4_GPIO_Port, RME_P4_Pin) << 3);
        case ENC_TORQUE:
            value = HAL_GPIO_ReadPin(TME_P1_GPIO_Port, TME_P1_Pin) | (HAL_GPIO_ReadPin(TME_P2_GPIO_Port, TME_P2_Pin) << 1) | (HAL_GPIO_ReadPin(TME_P3_GPIO_Port, TME_P3_Pin) << 2) | (HAL_GPIO_ReadPin(TME_P4_GPIO_Port, TME_P4_Pin) << 3);
    }

    uint8_t sketchyPercentage = 0;

    switch (value) {
        case 0x0:   // 0 deg
            sketchyPercentage = 0;  // 00.0%
        case 0x4:   // 45 deg
            sketchyPercentage = 2;  // 13.3%
            break;
        case 0xC:   // 90 deg
            sketchyPercentage = 4;  // 26.6%
            break;
        case 0xE:   // 135 deg
            sketchyPercentage = 6;  // 40.0%
            break;
        case 0x6:   // 180 deg
            sketchyPercentage = 8;  // 53.3%
            break;
        case 0x7:   // 225 deg
            sketchyPercentage = 11; // 73.3%
            break;
        case 0x3:   // 270 deg
            sketchyPercentage = 13; // 86.6%
            break;
        case 0x2:   // 315 deg
            sketchyPercentage = 15; // 100%
            break;
    }
}
