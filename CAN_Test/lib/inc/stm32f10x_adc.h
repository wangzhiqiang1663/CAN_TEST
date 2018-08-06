/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_adc.h
* Author             : MCD Application Team
* Version            : V2.0
* Date               : 05/23/2008
* Description        : This file contains all the functions prototypes for the
*                      ADC firmware library.
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
#ifndef __STM32F10x_ADC_H
#define __STM32F10x_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* ADC Init structure definition */
typedef struct
{
  u32 ADC_Mode;	 // ����ADC�����ڶ�������˫ADCģʽ��
  FunctionalState ADC_ScanConvMode; // �涨��ģ��ת��������ɨ��ģʽ����ͨ�������ǵ��Σ���ͨ����ģʽ ��
  FunctionalState ADC_ContinuousConvMode; // �涨��ģ��ת���������������ǵ���ģʽ�� 
  u32 ADC_ExternalTrigConv;	 // ������ʹ���ⲿ��������������ͨ����ģ��ת�� ��
  u32 ADC_DataAlign;	// �涨��ADC��������߶��뻹�����ұ߶��� ��
  u8 ADC_NbrOfChannel;	// �涨��˳����й���ת����ADCͨ������Ŀ�������Ŀ��ȡֵ��Χ��1��16	��
}ADC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
#define IS_ADC_ALL_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == ADC1_BASE) || \
                                   ((*(u32*)&(PERIPH)) == ADC2_BASE) || \
                                   ((*(u32*)&(PERIPH)) == ADC3_BASE))
                                 
#define IS_ADC_DMA_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == ADC1_BASE) || \
                                   ((*(u32*)&(PERIPH)) == ADC3_BASE))

/* ADC dual mode -------------------------------------------------------------*/
#define ADC_Mode_Independent                       ((u32)0x00000000) // ADC1��ADC2�����ڶ���ģʽ ��
#define ADC_Mode_RegInjecSimult                    ((u32)0x00010000) //	ADC1��ADC2������ͬ�������ͬ��ע��ģʽ ��
#define ADC_Mode_RegSimult_AlterTrig               ((u32)0x00020000) //	ADC1��ADC2������ͬ������ģʽ�ͽ��津��ģʽ ��
#define ADC_Mode_InjecSimult_FastInterl            ((u32)0x00030000) //	ADC1��ADC2������ͬ������ģʽ�Ϳ��ٽ���ģʽ ��
#define ADC_Mode_InjecSimult_SlowInterl            ((u32)0x00040000) //	ADC1��ADC2������ͬ��ע��ģʽ�����ٽ���ģʽ ��
#define ADC_Mode_InjecSimult                       ((u32)0x00050000) //	ADC1��ADC2������ͬ��ע��ģʽ ��
#define ADC_Mode_RegSimult                         ((u32)0x00060000) //	ADC1��ADC2������ͬ������ģʽ ��
#define ADC_Mode_FastInterl                        ((u32)0x00070000) //	ADC1��ADC2�����ڿ��ٽ���ģʽ ��
#define ADC_Mode_SlowInterl                        ((u32)0x00080000) //	ADC1��ADC2���������ٽ���ģʽ ��
#define ADC_Mode_AlterTrig                         ((u32)0x00090000) //	ADC1��ADC2�����ڽ��津��ģʽ ��

#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) || \
                           ((MODE) == ADC_Mode_RegInjecSimult) || \
                           ((MODE) == ADC_Mode_RegSimult_AlterTrig) || \
                           ((MODE) == ADC_Mode_InjecSimult_FastInterl) || \
                           ((MODE) == ADC_Mode_InjecSimult_SlowInterl) || \
                           ((MODE) == ADC_Mode_InjecSimult) || \
                           ((MODE) == ADC_Mode_RegSimult) || \
                           ((MODE) == ADC_Mode_FastInterl) || \
                           ((MODE) == ADC_Mode_SlowInterl) || \
                           ((MODE) == ADC_Mode_AlterTrig))

