/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_tim.h
* Author             : MCD Application Team
* Version            : V2.0
* Date               : 05/23/2008
* Description        : This file contains all the functions prototypes for the 
*                      TIM firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_TIM_H
#define __STM32F10x_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/

/* TIM Time Base Init structure definition */
typedef struct
{
 /* Set the Prescaler value */
//  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
  u16 TIM_Prescaler;	// ������������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ�� 
  u16 TIM_CounterMode;	// ѡ���˼�����ģʽ��
  /*Set the Autoreload value*/ 	
 // TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ; //	   �Զ���װ�ؼĴ���(TIMx_ARR)
 //ARR[15:0]: �Զ���װ�ص�ֵ
//ARR�ǽ�Ҫװ����ʵ�ʵ��Զ���װ�ؼĴ�������ֵ��	��ϸ�ο�13.4.1��ʱ����Ԫ�й�ARR�ĸ��ºͶ�����

  u16 TIM_Period;  // ����������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ ;	                          
  u16 TIM_ClockDivision;  // ������ʱ�ӷָ
  u8 TIM_RepetitionCounter;	// ���������ڼ�����ֵ��
} TIM_TimeBaseInitTypeDef;

/* TIM Output Compare Init structure definition */
typedef struct
{
  u16 TIM_OCMode;  // ѡ��ʱ��ģʽ��
  u16 TIM_OutputState;	// ѡ������Ƚ�״̬��
  u16 TIM_OutputNState;	//	ѡ�񻥲�����Ƚ�״̬��
  u16 TIM_Pulse;  // �����˴�װ�벶��ȽϼĴ���������ֵ��
  u16 TIM_OCPolarity;  // ������ԡ�
  u16 TIM_OCNPolarity; // ����������� ��
  u16 TIM_OCIdleState; // ѡ�����״̬�µķǹ���״̬ ��
  u16 TIM_OCNIdleState; // ѡ�����״̬�µķǹ���״̬ ��

  u16 TIM_Channel;	// ѡ��ͨ�� ��
} TIM_OCInitTypeDef;

/* TIM Input Capture Init structure definition */
typedef struct
{
  u16 TIM_Channel;	// ѡ��ͨ�� ��
  u16 TIM_ICPolarity;  // �����ء�
  u16 TIM_ICSelection; // ѡ������ ��
  u16 TIM_ICPrescaler; // �������벶��Ԥ��Ƶ���� ��
  u16 TIM_ICFilter;	 // ѡ������Ƚ��˲��� ��
} TIM_ICInitTypeDef;

/* BDTR structure definition */
typedef struct
{
  u16 TIM_OSSRState; // ����������ģʽ�·ǹ���״̬ѡ�� ��
  u16 TIM_OSSIState; // ����������ģʽ�·ǹ���״̬ѡ�� ��
  u16 TIM_LOCKLevel; // ����������ƽ���� ��
  u16 TIM_DeadTime;	 // ָ��������򿪺͹ر�״̬֮�����ʱ��
  u16 TIM_Break;	// ʹ�ܻ���ʧ��TIM1ɲ�����롣
  u16 TIM_BreakPolarity; // ����TIM1ɲ������ܽż��ԡ�
  u16 TIM_AutomaticOutput; // ʹ�ܻ���ʧ���Զ�������ܸò���ȡֵ ��
} TIM_BDTRInitTypeDef;

/* Exported constants --------------------------------------------------------*/                             

#define IS_TIM_ALL_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == TIM1_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM2_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM3_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM4_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM5_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM6_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM7_BASE) || \
                                   ((*(u32*)&(PERIPH)) == TIM8_BASE))

#define IS_TIM_18_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == TIM1_BASE) || \
                                  ((*(u32*)&(PERIPH)) == TIM8_BASE))

#define IS_TIM_123458_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == TIM1_BASE) || \
                                      ((*(u32*)&(PERIPH)) == TIM2_BASE) || \
                                      ((*(u32*)&(PERIPH)) == TIM3_BASE) || \
                                      ((*(u32*)&(PERIPH)) == TIM4_BASE) || \
                                      ((*(u32*)&(PERIPH)) == TIM5_BASE) || \
                                      ((*(u32*)&(PERIPH)) == TIM8_BASE))

/* TIM Output Compare and PWM modes -----------------------------------------*/
//λ6:4  0C1M[2:0]������Ƚ�1ģʽ  
#define TIM_OCMode_Timing                  ((u16)0x0000)    // TIM����Ƚ�ʱ��ģʽ ��
#define TIM_OCMode_Active                  ((u16)0x0010)    // TIM����Ƚ�����ģʽ ��
//1(TIMx_CCR1)��ͬʱ��ǿ��OC1REFΪ�ߡ�

