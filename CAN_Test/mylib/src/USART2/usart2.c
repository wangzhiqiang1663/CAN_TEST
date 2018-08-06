#include"stm32f10x_lib.h"	
#include "delay.h"
#include "usart2.h"
#include "stdio.h"	 	 
#include "sim900a.h"	

//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void USART3_Init(u32 bound)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  USART_ClockInitTypeDef USART_ClockInitStructure;  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,ENABLE);
 	USART_DeInit(USART3);  //��λ������
	//USART2_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
  //USART3_RX	  PB11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	
	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	

}
//����3
void UART3SendByte(unsigned char SendData)
{	   
		USART_SendData(USART3,SendData);
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
} 
void UART3SendString(u8 *cmd)
{
	u16 i=0;	
	while(*(cmd+i)!=0)
	{
			UART3SendByte(*(cmd+i));i++;
	}
}

void UART3Sendshuju(u8 a[])
{
	u16 j=0;	
	while(a[j]!=0)
	{
			UART3SendByte(a[j]);j++;
	}
}