/* ADC extrenal trigger sources for regular channels conversion --------------*/
/* for ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T1_CC1                ((u32)0x00000000) // ѡ��ʱ��1�Ĳ���Ƚ�1��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_T1_CC2                ((u32)0x00020000) // ѡ��ʱ��1�Ĳ���Ƚ�2��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_T2_CC2                ((u32)0x00060000) // ѡ��ʱ��2�Ĳ���Ƚ�2��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_T3_TRGO               ((u32)0x00080000) //	ѡ��ʱ��3��TRGO��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_T4_CC4                ((u32)0x000A0000) // ѡ��ʱ��4�Ĳ���Ƚ�4��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO    ((u32)0x000C0000) // ѡ���ⲿ�ж���11�¼���Ϊת���ⲿ���� ��
/* for ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigConv_T1_CC3                ((u32)0x00040000) // ѡ��ʱ��1�Ĳ���Ƚ�3��Ϊת���ⲿ���� ��
#define ADC_ExternalTrigConv_None                  ((u32)0x000E0000) // ת��������������ⲿ�������� ��
/* for ADC3 */
#define ADC_ExternalTrigConv_T3_CC1                ((u32)0x00000000)
#define ADC_ExternalTrigConv_T2_CC3                ((u32)0x00020000)
#define ADC_ExternalTrigConv_T8_CC1                ((u32)0x00060000)
#define ADC_ExternalTrigConv_T8_TRGO               ((u32)0x00080000)
#define ADC_ExternalTrigConv_T5_CC1                ((u32)0x000A0000)
#define ADC_ExternalTrigConv_T5_CC3                ((u32)0x000C0000)

#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConv_T1_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T4_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_None) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC3))

/* ADC data align ------------------------------------------------------------*/
#define ADC_DataAlign_Right                        ((u32)0x00000000) // ADC�����Ҷ��� ��
#define ADC_DataAlign_Left                         ((u32)0x00000800) // ADC��������� ��

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))

/* ADC channels --------------------------------------------------------------*/
#define ADC_Channel_0                               ((u8)0x00) // ѡ��ADCͨ��0 ��
#define ADC_Channel_1                               ((u8)0x01) // ѡ��ADCͨ��1 ��
#define ADC_Channel_2                               ((u8)0x02) // ѡ��ADCͨ��2 ��
#define ADC_Channel_3                               ((u8)0x03) // ѡ��ADCͨ��3 ��
#define ADC_Channel_4                               ((u8)0x04) // ѡ��ADCͨ��4 ��
#define ADC_Channel_5                               ((u8)0x05) // ѡ��ADCͨ��5 ��
#define ADC_Channel_6                               ((u8)0x06) // ѡ��ADCͨ��6 ��
#define ADC_Channel_7                               ((u8)0x07) // ѡ��ADCͨ��7 ��
#define ADC_Channel_8                               ((u8)0x08) // ѡ��ADCͨ��8 ��
#define ADC_Channel_9                               ((u8)0x09) // ѡ��ADCͨ��9 ��
#define ADC_Channel_10                              ((u8)0x0A) // ѡ��ADCͨ��10 ��
#define ADC_Channel_11                              ((u8)0x0B) // ѡ��ADCͨ��11 ��
#define ADC_Channel_12                              ((u8)0x0C) // ѡ��ADCͨ��12 ��
#define ADC_Channel_13                              ((u8)0x0D) // ѡ��ADCͨ��13 ��
#define ADC_Channel_14                              ((u8)0x0E) // ѡ��ADCͨ��14 ��
#define ADC_Channel_15                              ((u8)0x0F) // ѡ��ADCͨ��15 ��
#define ADC_Channel_16                              ((u8)0x10) // ѡ��ADCͨ��16 ��
#define ADC_Channel_17                              ((u8)0x11) // ѡ��ADCͨ��17 ��

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_0) || ((CHANNEL) == ADC_Channel_1) || \
                                 ((CHANNEL) == ADC_Channel_2) || ((CHANNEL) == ADC_Channel_3) || \
                                 ((CHANNEL) == ADC_Channel_4) || ((CHANNEL) == ADC_Channel_5) || \
                                 ((CHANNEL) == ADC_Channel_6) || ((CHANNEL) == ADC_Channel_7) || \
                                 ((CHANNEL) == ADC_Channel_8) || ((CHANNEL) == ADC_Channel_9) || \
                                 ((CHANNEL) == ADC_Channel_10) || ((CHANNEL) == ADC_Channel_11) || \
                                 ((CHANNEL) == ADC_Channel_12) || ((CHANNEL) == ADC_Channel_13) || \
                                 ((CHANNEL) == ADC_Channel_14) || ((CHANNEL) == ADC_Channel_15) || \
                                 ((CHANNEL) == ADC_Channel_16) || ((CHANNEL) == ADC_Channel_17))

