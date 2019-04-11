
#include "app_cfg.h"
#include "print_string.h"
#include "../queue/queue.h"
#include "../utilities/arm/app_type.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define this (*ptThis)
#define TASK_STR_RESET_FSM()  \
    do {                      \
        this.chState = START; \
    } while (0)

bool print_string_init(print_str_t *ptPRN, uint8_t *pchString, byte_queue_t *ptFIFOout)
{
    enum {
        START
    };
    if (NULL == ptPRN) {
        return false;
    }
    ptPRN->pchString = pchString;
    ptPRN->ptFIFOout = ptFIFOout;
    ptPRN->chState = 0;
    return true;
}

fsm_rt_t print_string(print_str_t *ptPRN)
{
    enum {
        START,
        PRINT_CHECK,
        PRINT_STR
    };
    print_str_t *ptThis = ptPRN;
    if (ptPRN == NULL) {
        return fsm_rt_err;
    }
    switch (this.chState) {
        case START:
            this.chState = PRINT_CHECK;
            // break;
        case PRINT_CHECK:
            if (*this.pchString == '\0') {
                TASK_STR_RESET_FSM();
                return fsm_rt_cpl;
            } else {
                this.chState = PRINT_STR;
            }
            // break;
        case PRINT_STR:
            if (ENQUEUE_BYTE(this.ptFIFOout, *this.pchString)) {
                this.pchString++;
                this.chState = PRINT_CHECK;
            }
            break;
        default:
            return fsm_rt_err;
            break;
    }
    return fsm_rt_on_going;
}
