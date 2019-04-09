
#include "app_cfg.h"
#include "check_string.h"
#include "../queue/queue.h"

bool check_string_init(check_str_t *ptCHK, uint8_t *pchString,byte_queue_t*ptFIFOin) 
{
    enum { 
        START 
    };
    if (ptCHK == NULL) {
        return false;
    }
    ptCHK->pchString = pchString;
    ptCHK->chState = START;
    ptCHK->ptFIFOin =ptFIFOin;
    return true;
}

fsm_rt_t check_string(check_str_t *ptCHK) 
{
    enum { 
        START, 
        CHECK_END, 
        READ_CHAR, 
        CHECK_WORLD 
    };
    check_str_t *ptThis = ptCHK;
    if (ptThis == NULL) {
        return fsm_rt_err;
    }
    switch (this.chState) {
        case START:
            this.chState = CHECK_END;
            // break;
        case CHECK_END:
            if (*this.pchString == '\0') {
                TASK_STR_RESET_FSM();
                return fsm_rt_cpl;
            } else {
                this.chState = READ_CHAR;
            }
            // break;
        case READ_CHAR:
            if (DEQUEUE_BYTE(this.ptFIFOin,&this.chCurrentByte)) {
                this.chState = CHECK_WORLD;
                // break;
            } else {
                break;
            }
        case CHECK_WORLD:
            if (*this.pchString == this.chCurrentByte) {
                this.pchString++;
                this.chState = CHECK_END;
            } else {
                TASK_STR_RESET_FSM();
            }
            break;
        default:
            return fsm_rt_err;
            break;
    }
    return fsm_rt_on_going;
}
