#include <stdint.h>

#include "encoders.h"
#include "main.h"
#include "stm32u5xx_hal.h"

typedef struct {
    uint8_t power;
    uint8_t regen;
    uint8_t torque;
} EncoderPositions;

uint16_t getStatus(Encoder encoder)
{

}

void pollEncoderDials(void)
{
    if (HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin) == GPIO_PIN_SET) {
        
    }
}

uint16_t pollSpecificEncoderDial(Encoder encoder)
{
    switch(encoder) {
        case ENC_POWER:
            break;
        case ENC_REGEN:
            break;
        case ENC_TORQUE:
            break;
    }
    return 
}
