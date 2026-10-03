//
// Created by qjy on 2026/10/3.
//
#include "can_user.h"
CAN_RxHeaderTypeDef rx_header;
CAN_TxHeaderTypeDef tx_header;
uint32_t can_tx_mailbox;
CAN_FilterTypeDef can_filter_config;

CAN_TxHeaderTypeDef tx_header ={
    .StdId=0200，
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 8,
    .TransmitGlobalTime = DISABLE,
    
};