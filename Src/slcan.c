#include "stm32f0xx_hal.h"
#include "slcan.h"

uint8_t slcan_parse_frame(char *buf, CanRxMsgTypeDef *frame) {
    uint8_t i = 0;
    uint8_t id_len, j;
    uint32_t tmp;

    for (j=0; j < SLCAN_MTU; j++) {
	buf[j] = '\0';
    }

    if (frame->RTR == CAN_RTR_DATA) {
	buf[i] = 't';
    } else if (frame->RTR == CAN_RTR_REMOTE) {
	buf[i] = 'r';
    }
    id_len = 3;
    if (frame->IDE == CAN_ID_EXT) {
	// convert first char to upper case for extended frame
	buf[i] -= 32;
	id_len = 6; //?
    }
    i++;

    tmp = frame->StdId;
    for(j=id_len; j > 0; j--) {
	// convert nybble to ASCII, add to buffer
	buf[j] = (tmp & 0xF) + 0x30;
	tmp = tmp >> 4;
	i++;
    }

    // add DLC
    buf[i++] = frame->DLC + 0x30;

    // add data bytes
    for (j = 0; j < frame->DLC; j++) {
	buf[i++] = (frame->Data[j] >> 4) + 0x30;
	buf[i++] = (frame->Data[j] & 0x0F) + 0x30;
    }

    buf[i++] = '\r';
    buf[i++] = '\n';
    buf[i++] = '\0';

    return i;
}

void slcan_parse_str(CanTxMsgTypeDef *frame, char *buf) {

}
