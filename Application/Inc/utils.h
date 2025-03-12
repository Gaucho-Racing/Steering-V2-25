#include <stdint.h>

#ifndef UTILS_H
#define UTILS_H

#define TICK_FREQ 1000 // TODO: PLEASE CHECK, COPIED FROM ECU

uint32_t millis(void);
uint8_t getBit(uint8_t number, uint8_t indexFromLeft);
uint8_t getBits(uint8_t number, uint8_t indexFromLeft, uint8_t length);

#endif
