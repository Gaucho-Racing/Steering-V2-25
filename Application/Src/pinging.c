#include <stdbool.h>

#include "pinging.h"
#include "fdcan.h"
#include "msgIDs.h"
#include "grIDs.h"
#include "utils.h"

const uint8_t pingIDs[] = {GR_ACU,
                           GR_GR_INVERTER_1,
                           GR_GR_INVERTER_2,
                           GR_GR_INVERTER_3,
                           GR_GR_INVERTER_4,
                           GR_FAN_CONTROLLER_1,
                           GR_FAN_CONTROLLER_2,
                           GR_FAN_CONTROLLER_3,
                           GR_FAN_CONTROLLER_4,
                           GR_DASH_PANEL,
                           GR_STEERING_WHEEL};

uint32_t pingTimes[PINGCOUNT] = {0};

static bool pingHasReturned[PINGCOUNT] = {false};

void pingSchedule(void)
{
    static uint32_t nextPingTime = 0;

    if(millis() < nextPingTime) {
        return;
    }

    // check for timed out pings
    for(int i = 0; i < PINGCOUNT; i++) {
        if(!pingHasReturned[i]) {
            pingTimes[i] = PINGTIMEOUT*(TICK_FREQ/1000);
            // FIXME IDK HOW WE WANT TO HANDLE THIS
        } else {
            // FIXME IDK HOW WE WANT TO HANDLE THIS
        }

        pingHasReturned[i] = false;
    }

    uint32_t tick = HAL_GetTick();
    writeMessage(1, MSG_PING, GR_ALL, (uint8_t *)&tick, sizeof(uint32_t));

    nextPingTime += PINGTIMEOUT;
}

void respondToPing(uint8_t destID, uint32_t timestamp) {
    for(int i = 0; i < PINGCOUNT; i++) {
        if(destID == pingIDs[i]){
            pingTimes[i] = HAL_GetTick() - timestamp;
            pingHasReturned[i] = true;
            return;
        }
    }
}