#define TIM_OCMode_Inactive                ((u16)0x0020)   // TIM����ȽϷ�����ģʽ ��
#define TIM_OCMode_Toggle                  ((u16)0x0030)   // TIM����Ƚϴ���ģʽ ��
#define TIM_OCMode_PWM1                    ((u16)0x0060)   // TIM�����ȵ���ģʽ1 ��
#define TIM_OCMode_PWM2                    ((u16)0x0070)   // TIM�����ȵ���ģʽ2 ��

#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))

#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/* TIM One Pulse Mode -------------------------------------------------------*/
#define TIM_OPMode_Single                  ((u16)0x0008) //	���ɵ�һ�����壺����������һ�������¼�ֹͣ ;
#define TIM_OPMode_Repetitive              ((u16)0x0000) //	�����ظ������壺�ڸ����¼�ʱ��������ֹͣ ;

#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))

/* TIM Channel -------------------------------------------------------------*/
#define TIM_Channel_1                      ((u16)0x0000) // ʹ��TIMͨ��1 ��
#define TIM_Channel_2                      ((u16)0x0004) // ʹ��TIMͨ��2 ��
#define TIM_Channel_3                      ((u16)0x0008) // ʹ��TIMͨ��3 ��
#define TIM_Channel_4                      ((u16)0x000C) // ʹ��TIMͨ��4 ��

#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))

#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))

#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
/* TIM Clock Division CKD --------------------------------------------------*/
#define TIM_CKD_DIV1                       ((u16)0x0000) // TDTS = Tck_TIM ��
#define TIM_CKD_DIV2                       ((u16)0x0100) // TDTS = Tck_2TIM ��
#define TIM_CKD_DIV4                       ((u16)0x0200) // TDTS = Tck_4TIM ��

#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))

/* TIM Counter Mode --------------------------------------------------------*/
#define TIM_CounterMode_Up                 ((u16)0x0000) // TIM���ϼ���ģʽ ;
#define TIM_CounterMode_Down               ((u16)0x0010) // TIM���¼���ģʽ ��
#define TIM_CounterMode_CenterAligned1     ((u16)0x0020) //	TIM�������ģʽ1����ģʽ ��
#define TIM_CounterMode_CenterAligned2     ((u16)0x0040) //	TIM�������ģʽ2����ģʽ ��
#define TIM_CounterMode_CenterAligned3     ((u16)0x0060) //	TIM�������ģʽ3����ģʽ ��

#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))

/* TIM Output Compare Polarity ---------------------------------------------*/
#define TIM_OCPolarity_High                ((u16)0x0000) // TIM����Ƚϼ��Ը� ��
#define TIM_OCPolarity_Low                 ((u16)0x0002) // TIM����Ƚϼ��Ե� ��

#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))

/* TIM Output Compare N Polarity -------------------------------------------*/
#define TIM_OCNPolarity_High               ((u16)0x0000) //	TIM����Ƚ�N���Ը� ��
#define TIM_OCNPolarity_Low                ((u16)0x0008) //	TIM����Ƚ�N���Ե� ��

#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))

/* TIM Output Compare states -----------------------------------------------*/
#define TIM_OutputState_Disable            ((u16)0x0000) // ʧ������Ƚ�״̬ ��
#define TIM_OutputState_Enable             ((u16)0x0001) // ʹ������Ƚ�״̬ ��

#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))

/* TIM Output Compare N States ---------------------------------------------*/
#define TIM_OutputNState_Disable           ((u16)0x0000) //	ʧ������Ƚ�N״̬ ��
#define TIM_OutputNState_Enable            ((u16)0x0004) //	ʹ������Ƚ�N״̬ ��

#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))

/* TIM Capture Compare States -----------------------------------------------*/
#define TIM_CCx_Enable                      ((u16)0x0001)
#define TIM_CCx_Disable                     ((u16)0x0000)

#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))

/* TIM Capture Compare N States --------------------------------------------*/
#define TIM_CCxN_Enable                     ((u16)0x0004)
#define TIM_CCxN_Disable                    ((u16)0x0000)                                     

#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))

/* Break Input enable/disable -----------------------------------------------*/
#define TIM_Break_Enable                   ((u16)0x1000) // ʹ��TIMɲ������ ��
#define TIM_Break_Disable                  ((u16)0x0000) // ʧ��TIMɲ������ ��

#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))

