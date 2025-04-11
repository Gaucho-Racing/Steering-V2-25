#include <stdint.h>

#ifndef ENCODERS_H
    #define ENCODERS_H

    typedef enum {
        ENC_CURRENT,
        ENC_TORQUE,
        ENC_REGEN,
    } Encoder;

    typedef struct {
        uint8_t current;
        uint8_t torque;
        uint8_t regen;
    } EncoderPercentages;

    extern volatile EncoderPercentages globalEncoderPercentages;

    uint16_t getStatus(Encoder encoder);
#endif
