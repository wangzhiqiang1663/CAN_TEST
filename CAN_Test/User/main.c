/*Include---------------------------*/
#include "stm32f10x_lib.h"		//包含所有的头文件
#include "delay.h"
#include "can.h"
#include "usart.h"


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
	//----------使用外部RC晶振-----------
	RCC_DeInit();			//初始化为缺省值
	RCC_HSEConfig(RCC_HSE_ON);	//使能外部的高速时钟 
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);	//等待外部高速时钟使能就绪
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//Enable Prefetch Buffer
	FLASH_SetLatency(FLASH_Latency_2);		//Flash 2 wait state
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);		//HCLK = SYSCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);			//PCLK2 =  HCLK
	RCC_PCLK1Config(RCC_HCLK_Div2);			//PCLK1 = HCLK/2
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);	//PLLCLK = 8MHZ * 9 =72MHZ
	RCC_PLLCmd(ENABLE);			//Enable PLLCLK

	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	//Wait till PLLCLK is ready
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//Select PLL as system clock
	while(RCC_GetSYSCLKSource()!=0x08);		//Wait till PLL is used as system clock source
	
	//---------打开相应外设时钟--------------------
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);	//使能APB2外设的GPIOA的时钟		 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
//	//开启时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC,ENABLE);
}

 




/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
int  main(void)
{  

 
  u8 TransmitMailbox = 0;		/* 定义消息发送状态变量 */
	CanTxMsg TxMessage;			/* 定义消息发送结构体 */
	CanRxMsg RxMessage;			/* 定义消息接收结构体 */
	
	/* 设置系统时钟 */
  RCC_Configuration(); 
  delay_init(72);
	
	
	
	/* 设置 USART */
	Usart_Configuration();
	
	/* 设置 CAN 控制器 */
	CAN_Configuration();
	
	/* 配置发送数据结构体 ，标准ID格式 ，ID为0xAA，数据帧 ，数据长度为8个字节 */
	TxMessage.ExtId = 0XAAAA0000; 
//  TxMessage.ExtId = 0x3000A;
	TxMessage.RTR = CAN_RTR_DATA;     //传送数据帧
	TxMessage.IDE = CAN_ID_EXT;
//	TxMessage.IDE = CAN_ID_STD;       //说明是标准帧
	TxMessage.DLC = 8;                //长度为8个字节
	TxMessage.Data[0] = 0x00;
	TxMessage.Data[1] = 0x12;
	TxMessage.Data[2] = 0x34;
	TxMessage.Data[3] = 0x56;
	TxMessage.Data[4] = 0x78;
	TxMessage.Data[5] = 0xAB;
	TxMessage.Data[6] = 0xCD;
	TxMessage.Data[7] = 0xEF;	
	printf("\r\nThe CAN has send data: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x 0x%x 0x%x\r\n",
		   	TxMessage.Data[0], TxMessage.Data[1], TxMessage.Data[2],
			TxMessage.Data[3], TxMessage.Data[4], TxMessage.Data[5],
			TxMessage.Data[6], TxMessage.Data[7],TransmitMailbox,TxMessage.StdId,TxMessage.ExtId);
	/* 发送数据 */
	TransmitMailbox = CAN_Transmit(&TxMessage);
	/* 等待发送完成 */
	while((CAN_TransmitStatus(TransmitMailbox) != CANTXOK));
	
	printf("\r\nThe CAN has send data: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x 0x%x 0x%x\r\n",
		   	TxMessage.Data[0], TxMessage.Data[1], TxMessage.Data[2],
			TxMessage.Data[3], TxMessage.Data[4], TxMessage.Data[5],
			TxMessage.Data[6], TxMessage.Data[7],TransmitMailbox,TxMessage.StdId,TxMessage.ExtId);
	
	/* 等待接收完成 */
	while((CAN_MessagePending(CAN_FIFO0) == 0));	
	/* 初始化接收数据结构体 */
	RxMessage.ExtId = 0x000;
	RxMessage.IDE = CAN_ID_STD;
	RxMessage.DLC = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;
	
   	/* 接收数据 */
	CAN_Receive(CAN_FIFO0 , &RxMessage);
	
	printf("\r\nThe CAN has receive data: 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x 0x%x 0x%x\r\n",		   	
		    	RxMessage.Data[0], RxMessage.Data[1], RxMessage.Data[2],
				RxMessage.Data[3], RxMessage.Data[4], RxMessage.Data[5],
				RxMessage.Data[6], RxMessage.Data[7],RxMessage.StdId,RxMessage.ExtId );
	
	while(1);

	 }