/* Break Polarity -----------------------------------------------------------*/
#define TIM_BreakPolarity_Low              ((u16)0x0000) // TIMɲ������ܽż��Ե� ��
#define TIM_BreakPolarity_High             ((u16)0x2000) // TIMɲ������ܽż��Ը� ��

#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))

/* TIM AOE Bit Set/Reset ---------------------------------------------------*/
#define TIM_AutomaticOutput_Enable         ((u16)0x4000) // �Զ��������ʹ�� �� 
#define TIM_AutomaticOutput_Disable        ((u16)0x0000) // �Զ��������ʧ�� ��

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/* Lock levels --------------------------------------------------------------*/
#define TIM_LOCKLevel_OFF                  ((u16)0x0000) // �����κ�λ ��
#define TIM_LOCKLevel_1                    ((u16)0x0100) //	ʹ������ƽ1 ��
#define TIM_LOCKLevel_2                    ((u16)0x0200) //	ʹ������ƽ2 ��
#define TIM_LOCKLevel_3                    ((u16)0x0300) //	ʹ������ƽ3 ��

#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))

/* OSSI: Off-State Selection for Idle mode states ---------------------------*/
#define TIM_OSSIState_Enable               ((u16)0x0400) // ʹ��TIM OSSI״̬ ��
#define TIM_OSSIState_Disable              ((u16)0x0000) // ʧ��TIM OSSI״̬ ��

#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))

/* OSSR: Off-State Selection for Run mode states ----------------------------*/
#define TIM_OSSRState_Enable               ((u16)0x0800) // ʹ��TIM OSSR״̬ ��
#define TIM_OSSRState_Disable              ((u16)0x0000) // ʧ��TIM OSSR״̬ ��

#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))

/* TIM Output Compare Idle State -------------------------------------------*/
#define TIM_OCIdleState_Set                ((u16)0x0100)
#define TIM_OCIdleState_Reset              ((u16)0x0000) // ��MOE=0����TIM����ȽϿ���״̬

#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))

/* TIM Output Compare N Idle State -----------------------------------------*/
#define TIM_OCNIdleState_Set               ((u16)0x0200)
#define TIM_OCNIdleState_Reset             ((u16)0x0000) // ��MOE=0����TIM����Ƚ�N����״̬ ��

#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))

/* TIM Input Capture Polarity ----------------------------------------------*/
#define  TIM_ICPolarity_Rising             ((u16)0x0000) // TIM���벶�������� ��
#define  TIM_ICPolarity_Falling            ((u16)0x0002) // TIM���벶���½��� ��

#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling))

/* TIM Input Capture Selection ---------------------------------------------*/
#define TIM_ICSelection_DirectTI           ((u16)0x0001) // TIM1����2��3��4ѡ���Ӧ����IC1��IC2��IC3��IC4���� ��
#define TIM_ICSelection_IndirectTI         ((u16)0x0002) // TIM1����2��3��4ѡ���Ӧ����IC2��IC1��IC4��IC3���� ��
#define TIM_ICSelection_TRC                ((u16)0x0003) // TIM1����2��3��4ѡ����TRC���� ��

#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))

/* TIM Input Capture Prescaler ---------------------------------------------*/
#define TIM_ICPSC_DIV1                     ((u16)0x0000) // TIM�����ڲ���������ÿ̽�⵽һ������ִ��һ�� ��
#define TIM_ICPSC_DIV2                     ((u16)0x0004) // TIM����ÿ2���¼�ִ��һ�� ��
#define TIM_ICPSC_DIV4                     ((u16)0x0008) // TIM����ÿ3���¼�ִ��һ�� ��
#define TIM_ICPSC_DIV8                     ((u16)0x000C) // TIM����ÿ4���¼�ִ��һ�� ��

#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))                                          

/* TIM interrupt sources ---------------------------------------------------*/
#define TIM_IT_Update                      ((u16)0x0001) // TIM�ж�Դ ��
#define TIM_IT_CC1                         ((u16)0x0002) // TIM����/�Ƚ�1�ж�Դ ��
#define TIM_IT_CC2                         ((u16)0x0004) // TIM����/�Ƚ�2�ж�Դ ��
#define TIM_IT_CC3                         ((u16)0x0008) // TIM����/�Ƚ�3�ж�Դ ��
#define TIM_IT_CC4                         ((u16)0x0010) // TIM����/�Ƚ�4�ж�Դ ��
#define TIM_IT_COM                         ((u16)0x0020) //	TIM COM�ж�Դ ��
#define TIM_IT_Trigger                     ((u16)0x0040) // TIM�����ж�Դ ��
#define TIM_IT_Break                       ((u16)0x0080) //	TIMɲ���ж�Դ ��

