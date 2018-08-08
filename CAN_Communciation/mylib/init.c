# include"init.h"


void all_init(void)
{
	    MotorMsg_InitConfig();
	    KalmanfilterInit();
	    PID_InitConfig();
	
      TIM1_Config();
	    Usart_Configuration();//���ڳ�ʼ������
	    Encoder_InitConfig();
	    ADC1_Config();
	
	    SetMotorPWM(0);
	    CurrentZeroPointConfirm();
     
	    /*********  Ѱ�����   *********/
//	    while(!MotorMsg.Encoder.flag)
//			{
//			SetMotorPWM(750);
//			}
			
	    TIM3_Start();
	    MotorMsg.Encoder.flag=0;
	    
}
