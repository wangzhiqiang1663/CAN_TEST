/*Include---------------------------*/

#include "delay.h"
#include "can.h"
#include "usart.h"

extern u8 flag;//数据接收标志
extern u8 jieshou[8];//存放接收到的数据
u8 a=0;

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

//	CanRxMsg RxMessage;			/* 定义消息接收结构体 */

	/* 设置系统时钟 */
  RCC_Configuration(); 
  delay_init(72);
	
	/* 设置 USART */
	Usart_Configuration();
	/* 设置 CAN 控制器 */
  All_Init();
  flag=1;
  while(1)
  {	 
  	if(flag==1)	//如果接收到数据
	 {
		flag=0;
		if(a==0)
		{
	  		SendCan("12345678",0x9104); //发送8字节长度字符串
		 	a=1;
		}
		else 
		{
			  SendCan("abcdefgh",0x9104);
		 	a=0;
		}
		  printf("%d\r\n",a); 
		 
	 }
	 
  }
 
 }




