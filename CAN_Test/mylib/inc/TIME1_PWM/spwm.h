#ifndef _spwm_H
#define _spwm_H



#include "stm32f10x_lib.h"		//�������е�ͷ�ļ�
#include "config.h"

void TIM1_Config(void);
void SetMotorPWM(float pwm);
#endif