#define IS_TIM_IT(IT) ((((IT) & (u16)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_PERIPH_IT(PERIPH, TIM_IT) ((((((*(u32*)&(PERIPH)) == TIM2_BASE) || (((*(u32*)&(PERIPH)) == TIM3_BASE))||\
                                            (((*(u32*)&(PERIPH)) == TIM4_BASE)) || (((*(u32*)&(PERIPH)) == TIM5_BASE))))&& \
                                            (((TIM_IT) & (u16)0xFFA0) == 0x0000) && ((TIM_IT) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM1_BASE) || (((*(u32*)&(PERIPH)) == TIM8_BASE))))&& \
                                            (((TIM_IT) & (u16)0xFF00) == 0x0000) && ((TIM_IT) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM6_BASE) || (((*(u32*)&(PERIPH)) == TIM7_BASE))))&& \
                                            (((TIM_IT) & (u16)0xFFFE) == 0x0000) && ((TIM_IT) != 0x0000)))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))

/* TIM DMA Base address ----------------------------------------------------*/
#define TIM_DMABase_CR1                    ((u16)0x0000) // TIM CR1�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CR2                    ((u16)0x0001) // TIM CR2�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_SMCR                   ((u16)0x0002) // TIM SMCR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_DIER                   ((u16)0x0003) //	TIM DIER�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_SR                     ((u16)0x0004) //	TIM SR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_EGR                    ((u16)0x0005) //	TIM EGR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCMR1                  ((u16)0x0006) //	TIM CCMR1�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCMR2                  ((u16)0x0007) //	TIM CCMR2�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCER                   ((u16)0x0008) //	TIM CCER�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CNT                    ((u16)0x0009) //	TIM CNT�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_PSC                    ((u16)0x000A) //	TIM PSC�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_ARR                    ((u16)0x000B) //	TIM APR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_RCR                    ((u16)0x000C) //	TIM RCR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCR1                   ((u16)0x000D) //	TIM CCR1�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCR2                   ((u16)0x000E) //	TIM CCR2�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCR3                   ((u16)0x000F) //	TIM CCR3�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_CCR4                   ((u16)0x0010) //	TIM CCR4�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_BDTR                   ((u16)0x0011) //	TIM BDTR�Ĵ�����ΪDMA������ʼ ��
#define TIM_DMABase_DCR                    ((u16)0x0012) //	TIM DCR�Ĵ�����ΪDMA������ʼ ��

#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
                               ((BASE) == TIM_DMABase_DCR))

/* TIM DMA Burst Length ----------------------------------------------------*/
#define TIM_DMABurstLength_1Byte           ((u16)0x0000) // TIM DMA�������ͳ���1�� ��
#define TIM_DMABurstLength_2Bytes          ((u16)0x0100) // TIM DMA�������ͳ���2�� ��
#define TIM_DMABurstLength_3Bytes          ((u16)0x0200) // TIM DMA�������ͳ���3�� ��
#define TIM_DMABurstLength_4Bytes          ((u16)0x0300) // TIM DMA�������ͳ���4�� ��
#define TIM_DMABurstLength_5Bytes          ((u16)0x0400) // TIM DMA�������ͳ���5�� ��
#define TIM_DMABurstLength_6Bytes          ((u16)0x0500) // TIM DMA�������ͳ���6�� ��
#define TIM_DMABurstLength_7Bytes          ((u16)0x0600) // TIM DMA�������ͳ���7�� ��
#define TIM_DMABurstLength_8Bytes          ((u16)0x0700) // TIM DMA�������ͳ���8�� ��
#define TIM_DMABurstLength_9Bytes          ((u16)0x0800) // TIM DMA�������ͳ���9�� ��
#define TIM_DMABurstLength_10Bytes         ((u16)0x0900) // TIM DMA�������ͳ���10�� ��
#define TIM_DMABurstLength_11Bytes         ((u16)0x0A00) // TIM DMA�������ͳ���11�� ��
#define TIM_DMABurstLength_12Bytes         ((u16)0x0B00) // TIM DMA�������ͳ���12�� ��
#define TIM_DMABurstLength_13Bytes         ((u16)0x0C00) // TIM DMA�������ͳ���13�� ��
#define TIM_DMABurstLength_14Bytes         ((u16)0x0D00) // TIM DMA�������ͳ���14�� ��
#define TIM_DMABurstLength_15Bytes         ((u16)0x0E00) // TIM DMA�������ͳ���15�� ��
#define TIM_DMABurstLength_16Bytes         ((u16)0x0F00) // TIM DMA�������ͳ���16�� ��
#define TIM_DMABurstLength_17Bytes         ((u16)0x1000) // TIM DMA�������ͳ���17�� ��
#define TIM_DMABurstLength_18Bytes         ((u16)0x1100) // TIM DMA�������ͳ���18�� ��

