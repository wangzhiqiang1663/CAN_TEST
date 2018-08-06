/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_bkp.h
* Author             : MCD Application Team
* Version            : V2.0
* Date               : 05/23/2008
* Description        : This file contains all the functions prototypes for the
*                      BKP firmware library.
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
#ifndef __STM32F10x_BKP_H
#define __STM32F10x_BKP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Tamper Pin active level */
#define BKP_TamperPinLevel_High           ((u16)0x0000)	// ������ܽŸߵ�ƽ��Ч ��
#define BKP_TamperPinLevel_Low            ((u16)0x0001)	// ������ܽŵ͵�ƽ��Ч ��

#define IS_BKP_TAMPER_PIN_LEVEL(LEVEL) (((LEVEL) == BKP_TamperPinLevel_High) || \
                                        ((LEVEL) == BKP_TamperPinLevel_Low))

/* RTC output source to output on the Tamper pin */
#define BKP_RTCOutputSource_None          ((u16)0x0000)	// ������ܽ�����RTC��� ��
#define BKP_RTCOutputSource_CalibClock    ((u16)0x0080)	// ������ܽ����������ʱ��Ƶ��ΪRTCʱ�ӳ���64 ��
#define BKP_RTCOutputSource_Alarm         ((u16)0x0100)	// ������ܽ������RTC�������� ��
#define BKP_RTCOutputSource_Second        ((u16)0x0300)	// ������ܽ������RTC������ ��

#define IS_BKP_RTC_OUTPUT_SOURCE(SOURCE) (((SOURCE) == BKP_RTCOutputSource_None) || \
                                          ((SOURCE) == BKP_RTCOutputSource_CalibClock) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Alarm) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Second))

/* Data Backup Register */
#define BKP_DR1                           ((u16)0x0004)	// ѡ�����ݼĴ��� 1 ��
#define BKP_DR2                           ((u16)0x0008)	// ѡ�����ݼĴ��� 2 ��
#define BKP_DR3                           ((u16)0x000C)	// ѡ�����ݼĴ��� 3 ��
#define BKP_DR4                           ((u16)0x0010)	// ѡ�����ݼĴ��� 4 ��
#define BKP_DR5                           ((u16)0x0014)	// ѡ�����ݼĴ��� 5 ��
#define BKP_DR6                           ((u16)0x0018)	// ѡ�����ݼĴ��� 6 ��
#define BKP_DR7                           ((u16)0x001C)	// ѡ�����ݼĴ��� 7 ��
#define BKP_DR8                           ((u16)0x0020)	// ѡ�����ݼĴ��� 8 ��
#define BKP_DR9                           ((u16)0x0024)	// ѡ�����ݼĴ��� 9 ��
#define BKP_DR10                          ((u16)0x0028)	// ѡ�����ݼĴ��� 10 ��
#define BKP_DR11                          ((u16)0x0040)	// ѡ�����ݼĴ��� 11 ��
#define BKP_DR12                          ((u16)0x0044)	// ѡ�����ݼĴ��� 12 ��
#define BKP_DR13                          ((u16)0x0048)	// ѡ�����ݼĴ��� 13 ��
#define BKP_DR14                          ((u16)0x004C)	// ѡ�����ݼĴ��� 14 ��
#define BKP_DR15                          ((u16)0x0050)	// ѡ�����ݼĴ��� 15 ��
#define BKP_DR16                          ((u16)0x0054)	// ѡ�����ݼĴ��� 16 ��
#define BKP_DR17                          ((u16)0x0058)	// ѡ�����ݼĴ��� 17 ��
#define BKP_DR18                          ((u16)0x005C)	// ѡ�����ݼĴ��� 18 ��
#define BKP_DR19                          ((u16)0x0060)	// ѡ�����ݼĴ��� 19 ��
#define BKP_DR20                          ((u16)0x0064)	// ѡ�����ݼĴ��� 20 ��
#define BKP_DR21                          ((u16)0x0068)	// ѡ�����ݼĴ��� 21 ��
#define BKP_DR22                          ((u16)0x006C)	// ѡ�����ݼĴ��� 22 ��
#define BKP_DR23                          ((u16)0x0070)	// ѡ�����ݼĴ��� 23 ��
#define BKP_DR24                          ((u16)0x0074)	// ѡ�����ݼĴ��� 24 ��
#define BKP_DR25                          ((u16)0x0078)	// ѡ�����ݼĴ��� 25 ��
#define BKP_DR26                          ((u16)0x007C)	// ѡ�����ݼĴ��� 26 ��
#define BKP_DR27                          ((u16)0x0080)	// ѡ�����ݼĴ��� 27 ��
#define BKP_DR28                          ((u16)0x0084)	// ѡ�����ݼĴ��� 28 ��
#define BKP_DR29                          ((u16)0x0088)	// ѡ�����ݼĴ��� 29 ��
#define BKP_DR30                          ((u16)0x008C)	// ѡ�����ݼĴ��� 30 ��
#define BKP_DR31                          ((u16)0x0090)	// ѡ�����ݼĴ��� 31 ��
#define BKP_DR32                          ((u16)0x0094)	// ѡ�����ݼĴ��� 32 ��
#define BKP_DR33                          ((u16)0x0098)	// ѡ�����ݼĴ��� 33 ��
#define BKP_DR34                          ((u16)0x009C)	// ѡ�����ݼĴ��� 34 ��
#define BKP_DR35                          ((u16)0x00A0)	// ѡ�����ݼĴ��� 35 ��
#define BKP_DR36                          ((u16)0x00A4)	// ѡ�����ݼĴ��� 36 ��
#define BKP_DR37                          ((u16)0x00A8)	// ѡ�����ݼĴ��� 37 ��
#define BKP_DR38                          ((u16)0x00AC)	// ѡ�����ݼĴ��� 38 ��
#define BKP_DR39                          ((u16)0x00B0)	// ѡ�����ݼĴ��� 39 ��
#define BKP_DR40                          ((u16)0x00B4)	// ѡ�����ݼĴ��� 40 ��
#define BKP_DR41                          ((u16)0x00B8)	// ѡ�����ݼĴ��� 41 ��
#define BKP_DR42                          ((u16)0x00BC)	// ѡ�����ݼĴ��� 42 ��

