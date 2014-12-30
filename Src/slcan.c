#include "stm32f0xx_hal.h"
#include "slcan.h"

uint8_t slcan_parse_frame(char *buf, CanRxMsgTypeDef *frame) {
    uint8_t i = 0;
    uint8_t id_len, j;
    uint32_t tmp;

    for (j=0; j < SLCAN_MTU; j++) {
	buf[j] = '\0';
    }

    // add character for frame type
    if (frame->RTR == CAN_RTR_DATA) {
	buf[i] = 't';
    } else if (frame->RTR == CAN_RTR_REMOTE) {
	buf[i] = 'r';
    }

    // assume standard identifier
    id_len = SLCAN_STD_ID_LEN;
    tmp = frame->StdId;
    // check if extended
    if (frame->IDE == CAN_ID_EXT) {
	// convert first char to upper case for extended frame
	buf[i] -= 32;
	id_len = SLCAN_EXT_ID_LEN;
	tmp = frame->ExtId;
    }
    i++;

    // add identifier to buffer
    for(j=id_len; j > 0; j--) {
	// add nybble to buffer
	buf[j] = (tmp & 0xF);
	tmp = tmp >> 4;
	i++;
    }

    // add DLC to buffer
    buf[i++] = frame->DLC;

    // add data bytes
    for (j = 0; j < frame->DLC; j++) {
	buf[i++] = (frame->Data[j] >> 4);
	buf[i++] = (frame->Data[j] & 0x0F);
    }

    // convert to ASCII (2nd character to end)
    for (j = 1; j < i; j++) {
	if (buf[j] < 0xA) {
	    buf[j] += 0x30;
	} else {
	    buf[j] += 0x37;
	}
    }

    // add newline, null terminate
    buf[i++] = '\r';
    buf[i++] = '\n';
    buf[i++] = '\0';

    // return number of bytes in string
    return i;
}

void slcan_parse_str(CanTxMsgTypeDef *frame, char *buf, uint8_t len) {

    // convert from ASCII (2nd character to end)
    uint8_t i;
    for (i = 1; i < len-1; i++) {
	if (buf[i] < 'A') {
	    buf[i] -= 0x30;
	} else {
	    buf[i] -= 0x37;
	}
    }

    if (buf[0] == 't' || buf[0] == 'T') {
	frame->RTR = CAN_RTR_DATA;
    } else if (buf[0] == 'r' || buf[0] == 'R') {
	frame->RTR = CAN_RTR_REMOTE;
    } else {
	return;
    }

    if (buf[0] == 't' || buf[0] == 'r') {
	frame->IDE = CAN_ID_STD;
    } else if (buf[0] == 'T' || buf[0] == 'R') {
	frame->IDE = CAN_ID_EXT;
    } else {
	// error
	return;
    }

    uint8_t id_len = frame->IDE == CAN_ID_EXT ? SLCAN_EXT_ID_LEN : SLCAN_STD_ID_LEN;
    frame->StdId = 0;
    i = 1;
    while (i <= id_len) {
	frame->StdId += buf[i++];
	frame->StdId *= 16;
    }
    frame->StdId /= 16;

    frame->DLC = buf[i++];

    uint8_t j;
    for (j = 0; j < frame->DLC; j++) {
	frame->Data[j] = (buf[i] << 4) + buf[i+1];
	i += 2;
    }
}
