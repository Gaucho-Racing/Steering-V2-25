#include <stdint.h>

#ifndef ENCODERS_H
    #define ENCODERS_H

    typedef enum {
        ENC_POWER,
        ENC_TORQUE,
        ENC_REGEN,
    } Encoder;

    uint16_t getStatus(Encoder encoder);
    void pollEncoderDials(void);
#endif
