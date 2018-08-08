#ifndef    _CAN_H
#define    _CAN_H
#include "stm32f10x_lib.h"


#define CAN_ID 0x0005 //设定CAN过滤器标准帧ID

void CAN_Configuration(void);
void SendCan(u8 *Transdata,u32 id);
void Init_RxMes(CanRxMsg *RxMessage);
void All_Init(void);
void NVIC_Configuration(void);
#endif



