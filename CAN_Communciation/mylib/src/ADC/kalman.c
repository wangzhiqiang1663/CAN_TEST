# include "kalman.h"

 KalmanType Kalman;


 void KalmanfilterInit(void)
 {
	 Kalman.Q=1e-8;
	 Kalman.R=5.95e-5;
	 
	 Kalman.A=1;
	 Kalman.B=0;
	 Kalman.H=1;
	 
	 Kalman.X_estimate=0;
	 Kalman.P_estimate=0;
	 Kalman.P_forecast=0;
	 Kalman.X_forecast=0;
	 
	 Kalman.K=0;
	 Kalman.I=1;
 }
	
 float kalmanfilter(float x)
 {
   float y;
	 y=x;
	 //1.���Ԥ��ֵ�Լ�Ԥ��ֵ����ʵֵ֮������Э�������
	 Kalman.X_forecast=Kalman.A*Kalman.X_estimate+Kalman.B;
	 Kalman.P_forecast=Kalman.P_estimate+Kalman.Q;
	 
	 //2.�������¹��̣����㿨���������ù���ֵ
	 Kalman.K=Kalman.P_forecast/(Kalman.P_forecast+Kalman.R);
	 Kalman.X_estimate=Kalman.X_forecast+Kalman.K*(y-Kalman.X_forecast);
	 
	 //3.������ʵֵ�����ֵ֮���Э��������Ա��´�ʹ��
	 Kalman.P_estimate=(Kalman.I-Kalman.H*Kalman.K)*Kalman.P_forecast;
	 
	 return Kalman.X_estimate;
	 
 } 
 
 
 
 
 