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

uint8_t getAbsolutePosition(Encoder encoder)
{
    uint8_t result = 0;
    switch(encoder) {
        case ENC_CURRENT:
            result = HAL_GPIO_ReadPin(TME_P1_GPIO_Port, TME_P1_Pin) | (HAL_GPIO_ReadPin(TME_P2_GPIO_Port, TME_P2_Pin) << 1)
            result += HAL_GPIO_ReadPin(TME_P3_GPIO_Port, TME_P3_Pin) << 2;
            result += HAL_GPIO_ReadPin(TME_P4_GPIO_Port, TME_P4_Pin) << 3;
            break;

        case ENC_REGEN:

            break;

        case ENC_TORQUE:

            break;
    }
}

uint16_t getStatus(Encoder encoder)
{
    
}
