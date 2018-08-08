#include "reset.h"

/**********************************************************
** ������:All_GPIO_Config
** ��������: ���е�GPIO�����÷�������
** �������: ��
** �������: ��
***********************************************************/
void NVIC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO�ṹ��	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA��GPIOB��ʱ��

	//PA3����Ϊ�������룬��Ϊ�ⲿ�ж���3���ж���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**********************************************************
** ������: NVIC_Config
** ��������: �ж����ȼ�����������
** �������: ��
** �������: ��
***********************************************************/
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�������2	 
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;//�����ⲿ�ж�3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//ռ��ʽ���ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
 

}

/**********************************************************
** ������: EXTI_Config
** ��������:  �ⲿ�ж�����
** �������: ��
** �������: ��
***********************************************************/
void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);	//PA3��Ϊ�ⲿ�ж���3����
	EXTI_ClearITPendingBit(EXTI_Line3);	//���3�߱�־λ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//���ش���
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 //�������ϲ�����ʼ���ṹ��

	
}



void reset_Config(void)
{
	 MotorMsg.Encoder.flag=1;
	 NVIC_GPIO_Config();
   NVIC_Config();
	 EXTI_Config(); 
}