#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Byte) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Bytes))

/* TIM DMA sources ---------------------------------------------------------*/
#define TIM_DMA_Update                     ((u16)0x0100) // TIM����DMAԴ ��
#define TIM_DMA_CC1                        ((u16)0x0200) // TIM����/�Ƚ�1DMAԴ ��
#define TIM_DMA_CC2                        ((u16)0x0400) // TIM����/�Ƚ�2DMAԴ ��
#define TIM_DMA_CC3                        ((u16)0x0800) // TIM����/�Ƚ�3DMAԴ ��
#define TIM_DMA_CC4                        ((u16)0x1000) // TIM����/�Ƚ�4DMAԴ ��
#define TIM_DMA_COM                        ((u16)0x2000) //	TIM COM DMAԴ ��
#define TIM_DMA_Trigger                    ((u16)0x4000) // TIM����DMAԴ ��

#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (u16)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

#define IS_TIM_PERIPH_DMA(PERIPH, SOURCE) ((((((*(u32*)&(PERIPH)) == TIM2_BASE) || (((*(u32*)&(PERIPH)) == TIM3_BASE))||\
                                            (((*(u32*)&(PERIPH)) == TIM4_BASE)) || (((*(u32*)&(PERIPH)) == TIM5_BASE))))&& \
                                            (((SOURCE) & (u16)0xA0FF) == 0x0000) && ((SOURCE) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM1_BASE) || (((*(u32*)&(PERIPH)) == TIM8_BASE))))&& \
                                            (((SOURCE) & (u16)0x80FF) == 0x0000) && ((SOURCE) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM6_BASE) || (((*(u32*)&(PERIPH)) == TIM7_BASE))))&& \
                                            (((SOURCE) & (u16)0xFEFF) == 0x0000) && ((SOURCE) != 0x0000)))

/* TIM External Trigger Prescaler ------------------------------------------*/
#define TIM_ExtTRGPSC_OFF                  ((u16)0x0000) // TIM ETRP Ԥ��Ƶ OFF ;
#define TIM_ExtTRGPSC_DIV2                 ((u16)0x1000) // TIM ETRPƵ�ʳ���2 ;
#define TIM_ExtTRGPSC_DIV4                 ((u16)0x2000) // TIM ETRPƵ�ʳ���4 ;
#define TIM_ExtTRGPSC_DIV8                 ((u16)0x3000) // TIM ETRPƵ�ʳ���8 ;

#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))

/* TIM Internal Trigger Selection ------------------------------------------*/
#define TIM_TS_ITR0                        ((u16)0x0000) // TIM�ڲ�����0 ��
#define TIM_TS_ITR1                        ((u16)0x0010) // TIM�ڲ�����1 ��
#define TIM_TS_ITR2                        ((u16)0x0020) // TIM�ڲ�����2 ��
#define TIM_TS_ITR3                        ((u16)0x0030) // TIM�ڲ�����3 ��
#define TIM_TS_TI1F_ED                     ((u16)0x0040) // TIM IC1���ӵ�TI1��ʹ�ñ���̽�� ��
#define TIM_TS_TI1FP1                      ((u16)0x0050) // TIM IC1���ӵ�TI1 ��
#define TIM_TS_TI2FP2                      ((u16)0x0060) // TIM IC2���ӵ�TI2 ��
#define TIM_TS_ETRF                        ((u16)0x0070) // TIM�ⲿ�������� ;

#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))

#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))

/* TIM TIx External Clock Source -------------------------------------------*/
#define TIM_TIxExternalCLK1Source_TI1      ((u16)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((u16)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((u16)0x0040)

#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))

/* TIM External Trigger Polarity -------------------------------------------*/
#define TIM_ExtTRGPolarity_Inverted        ((u16)0x8000) // TIM�ⲿ�������Է�ת���͵�ƽ���½�����Ч ;
#define TIM_ExtTRGPolarity_NonInverted     ((u16)0x0000) // TIM�ⲿ�������ԷǷ�ת���ߵ�ƽ����������Ч ;

#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))

/* TIM Prescaler Reload Mode -----------------------------------------------*/
#define TIM_PSCReloadMode_Update           ((u16)0x0000) // TIMԤ��Ƶֵ�ڸ����¼�װ�� ;
#define TIM_PSCReloadMode_Immediate        ((u16)0x0001) // TIMԤ��Ƶֵ��ʱװ�� ;    

