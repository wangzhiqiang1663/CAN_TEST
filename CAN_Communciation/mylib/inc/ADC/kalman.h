#ifndef _KALMAN_H
#define _KALMAN_H

typedef struct
 {
	 //1.��������
	 float Q;   //���������������
	 float R;   //���������������������
	 
   //2.ϵͳ��������
	 int A;
	 int B;
	 int H;
	
	 //3.��������Լ��������
	 float X_forecast;
	 float P_forecast;
	 float X_estimate;
	 float P_estimate;
	 
	 //4.�����������
	 float K;
	 float I;
 }KalmanType;
 
 void KalmanfilterInit(void);
 float kalmanfilter(float x);
#endif
 
 
 
 
 
 