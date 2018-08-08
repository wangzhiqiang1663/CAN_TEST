#include"gpio_bitset.h"
#include"stm32f10x_lib.h"		//�������е�ͷ�ļ�

#define GPIOA_ODR (GPIOA_BASE+0X0C)
#define GPIOA_IDR (GPIOA_BASE+0X08)

#define GPIOB_ODR (GPIOB_BASE+0X0C)
#define GPIOB_IDR (GPIOB_BASE+0X08)

#define GPIOC_ODR (GPIOC_BASE+0X0C)
#define GPIOC_IDR (GPIOC_BASE+0X08)

#define GPIOD_ODR (GPIOD_BASE+0X0C)
#define GPIOD_IDR (GPIOD_BASE+0X08)

#define GPIOE_ODR (GPIOE_BASE+0X0C)
#define GPIOE_IDR (GPIOE_BASE+0X08)

#define BitBand(Addr,BitNum)  (*((unsigned long *)((Addr&0xf0000000)+0x2000000+((Addr&0xfffff)<<5)+(BitNum<<2))))

#define PAout(n) BitBand(GPIOA_ODR,n)
#define PAin(n)  BitBand(GPIOA_IDR,n)

#define PBout(n) BitBand(GPIOB_ODR,n)
#define PBin(n)  BitBand(GPIOB_IDR,n)

#define PCout(n) BitBand(GPIOC_ODR,n)
#define PCin(n)  BitBand(GPIOC_IDR,n)

#define PDout(n) BitBand(GPIOD_ODR,n)
#define PDin(n)  BitBand(GPIOD_IDR,n)

#define PEout(n) BitBand(GPIOE_ODR,n)
#define PEin(n)  BitBand(GPIOE_IDR,n)


/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Main program.
* Input          : GPIO_Mode��GPIO_Mode_AIN = 0x0,		  // ģ������ ��
  	                               GPIO_Mode_IN_FLOATING = 0x04, // �������� ��
  	                               GPIO_Mode_IPD = 0x28,		  // �������� ��
  	                               GPIO_Mode_IPU = 0x48,		  // �������� ��
  	                               GPIO_Mode_Out_OD = 0x14,	// ��©��� ��
  	                               GPIO_Mode_Out_PP = 0x10,    // ������� ��
  	                               GPIO_Mode_AF_OD = 0x1C,		// ���ÿ�©��� ��
  	                               GPIO_Mode_AF_PP = 0x18		// ����������� ��
										GPIO_Speed:    GPIO_Speed_10MHz    , // �������ٶ�Ϊ10MHz ;
  	                               GPIO_Speed_2MHz, 	  // �������ٶ�Ϊ2MHz ;
  	                               GPIO_Speed_50MHz      // �������ٶ�Ϊ50MHz ;
*******************************************************************************/ 

//void GPIO_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}