#define IS_BKP_DR(DR) (((DR) == BKP_DR1)  || ((DR) == BKP_DR2)  || ((DR) == BKP_DR3)  || \
                       ((DR) == BKP_DR4)  || ((DR) == BKP_DR5)  || ((DR) == BKP_DR6)  || \
                       ((DR) == BKP_DR7)  || ((DR) == BKP_DR8)  || ((DR) == BKP_DR9)  || \
                       ((DR) == BKP_DR10) || ((DR) == BKP_DR11) || ((DR) == BKP_DR12) || \
                       ((DR) == BKP_DR13) || ((DR) == BKP_DR14) || ((DR) == BKP_DR15) || \
                       ((DR) == BKP_DR16) || ((DR) == BKP_DR17) || ((DR) == BKP_DR18) || \
                       ((DR) == BKP_DR19) || ((DR) == BKP_DR20) || ((DR) == BKP_DR21) || \
                       ((DR) == BKP_DR22) || ((DR) == BKP_DR23) || ((DR) == BKP_DR24) || \
                       ((DR) == BKP_DR25) || ((DR) == BKP_DR26) || ((DR) == BKP_DR27) || \
                       ((DR) == BKP_DR28) || ((DR) == BKP_DR29) || ((DR) == BKP_DR30) || \
                       ((DR) == BKP_DR31) || ((DR) == BKP_DR32) || ((DR) == BKP_DR33) || \
                       ((DR) == BKP_DR34) || ((DR) == BKP_DR35) || ((DR) == BKP_DR36) || \
                       ((DR) == BKP_DR37) || ((DR) == BKP_DR38) || ((DR) == BKP_DR39) || \
                       ((DR) == BKP_DR40) || ((DR) == BKP_DR41) || ((DR) == BKP_DR42))

#define IS_BKP_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7F)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(u16 BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(u16 BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(u8 CalibrationValue);
void BKP_WriteBackupRegister(u16 BKP_DR, u16 Data);
u16 BKP_ReadBackupRegister(u16 BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);

#endif /* __STM32F10x_BKP_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
