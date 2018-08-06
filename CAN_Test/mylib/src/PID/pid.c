#include "pid.h"

POS_PID_Struct PID_Motor_P;  //λ�û�
POS_PID_Struct PID_Motor_V;  //�ٶȻ�
POS_PID_Struct PID_Motor_I;  //������
POS_PID_Struct pid_config;  //������

void PIDStruct_Init(POS_PID_Struct *pid)
{
	
	 pid->P= 0;   // �������� ProportionalConst
   pid->I= 0;    // ���ֳ��� Integral ConstConst
	 pid->D= 0;
	 pid->Imax= 0;
	 
	 pid->SumErr= 0;
   pid->LastError= 0;     //Error[ k - 1 ]
	 pid->NowErr= 0;
	 
	 pid->Measured= 0;
	 pid->Expect= 0;
	 
	 pid->O_limitmax= 0;    // �趨�����ת�޷�ֵ
	 pid->OutPut= 0;
}
void PID_Param_Init(POS_PID_Struct *pid,\
	                  float p,float i,float d,\
										float im,float outputmax)
{
	pid->P = p;
	pid->I = i;
	pid->D = d;
	pid->Imax=im;
	pid->O_limitmax = outputmax;
}



void PID_InitConfig(void)
{
	PIDStruct_Init(&PID_Motor_P);
	PIDStruct_Init(&PID_Motor_V);
	PIDStruct_Init(&PID_Motor_I);



	#ifdef P_V_I_CONTROL_MODE
	  PID_Param_Init(&PID_Motor_P,0.001,0,0,0,50);  
		PID_Param_Init(&PID_Motor_V,1,0.1,0,2000,1000);
		PID_Param_Init(&PID_Motor_I,5,0.1,0,1500,2400); 
	#endif	
		
	#ifdef P_V_CONTROL_MODE      //������    
		PID_Param_Init(&PID_Motor_P,0.2,0,0,100,50);  
		PID_Param_Init(&PID_Motor_V,18,0.2,0,5000,2400);
	#endif

	#ifdef V_I_CONTROL_MODE
		PID_Param_Init(&PID_Motor_V,0.1,0.1,0,2000,1000);
		PID_Param_Init(&PID_Motor_I,0.1,0.1,0,3000,2400); 

	#endif
  
	#ifdef P_I_CONTROL_MODE      //������    
		PID_Param_Init(&PID_Motor_P,2,0,0,2000,1000);  
		PID_Param_Init(&PID_Motor_I,5,0.01,0,5000,2400);
	#endif
	
	#ifdef P_CONTROL_MODE
		PID_Param_Init(&PID_Motor_P,13,0,0.01,5000,1600); 
	#endif

	#ifdef V_CONTROL_MODE      //������
		PID_Param_Init(&PID_Motor_V,15,0.2,0,5000,2400);
	#endif

	#ifdef I_CONTROL_MODE   
		PID_Param_Init(&PID_Motor_I,0.1,0.1,0,2000,1600);
	#endif

}
 

 
  float PIDCalc (POS_PID_Struct *pid)     
{ 
		float Pout = 0,Iout = 0,Dout = 0;
	
	/*������*/
	pid->NowErr  = pid->Expect - pid->Measured;
	pid->SumErr += (pid->I == 0) ? 0 : pid->NowErr;
	
	/*P-I-D*/
	Pout = pid->P * pid->NowErr;
	Iout = pid->I * pid->SumErr;
	Dout = pid->D * (pid->NowErr - pid->LastError);
	
	/*�����޷�*/
	if (Iout >= pid->Imax)
	{
		pid->SumErr -= pid->NowErr; 
		Iout        = pid->Imax;
	}
	else if (Iout <= -pid->Imax)
	{
		pid->SumErr -= pid->NowErr;
		Iout        = -pid->Imax;
	}
	
	/*PID���*/
	pid->OutPut = Pout + Iout + Dout;
	
	/*����޷�*/
	if (pid->OutPut >= pid->O_limitmax) 
		pid->OutPut = pid->O_limitmax;
	else if (pid->OutPut<=-pid->O_limitmax)
	  pid->OutPut = -pid->O_limitmax;
	
	/*������*/
	pid->LastError = pid->NowErr;
	
	pid_config.LastError=	pid->LastError;
	pid_config.SumErr=pid->SumErr;
	pid_config.OutPut=Pout;
	return pid->OutPut;  
}