/* ADC sampling times --------------------------------------------------------*/
#define ADC_SampleTime_1Cycles5                    ((u8)0x00) // ����ʱ��Ϊ1.5���� ��
#define ADC_SampleTime_7Cycles5                    ((u8)0x01) // ����ʱ��Ϊ7.5���� ��
#define ADC_SampleTime_13Cycles5                   ((u8)0x02) // ����ʱ��Ϊ13.5���� ��
#define ADC_SampleTime_28Cycles5                   ((u8)0x03) // ����ʱ��Ϊ28.5���� ��
#define ADC_SampleTime_41Cycles5                   ((u8)0x04) // ����ʱ��Ϊ41.5���� ��
#define ADC_SampleTime_55Cycles5                   ((u8)0x05) // ����ʱ��Ϊ55.5���� ��
#define ADC_SampleTime_71Cycles5                   ((u8)0x06) // ����ʱ��Ϊ71.5���� ��
#define ADC_SampleTime_239Cycles5                  ((u8)0x07) // ����ʱ��Ϊ239.5���� ��

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1Cycles5) || \
                                  ((TIME) == ADC_SampleTime_7Cycles5) || \
                                  ((TIME) == ADC_SampleTime_13Cycles5) || \
                                  ((TIME) == ADC_SampleTime_28Cycles5) || \
                                  ((TIME) == ADC_SampleTime_41Cycles5) || \
                                  ((TIME) == ADC_SampleTime_55Cycles5) || \
                                  ((TIME) == ADC_SampleTime_71Cycles5) || \
                                  ((TIME) == ADC_SampleTime_239Cycles5))

/* ADC extrenal trigger sources for injected channels conversion -------------*/
/* For ADC1 and ADC2 */
#define ADC_ExternalTrigInjecConv_T2_TRGO           ((u32)0x00002000) // ѡ��ʱ��2��TRGO��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_T2_CC1            ((u32)0x00003000) // ѡ��ʱ��2�Ĳ���Ƚ�1��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_T3_CC4            ((u32)0x00004000) // ѡ��ʱ��3�Ĳ���Ƚ�4��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_T4_TRGO           ((u32)0x00005000) // ѡ��ʱ��4��TRGO��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4 ((u32)0x00006000) // ѡ���ⲿ�ж���15�¼���Ϊע��ת���ⲿ���� ��
/* For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigInjecConv_T1_TRGO           ((u32)0x00000000) // ѡ��ʱ��1��TRGO��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_T1_CC4            ((u32)0x00001000) // ѡ��ʱ��1�Ĳ���Ƚ�4��Ϊע��ת���ⲿ���� ��
#define ADC_ExternalTrigInjecConv_None              ((u32)0x00007000) // ע��ת��������������ⲿ�������� ��
/* For ADC3 */
#define ADC_ExternalTrigInjecConv_T4_CC3            ((u32)0x00002000)
#define ADC_ExternalTrigInjecConv_T8_CC2            ((u32)0x00003000)
#define ADC_ExternalTrigInjecConv_T8_CC4            ((u32)0x00004000)
#define ADC_ExternalTrigInjecConv_T5_TRGO           ((u32)0x00005000)
#define ADC_ExternalTrigInjecConv_T5_CC4            ((u32)0x00006000)

#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_ExternalTrigInjecConv_T1_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T1_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T2_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T2_CC1) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T3_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_None) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_CC3) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T8_CC2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T8_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T5_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T5_CC4))

