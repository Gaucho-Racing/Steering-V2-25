#include <stdint.h>

#ifndef ENCODERS_H
    #define ENCODERS_H

    typedef enum {
        ENC_CURRENT,
        ENC_TORQUE,
        ENC_REGEN,
    } Encoder;

    typedef struct {
        uint
    } encoderPercentages;

    uint16_t getStatus(Encoder encoder);
#endif