#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))

/* TIM Forced Action -------------------------------------------------------*/
#define TIM_ForcedAction_Active            ((u16)0x0050) // ��ΪOCxREF�ϵĻ��ƽ ;
#define TIM_ForcedAction_InActive          ((u16)0x0040) // ��ΪOCxREF�ϵķǻ��ƽ ;

#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))

/* TIM Encoder Mode --------------------------------------------------------*/ 
#define TIM_EncoderMode_TI1                ((u16)0x0001) // ʹ��TIM����ģʽ1 ;
#define TIM_EncoderMode_TI2                ((u16)0x0002) //	ʹ��TIM����ģʽ2 ;
#define TIM_EncoderMode_TI12               ((u16)0x0003) // ʹ��TIM����ģʽ3 ;

#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))

/* TIM Event Source --------------------------------------------------------*/
#define TIM_EventSource_Update             ((u16)0x0001) // TIM�����¼�Դ ;
#define TIM_EventSource_CC1                ((u16)0x0002) // TIM����Ƚ�1�¼�Դ ;
#define TIM_EventSource_CC2                ((u16)0x0004) // TIM����Ƚ�2�¼�Դ ;
#define TIM_EventSource_CC3                ((u16)0x0008) // TIM����Ƚ�3�¼�Դ ;
#define TIM_EventSource_CC4                ((u16)0x0010) // TIM����Ƚ�4�¼�Դ ;
#define TIM_EventSource_COM                ((u16)0x0020) //	TIM COM�ж�Դ ��
#define TIM_EventSource_Trigger            ((u16)0x0040) // TIM�����¼�Դ ;
#define TIM_EventSource_Break              ((u16)0x0080) //	TIMɲ���ж�Դ ��

#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (u16)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

#define IS_TIM_PERIPH_EVENT(PERIPH, EVENT) ((((((*(u32*)&(PERIPH)) == TIM2_BASE) || (((*(u32*)&(PERIPH)) == TIM3_BASE))||\
                                            (((*(u32*)&(PERIPH)) == TIM4_BASE)) || (((*(u32*)&(PERIPH)) == TIM5_BASE))))&& \
                                            (((EVENT) & (u16)0xFFA0) == 0x0000) && ((EVENT) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM1_BASE) || (((*(u32*)&(PERIPH)) == TIM8_BASE))))&& \
                                            (((EVENT) & (u16)0xFF00) == 0x0000) && ((EVENT) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM6_BASE) || (((*(u32*)&(PERIPH)) == TIM7_BASE))))&& \
                                            (((EVENT) & (u16)0xFFFE) == 0x0000) && ((EVENT) != 0x0000)))

/* TIM Update Source --------------------------------------------------------*/
#define TIM_UpdateSource_Global            ((u16)0x0000) // �����ظ������壺�ڸ����¼�ʱ��������ֹͣ ;
#define TIM_UpdateSource_Regular           ((u16)0x0001) // ���ɵ�һ�����壺����������һ�������¼�ֹͣ ;

#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))

/* TIM Ouput Compare Preload State ------------------------------------------*/
#define TIM_OCPreload_Enable               ((u16)0x0008) // TIMx��CCR1�ϵ�Ԥװ�ؼĴ���ʹ�� ;
#define TIM_OCPreload_Disable              ((u16)0x0000) // TIMx��CCR1�ϵ�Ԥװ�ؼĴ���ʧ�� ;

#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))

/* TIM Ouput Compare Fast State ---------------------------------------------*/
#define TIM_OCFast_Enable                  ((u16)0x0004) // TIMx����ȽϿ�����������ʹ�� ;
#define TIM_OCFast_Disable                 ((u16)0x0000) //	TIMx����ȽϿ�����������ʧ�� ;

#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))
                                     
/* TIM Ouput Compare Clear State --------------------------------------------*/
#define TIM_OCClear_Enable                 ((u16)0x0080)  // TIMx����Ƚ����ʹ�� ;
#define TIM_OCClear_Disable                ((u16)0x0000)  // TIMx����Ƚ����ʧ�� ;

#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))                                     

