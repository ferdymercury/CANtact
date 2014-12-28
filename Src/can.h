#ifndef _CAN_H
#define _CAN_H

uint32_t can_init(void);
uint32_t can_tx(CanTxMsgTypeDef *tx_msg, uint32_t timeout);

#endif // _CAN_H
