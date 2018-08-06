#include"can.h"
#include "stm32f10x_lib.h"		//包含所有的头文件

/*******************************************************************************
* 函数名 		: CAN_Polling
* 函数描述    	: 设置CAN为环回收发模式
* 输入参数     	: 无
* 输出结果     	: 无
* 返回值       	: 无
*******************************************************************************/

void CAN_Configuration(void)
{
	 
	/* 定义 CAN 控制器和过滤器初始化结构体 */
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
  /* 定义 GPIO 初始化结构体 GPIO_InitStructure */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* CAN 寄存器复位 */
	CAN_DeInit();
	CAN_StructInit(&CAN_InitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap2_CAN, ENABLE);
	/* 设置 CAN 的 Rx(PA.11) 引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* 设置 CAN 的 Tx(PA.12) 引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* 	
	*	CAN 控制器初始化：
	*  
	*	失能时间触发通讯模式
	*	失能自动离线管理
	*	失能自动唤醒模式
	*	失能非自动重传输模式
	*	失能接收 FIFO 锁定模式
	*	失能发送 FIFO 优先级
	*	CAN 硬件工作在环回模式 
	*	重新同步跳跃宽度 1 个时间单位
	*	时间段 1 为 8 个时间单位
	*	时间段 2 为 7 个时间单位
	*	分频数为5  
	*/
	
	CAN_InitStructure.CAN_TTCM = DISABLE;  //设置使能或者失能时间触发方式，可以选择ENABLE或者DISABLE
	CAN_InitStructure.CAN_ABOM = DISABLE;  //用来失能或者使能自动离线管理
	CAN_InitStructure.CAN_AWUM = DISABLE;  //用来使能或者失能自动唤醒模式
	CAN_InitStructure.CAN_NART = DISABLE;  //用来使能或者失能非自动重传模式
	CAN_InitStructure.CAN_RFLM = DISABLE;  //用来失能或者使能FIFO锁定模式
	CAN_InitStructure.CAN_TXFP = DISABLE;  //用来失能或者使能发送FIFO 优先级
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;  //可以用来选择工作模式，共有四种工作模式
	/*   
   CAN_MODE                                      描述
	 CAN_Mode_Normal                               正常模式
	 CAN_Mode_Silent                               静默模式
   CAN_Mode_LoopBack                             环回模式
   CAN_Mode_Silent_LoopBack                      静默环回
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;       //计算时间 波特率=36M/(N*(1+TS1+TS2))
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler = 5;
	CAN_Init(&CAN_InitStructure);
	
	/* 	 
	*	CAN 过滤器初始化：
	*
	*	初始化过滤器 2
	*	标识符屏蔽位模式
	*	使用 1 个 32 位过滤器 
	*	过滤器标识符为 (0x00AA << 5)
	*	过滤器屏蔽标识符 0xFFFF
	*	过滤器 FIFO0 指向过滤器 0 
	*	使能过滤器 
	*/
	
	CAN_FilterInitStructure.CAN_FilterNumber = 0;         //指定初始化过滤器，提供了14个位宽可变的过滤器（0-13），由2个32位定时器
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;   //选择屏蔽位模式，一个寄存器是标识
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0xAAAA<<3;             // 11位的标识符是从第5位到第18位，所以需要左移5位
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffFF<<3;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
}