/* TIM Trigger Output Source ------------------------------------------------*/ 
#define TIM_TRGOSource_Reset               ((u16)0x0000) //	ʹ�üĴ���TIM_EGR��UGλ��Ϊ���������TRGO�� ;
#define TIM_TRGOSource_Enable              ((u16)0x0010) //	ʹ�ü�����ʹ��CEN��Ϊ���������TRGO�� ;
#define TIM_TRGOSource_Update              ((u16)0x0020) //	ʹ�ø����¼���Ϊ���������TRGO��;
#define TIM_TRGOSource_OC1                 ((u16)0x0030) //	һ��������߱Ƚ�ƥ�䷢��������־λCC1F������ʱ�����������һ���϶����壨TRGO��;
#define TIM_TRGOSource_OC1Ref              ((u16)0x0040) //	ʹ��OC1REF��Ϊ���������TRGO�� ;
#define TIM_TRGOSource_OC2Ref              ((u16)0x0050) //	ʹ��OC2REF��Ϊ���������TRGO�� ;
#define TIM_TRGOSource_OC3Ref              ((u16)0x0060) //	ʹ��OC3REF��Ϊ���������TRGO�� ;
#define TIM_TRGOSource_OC4Ref              ((u16)0x0070) //	ʹ��OC4REF��Ϊ���������TRGO�� ;

#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))

#define IS_TIM_PERIPH_TRGO(PERIPH, TRGO)  (((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM6_BASE))||(((*(u32*)&(PERIPH)) == TIM7_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_Reset)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM6_BASE))||(((*(u32*)&(PERIPH)) == TIM7_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_Enable)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM6_BASE))||(((*(u32*)&(PERIPH)) == TIM7_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_Update)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_OC1)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_OC1Ref)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_OC2Ref)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_OC3Ref)) ||\
                                           ((((*(u32*)&(PERIPH)) == TIM2_BASE)||(((*(u32*)&(PERIPH)) == TIM1_BASE))||\
                                           (((*(u32*)&(PERIPH)) == TIM3_BASE))||(((*(u32*)&(PERIPH)) == TIM4_BASE))|| \
                                           (((*(u32*)&(PERIPH)) == TIM5_BASE))||(((*(u32*)&(PERIPH)) == TIM8_BASE))) && \
                                           ((TRGO) == TIM_TRGOSource_OC4Ref)))

/* TIM Slave Mode ----------------------------------------------------------*/
#define TIM_SlaveMode_Reset                ((u16)0x0004) //	ѡ�д����źţ�TRGI�����������س�ʼ���������������Ĵ����ĸ��� ;
#define TIM_SlaveMode_Gated                ((u16)0x0005) //	�������źţ�TRGI��Ϊ�ߵ�ƽ������ʱ��ʹ�� ;
#define TIM_SlaveMode_Trigger              ((u16)0x0006) //	�������ڴ�����TRGI���������ؿ�ʼ ;
#define TIM_SlaveMode_External1            ((u16)0x0007) //	ѡ�д�����TRGI������������Ϊ������ʱ�� ;

#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))

/* TIM Master Slave Mode ---------------------------------------------------*/
#define TIM_MasterSlaveMode_Enable         ((u16)0x0080) //	TIM��/��ģʽʹ�� ;
#define TIM_MasterSlaveMode_Disable        ((u16)0x0000) //	TIM��/��ģʽʧ�� ;

#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))

/* TIM Flags ---------------------------------------------------------------*/
#define TIM_FLAG_Update                    ((u16)0x0001) // TIM���±�־λ ;
#define TIM_FLAG_CC1                       ((u16)0x0002) // TIM����/�Ƚ�1��־λ ;
#define TIM_FLAG_CC2                       ((u16)0x0004) // TIM����/�Ƚ�2��־λ ;
#define TIM_FLAG_CC3                       ((u16)0x0008) // TIM����/�Ƚ�3��־λ ;
#define TIM_FLAG_CC4                       ((u16)0x0010) // TIM����/�Ƚ�4��־λ ;
#define TIM_FLAG_COM                       ((u16)0x0020)
#define TIM_FLAG_Trigger                   ((u16)0x0040) // TIM������־λ ;
#define TIM_FLAG_Break                     ((u16)0x0080)
#define TIM_FLAG_CC1OF                     ((u16)0x0200) // TIM����/�Ƚ�1�����־λ ;
#define TIM_FLAG_CC2OF                     ((u16)0x0400) // TIM����/�Ƚ�2�����־λ ;
#define TIM_FLAG_CC3OF                     ((u16)0x0800) // TIM����/�Ƚ�3�����־λ ;
#define TIM_FLAG_CC4OF                     ((u16)0x1000) // TIM����/�Ƚ�4�����־λ ;

#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))