/* ADC injected channel selection --------------------------------------------*/
#define ADC_InjectedChannel_1                       ((u8)0x14) // ѡ��ע��ͨ��1 ��
#define ADC_InjectedChannel_2                       ((u8)0x18) // ѡ��ע��ͨ��2 ��
#define ADC_InjectedChannel_3                       ((u8)0x1C) // ѡ��ע��ͨ��3 ��
#define ADC_InjectedChannel_4                       ((u8)0x20) // ѡ��ע��ͨ��4 ��

#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
                                          ((CHANNEL) == ADC_InjectedChannel_2) || \
                                          ((CHANNEL) == ADC_InjectedChannel_3) || \
                                          ((CHANNEL) == ADC_InjectedChannel_4))

/* ADC analog watchdog selection ---------------------------------------------*/
#define ADC_AnalogWatchdog_SingleRegEnable         ((u32)0x00800200) // ��������ͨ��������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_SingleInjecEnable       ((u32)0x00400200) // ����ע��ͨ��������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable  ((u32)0x00C00200) // ��������ͨ������ע��ͨ��������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_AllRegEnable            ((u32)0x00800000) // ���й���ͨ��������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_AllInjecEnable          ((u32)0x00400000) // ����ע��ͨ��������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_AllRegAllInjecEnable    ((u32)0x00C00000) // ���й���ͨ��������ע��ͨ����������ģ�⿴�Ź� ��
#define ADC_AnalogWatchdog_None                    ((u32)0x00000000) // ������ģ�⿴�Ź� ��

#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
                                          ((WATCHDOG) == ADC_AnalogWatchdog_None))

/* ADC interrupts definition -------------------------------------------------*/
#define ADC_IT_EOC                                 ((u16)0x0220) // EOC�ж����� ��
#define ADC_IT_AWD                                 ((u16)0x0140) // AWDOG�ж����� ��
#define ADC_IT_JEOC                                ((u16)0x0480) // JEOC�ж����� ��

#define IS_ADC_IT(IT) ((((IT) & (u16)0xF81F) == 0x00) && ((IT) != 0x00))
#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_AWD) || \
                           ((IT) == ADC_IT_JEOC))

/* ADC flags definition ------------------------------------------------------*/
#define ADC_FLAG_AWD                               ((u8)0x01) // ģ�⿴�Ź���־λ ��
#define ADC_FLAG_EOC                               ((u8)0x02) // ת��������־λ ��
#define ADC_FLAG_JEOC                              ((u8)0x04) // ע����ת��������־λ ��
#define ADC_FLAG_JSTRT                             ((u8)0x08) // ע����ת����ʼ��־λ ��
#define ADC_FLAG_STRT                              ((u8)0x10) // ������ת����ʼ��־λ ��

#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (u8)0xE0) == 0x00) && ((FLAG) != 0x00))
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_AWD) || ((FLAG) == ADC_FLAG_EOC) || \
                               ((FLAG) == ADC_FLAG_JEOC) || ((FLAG)== ADC_FLAG_JSTRT) || \
                               ((FLAG) == ADC_FLAG_STRT))

/* ADC thresholds ------------------------------------------------------------*/
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)

/* ADC injected offset -------------------------------------------------------*/
#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)

/* ADC injected length -------------------------------------------------------*/
#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/* ADC injected rank ---------------------------------------------------------*/
#define IS_ADC_INJECTED_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x4))

/* ADC regular length --------------------------------------------------------*/
#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))

/* ADC regular rank ----------------------------------------------------------*/
#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x10))

/* ADC regular discontinuous mode number -------------------------------------*/
#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, u16 ADC_IT, FunctionalState NewState);
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, u8 Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
u16 ADC_GetConversionValue(ADC_TypeDef* ADCx);
u32 ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, u32 ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel, u8 Rank, u8 ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, u8 Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel, u16 Offset);
u16 ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, u8 ADC_InjectedChannel);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, u32 ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, u16 HighThreshold, u16 LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, u8 ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, u8 ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, u8 ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, u16 ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, u16 ADC_IT);

#endif /*__STM32F10x_ADC_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
