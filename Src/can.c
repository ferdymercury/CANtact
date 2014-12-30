#include "stm32f0xx_hal.h"

CAN_HandleTypeDef hcan;

void can_init(void) {
    uint32_t status;
    CAN_FilterConfTypeDef filter;

    filter.FilterIdHigh = 0;
    filter.FilterIdLow = 0;
    filter.FilterMaskIdHigh = 0;
    filter.FilterMaskIdLow = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterNumber = 0;
    filter.FilterFIFOAssignment = CAN_FIFO0;
    filter.BankNumber = 0;
    filter.FilterActivation = ENABLE;

    hcan.Instance = CAN;
    hcan.Init.Prescaler = 12;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SJW = CAN_SJW_1TQ;
    hcan.Init.BS1 = CAN_BS1_4TQ;
    hcan.Init.BS2 = CAN_BS2_3TQ;
    hcan.Init.TTCM = DISABLE;
    hcan.Init.ABOM = DISABLE;
    hcan.Init.AWUM = DISABLE;
    hcan.Init.NART = DISABLE;
    hcan.Init.RFLM = DISABLE;
    hcan.Init.TXFP = DISABLE;

    status = HAL_CAN_Init(&hcan);
    status = HAL_CAN_ConfigFilter(&hcan, &filter);
}

uint32_t can_tx(CanTxMsgTypeDef *tx_msg, uint32_t timeout) {
    uint32_t status;

    // transmit can frame
    hcan.pTxMsg = tx_msg;
    status = HAL_CAN_Transmit(&hcan, timeout);

    return status;
}

uint32_t can_rx(CanRxMsgTypeDef *rx_msg, uint32_t timeout) {
    uint32_t status;

    hcan.pRxMsg = rx_msg;

    status = HAL_CAN_Receive(&hcan, CAN_FIFO0, timeout);

    return status;
}

uint8_t is_can_msg_pending(uint8_t fifo) {
    return (__HAL_CAN_MSG_PENDING(&hcan, fifo) > 0);
}
