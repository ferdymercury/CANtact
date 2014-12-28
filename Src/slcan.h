#ifndef _SLCAN_H
#define _SLCAN_H

uint8_t slcan_parse_frame(char *buf, CanRxMsgTypeDef *frame);
void slcan_parse_str(CanTxMsgTypeDef *frame, char *buf);

/* maximum rx buffer len: extended CAN frame with timestamp */
#define SLCAN_MTU 30// (sizeof("T1111222281122334455667788EA5F\r")+1)

#endif // _SLCAN_H
