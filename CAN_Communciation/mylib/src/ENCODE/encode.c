# include"encode.h"	

float pwm;
float n[2];

MotorMsgType MotorMsg;
Motor_Control_TIME MotorTime;


void Encoder_InitConfig(void)
{
  GPIO_InitTypeDef         GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef        TIM_ICInitStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
/***********************TIME2 ������ʱ������������������*********************************/
  TIM_DeInit(TIM2);	 
	TIM_InternalClockConfig(TIM2);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM2�ĸ��±�־λ
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//���и����ж�
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;           // �������ֵ65535    
  TIM_TimeBaseStructure.TIM_Prescaler =0;	            //����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //�����ؼ���
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;        
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
//  TIM3->ARR=30000;
//	TIM3->PSC=0;
//	TIM3->CCMR1|=1<<0;
//	TIM3->CCMR1|=1<<8;
//	TIM3->CCER|=0<<1;
//  TIM3->CCER|=0<<5;
//	TIM3->SMCR|=3<<0;
  TIM_SetCounter(TIM2,30000);  
//	TIM_SetAutoreload(TIM3,30000);
	TIM_ARRPreloadConfig(TIM2, ENABLE);//ʹ��TIM3��ARR�ϵ�Ԥװ�ؼĴ���
  TIM_Cmd(TIM2, ENABLE);  
	
	//TIM3����Ϊ1ms�Ķ�ʱ��
	TIM_TimeBaseStructure.TIM_Period = 10-1;          //��ʱ��Ƶ��Ϊ72MHZ����ƵΪ900����ʱ��2����Ƶ��Ϊ80K,����ֵΪ10����1/8K���1�Σ���0.125ms����һ��
	TIM_TimeBaseStructure.TIM_Prescaler =900-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�������2	 
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQChannel; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

}

void TIM3_Start(void)
{
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);	
	TIM_Cmd(TIM3, ENABLE);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}

void MotorMsg_InitConfig(void)
{
	MotorMsg.Current     = 0;
	MotorMsg.Encoder.Pos = 0;
	MotorMsg.Encoder.Vol = 0;
	
	MotorTime.P_TIME=0;
	MotorTime.I_TIME=0;
	MotorTime.N_TIME=0;
	MotorTime.N_number=0;
}

//�����źţ���������ʱ����8K��ת�ٻ�����ʱ��4K,λ�û�����ʱ����2K
void TIM3_Process(void)
{
//	  a++;
//	  f=(a>=40000)?-1:1;
	
	  MotorTime.P_TIME++;
	  MotorTime.N_TIME++;

	  if(MotorTime.N_TIME%2==0)	
		 {
			if(MotorTime.P_TIME%4==0)
			{
				MotorMsg.Encoder.Vol  = TIM2->CNT-30000-MotorTime.N_number;
				MotorTime.N_number=0;
			}
			else
			{
			  MotorMsg.Encoder.Vol  = TIM2->CNT-30000;
        MotorTime.N_number=TIM2->CNT-30000;
			}
			  MotorTime.N_TIME=0;
		 }
	  if(MotorTime.P_TIME%4==0)
		{ 
			  MotorMsg.Encoder.Pos += TIM2->CNT-30000;
			  MotorTime.P_TIME=0;
			  TIM2->CNT = 30000;
		}
		
//		MotorMsg.zero = Get_Current(0);
		MotorMsg.Current = Get_Current(1);

    PID_Motor_P.Measured = (float)MotorMsg.Encoder.Pos;
	  PID_Motor_V.Measured = (float)MotorMsg.Encoder.Vol;
	  PID_Motor_I.Measured = (float)MotorMsg.Current;

#ifdef P_V_I_CONTROL_MODE
	PID_Motor_P.Expect   = expect;
	PID_Motor_V.Expect   = PIDCalc(&PID_Motor_P);
	PID_Motor_I.Expect   = PIDCalc(&PID_Motor_V);
	pwm                  = PIDCalc(&PID_Motor_I);
#endif	
	
#ifdef P_V_CONTROL_MODE  
	PID_Motor_P.Expect   = expect;
	PID_Motor_V.Expect   = PIDCalc(&PID_Motor_P);
	pwm                  = PIDCalc(&PID_Motor_V);
#endif

#ifdef V_I_CONTROL_MODE
	PID_Motor_V.Expect   = expect;
	PID_Motor_I.Expect   = PIDCalc(&PID_Motor_V);
	pwm                  = PIDCalc(&PID_Motor_I);
#endif

#ifdef P_I_CONTROL_MODE
	PID_Motor_P.Expect   = expect;
	PID_Motor_I.Expect   = PIDCalc(&PID_Motor_P);
	pwm                  = PIDCalc(&PID_Motor_I);
#endif

#ifdef P_CONTROL_MODE
  PID_Motor_P.Expect   = expect;
	pwm                  = PIDCalc(&PID_Motor_P);
#endif

#ifdef V_CONTROL_MODE  
  PID_Motor_V.Expect   = expect;
	pwm                  = PIDCalc(&PID_Motor_V);
#endif

#ifdef I_CONTROL_MODE
	PID_Motor_I.Expect   = expect;
	pwm                  = PIDCalc(&PID_Motor_I);
#endif
	
    SetMotorPWM(pwm);

}
