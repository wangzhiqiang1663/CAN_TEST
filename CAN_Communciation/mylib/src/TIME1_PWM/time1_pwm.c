#include "time1_pwm.h"


/**********************************************************
** ������: TIM1_Config
** ��������:  ��ʱ��2����ΪPWM1���ģʽ
** �������: ��
** �������: ��
***********************************************************/
void TIM1_Config(void)
{
		TIM1_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����ṹ��
		TIM1_OCInitTypeDef  TIM_OCInitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
//	  TIM1_OCInitTypeDef  TIMI_OCInitStructure;
	//1.��ʱ����ʼ������
		TIM1_DeInit();
		TIM1_InternalClockConfig();

	//2.����ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOA�����ܸ���IOʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ��TIM1ʱ��
	//3.GPIOA��GPI0B����Ϊ����ʱ��1��PWM��1��ͨ�����ù��ܻ������
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//I/Oʱ��Ϊ50MHz
  	GPIO_Init(GPIOA, &GPIO_InitStructure);//��������ָ��������ʼ��GPIO�ṹ��
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
	//4.��ʱ����������,����PWM���Ƶ�ʣ�Prescaler/72M*Period=����
		TIM_TimeBaseStructure.TIM1_Period =2500-1;//����ֵΪ1000
		TIM_TimeBaseStructure.TIM1_Prescaler =1-1;//����Ƶ
		TIM_TimeBaseStructure.TIM1_ClockDivision = 0;//������Ƶ0
		TIM_TimeBaseStructure.TIM1_CounterMode = TIM_CounterMode_Up;//���ϼ���
		TIM_TimeBaseStructure.TIM1_RepetitionCounter=0;
		TIM1_TimeBaseInit(&TIM_TimeBaseStructure);
		
	   
		 
  //5.��ʱ�����ͨ�����ã�ע��ͨ�üĴ�����TIM_OutputNState�ȴ�N����
		TIM_OCInitStructure.TIM1_OCMode = TIM_OCMode_PWM1;//��ʱ������ΪPWM1ģʽ
		TIM_OCInitStructure.TIM1_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM1_OutputNState=TIM_OutputNState_Enable;  //ʹ�ܻ��������
		TIM_OCInitStructure.TIM1_Pulse =1250;//����ֵΪ1250
	  TIM_OCInitStructure.TIM1_OutputState = TIM1_OutputState_Enable;
    TIM_OCInitStructure.TIM1_OutputNState = TIM1_OutputNState_Enable;
		TIM_OCInitStructure.TIM1_OCPolarity = TIM1_OCPolarity_High;//TIM����Ƚϼ��Ը�
		TIM_OCInitStructure.TIM1_OCNPolarity =TIM1_OCNPolarity_High; 
    TIM_OCInitStructure.TIM1_OCIdleState = TIM1_OCIdleState_Reset;
    TIM_OCInitStructure.TIM1_OCNIdleState = TIM1_OCIdleState_Set;		
//		TIM1_OCInitStructure.TIM1_OCIdleState=TIM_OCIdleState_Set;    //���������״̬ 
//		TIM1_OCInitStructure.TIM1_OCNIdleState =TIM_OCNIdleState_Reset;  
			
	
		TIM1_OC1Init(&TIM_OCInitStructure); //����TIM_OCInitStruct��ָ���Ĳ�����ʼ��TIM1
    TIM1_OC1PreloadConfig(TIM_OCPreload_Enable); //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
		
		
   
//		TIM_OCInitStructure.TIM1_OCMode = TIM1_OCMode_PWM1;
//		TIM_OCInitStructure.TIM1_OutputState = TIM1_OutputState_Enable;
//		TIM_OCInitStructure.TIM1_OutputNState = TIM1_OutputNState_Enable;
//		TIM_OCInitStructure.TIM1_Pulse = 400;
//		TIM_OCInitStructure.TIM1_OCPolarity = TIM1_OCPolarity_Low;
//		TIM_OCInitStructure.TIM1_OCNPolarity = TIM1_OCNPolarity_Low;
//		TIM_OCInitStructure.TIM1_OCIdleState = TIM1_OCIdleState_Set;
//		TIM_OCInitStructure.TIM1_OCNIdleState = TIM1_OCIdleState_Reset;
//    TIM1_OC3Init(&TIM_OCInitStructure);
//		
//    TIM1_OC3PreloadConfig(TIM_OCPreload_Enable); //ʹ��TIM1��CCR3�ϵ�Ԥװ�ؼĴ���
	
		TIM1_ARRPreloadConfig(ENABLE);//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
		TIM1_CCxCmd(TIM1_Channel_1, ENABLE);
		TIM1_CCxNCmd(TIM1_Channel_1, ENABLE);
	
	
	
		
//		TIM1_CCxCmd(TIM1_Channel_3, ENABLE);
//		TIM1_CCxNCmd(TIM1_Channel_3, ENABLE);
    TIM1_Cmd(ENABLE);//ʹ�ܶ�ʱ��1   
		TIM1_CtrlPWMOutputs(ENABLE);      //PWM���ʹ�ܣ���time2��ͬ�������    
    
}


void SetMotorPWM(float pwm)
{   
	  pwm=(int)pwm+1250;
		TIM1->CCR1 = pwm;	
}