#define IS_TIM_CLEAR_FLAG(PERIPH, TIM_FLAG) ((((((*(u32*)&(PERIPH)) == TIM2_BASE) || (((*(u32*)&(PERIPH)) == TIM3_BASE))||\
                                            (((*(u32*)&(PERIPH)) == TIM4_BASE)) || (((*(u32*)&(PERIPH)) == TIM5_BASE))))&& \
                                            (((TIM_FLAG) & (u16)0xE1A0) == 0x0000) && ((TIM_FLAG) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM1_BASE) || (((*(u32*)&(PERIPH)) == TIM8_BASE))))&& \
                                            (((TIM_FLAG) & (u16)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000)) ||\
                                            (((((*(u32*)&(PERIPH)) == TIM6_BASE) || (((*(u32*)&(PERIPH)) == TIM7_BASE))))&& \
                                            (((TIM_FLAG) & (u16)0xFFFE) == 0x0000) && ((TIM_FLAG) != 0x0000)))

#define IS_TIM_PERIPH_FLAG(PERIPH, TIM_FLAG)  (((((*(u32*)&(PERIPH))==TIM2_BASE) || ((*(u32*)&(PERIPH)) == TIM3_BASE) ||\
                                                 ((*(u32*)&(PERIPH)) == TIM4_BASE) || ((*(u32*)&(PERIPH))==TIM5_BASE) || \
                                                 ((*(u32*)&(PERIPH))==TIM1_BASE) || ((*(u32*)&(PERIPH))==TIM8_BASE)) &&\
                                                 (((TIM_FLAG) == TIM_FLAG_CC1) || ((TIM_FLAG) == TIM_FLAG_CC2) ||\
                                                 ((TIM_FLAG) == TIM_FLAG_CC3) || ((TIM_FLAG) == TIM_FLAG_CC4) || \
                                                 ((TIM_FLAG) == TIM_FLAG_Trigger))) ||\
                                                 ((((*(u32*)&(PERIPH))==TIM2_BASE) || ((*(u32*)&(PERIPH)) == TIM3_BASE) || \
                                                 ((*(u32*)&(PERIPH)) == TIM4_BASE) || ((*(u32*)&(PERIPH))==TIM5_BASE) ||\
                                                 ((*(u32*)&(PERIPH))==TIM1_BASE)|| ((*(u32*)&(PERIPH))==TIM8_BASE) || \
                                                 ((*(u32*)&(PERIPH))==TIM7_BASE) || ((*(u32*)&(PERIPH))==TIM6_BASE)) && \
                                                 (((TIM_FLAG) == TIM_FLAG_Update))) ||\
                                                 ((((*(u32*)&(PERIPH))==TIM1_BASE) || ((*(u32*)&(PERIPH)) == TIM8_BASE)) &&\
                                                 (((TIM_FLAG) == TIM_FLAG_COM) || ((TIM_FLAG) == TIM_FLAG_Break))) ||\
                                                 ((((*(u32*)&(PERIPH))==TIM2_BASE) || ((*(u32*)&(PERIPH)) == TIM3_BASE) || \
                                                 ((*(u32*)&(PERIPH)) == TIM4_BASE) || ((*(u32*)&(PERIPH))==TIM5_BASE) || \
                                                 ((*(u32*)&(PERIPH))==TIM1_BASE) || ((*(u32*)&(PERIPH))==TIM8_BASE)) &&\
                                                 (((TIM_FLAG) == TIM_FLAG_CC1OF) || ((TIM_FLAG) == TIM_FLAG_CC2OF) ||\
                                                 ((TIM_FLAG) == TIM_FLAG_CC3OF) || ((TIM_FLAG) == TIM_FLAG_CC4OF))))             
                                                                                            
/* TIM Input Capture Filer Value ---------------------------------------------*/
#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF) 

/* TIM External Trigger Filter -----------------------------------------------*/
#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)                              

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, u16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, u16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, u16 TIM_DMABase, u16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, u16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_TIxExternalCLKSource,
                                u16 TIM_ICPolarity, u16 ICFilter);                                
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                             u16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, 
                             u16 TIM_ExtTRGPolarity, u16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                   u16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, u16 Prescaler, u16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, u16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, u16 TIM_EncoderMode,
                                u16 TIM_IC1Polarity, u16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, u16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, u16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, u16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, u16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, u16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, u16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, u16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, u16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, u16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, u16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, u16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, u16 TIM_CKD);
u16 TIM_GetCapture1(TIM_TypeDef* TIMx);
u16 TIM_GetCapture2(TIM_TypeDef* TIMx);
u16 TIM_GetCapture3(TIM_TypeDef* TIMx);
u16 TIM_GetCapture4(TIM_TypeDef* TIMx);
u16 TIM_GetCounter(TIM_TypeDef* TIMx);
u16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, u16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, u16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT);
                                                                                                             
#endif /*__STM32F10x_TIM_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/








