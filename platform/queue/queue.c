#include "app_cfg.h"
#include "queue.h"
#include <stdint.h>
#include <stdbool.h>
#define this (*ptThis)
bool enqueue_byte( void* pEnqueueByte,uint8_t chByte)
{
    byte_queue_t*ptThis=(byte_queue_t*)pEnqueueByte;
    if ((ptThis == NULL)||(is_byte_queue_full(ptThis))) {
        return false;
    }
    this.pchBuffer[this.hwTail] = chByte;
    this.hwTail++;
    if(this.hwTail>=this.hwSize){
        this.hwTail = 0;
    }
    this.hwLength++;
    return true;
    
}

bool dequeue_byte(void* pDequeueByte,uint8_t* pchByte)
{
    byte_queue_t*ptThis=(byte_queue_t*)pDequeueByte;
    if ((ptThis == NULL)||(is_byte_queue_empty(ptThis))) {
        return false;
    }
    *pchByte = this.pchBuffer[this.hwHead];
    this.hwHead++;
    if(this.hwHead>=this.hwSize){
        this.hwHead = 0;
    }
    this.hwLength--;
    return true;
}

bool is_byte_queue_full(byte_queue_t* ptThis)
{
    if (ptThis == NULL) {
        return false;
    }
    if ((this.hwTail == this.hwHead) && (this.hwLength)) {
        return true;
    }
    return false;
}

bool is_byte_queue_empty(byte_queue_t* ptThis)
{
    if (ptThis == NULL) {
        return false;
    }
    if ((this.hwTail == this.hwHead )&&(!this.hwLength)) {
            return true;
    }
    return false;
}

bool init_byte_queue(byte_queue_t* ptThis,uint8_t *pchBuffer,uint16_t hwSize)
{
    if ((ptThis == NULL)||(NULL==pchBuffer)||(0 == hwSize)) {
        return false;    
    } 
    this.hwHead = 0;
    this.hwTail = 0;
    this.pchBuffer = pchBuffer;
    this.hwSize = hwSize;
    this.hwLength = 0;
    return true;
    
}
