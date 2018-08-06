#include"can.h"
#include "stm32f10x_lib.h"		//�������е�ͷ�ļ�

/*******************************************************************************
* ������ 		: CAN_Polling
* ��������    	: ����CANΪ�����շ�ģʽ
* �������     	: ��
* ������     	: ��
* ����ֵ       	: ��
*******************************************************************************/

void CAN_Configuration(void)
{
	 
	/* ���� CAN �������͹�������ʼ���ṹ�� */
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
  /* ���� GPIO ��ʼ���ṹ�� GPIO_InitStructure */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* CAN �Ĵ�����λ */
	CAN_DeInit();
	CAN_StructInit(&CAN_InitStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap2_CAN, ENABLE);
	/* ���� CAN �� Rx(PA.11) ���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* ���� CAN �� Tx(PA.12) ���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* 	
	*	CAN ��������ʼ����
	*  
	*	ʧ��ʱ�䴥��ͨѶģʽ
	*	ʧ���Զ����߹���
	*	ʧ���Զ�����ģʽ
	*	ʧ�ܷ��Զ��ش���ģʽ
	*	ʧ�ܽ��� FIFO ����ģʽ
	*	ʧ�ܷ��� FIFO ���ȼ�
	*	CAN Ӳ�������ڻ���ģʽ 
	*	����ͬ����Ծ��� 1 ��ʱ�䵥λ
	*	ʱ��� 1 Ϊ 8 ��ʱ�䵥λ
	*	ʱ��� 2 Ϊ 7 ��ʱ�䵥λ
	*	��Ƶ��Ϊ5  
	*/
	
	CAN_InitStructure.CAN_TTCM = DISABLE;  //����ʹ�ܻ���ʧ��ʱ�䴥����ʽ������ѡ��ENABLE����DISABLE
	CAN_InitStructure.CAN_ABOM = DISABLE;  //����ʧ�ܻ���ʹ���Զ����߹���
	CAN_InitStructure.CAN_AWUM = DISABLE;  //����ʹ�ܻ���ʧ���Զ�����ģʽ
	CAN_InitStructure.CAN_NART = DISABLE;  //����ʹ�ܻ���ʧ�ܷ��Զ��ش�ģʽ
	CAN_InitStructure.CAN_RFLM = DISABLE;  //����ʧ�ܻ���ʹ��FIFO����ģʽ
	CAN_InitStructure.CAN_TXFP = DISABLE;  //����ʧ�ܻ���ʹ�ܷ���FIFO ���ȼ�
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;  //��������ѡ����ģʽ���������ֹ���ģʽ
	/*   
   CAN_MODE                                      ����
	 CAN_Mode_Normal                               ����ģʽ
	 CAN_Mode_Silent                               ��Ĭģʽ
   CAN_Mode_LoopBack                             ����ģʽ
   CAN_Mode_Silent_LoopBack                      ��Ĭ����
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;       //����ʱ�� ������=36M/(N*(1+TS1+TS2))
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler = 5;
	CAN_Init(&CAN_InitStructure);
	
	/* 	 
	*	CAN ��������ʼ����
	*
	*	��ʼ�������� 2
	*	��ʶ������λģʽ
	*	ʹ�� 1 �� 32 λ������ 
	*	��������ʶ��Ϊ (0x00AA << 5)
	*	���������α�ʶ�� 0xFFFF
	*	������ FIFO0 ָ������� 0 
	*	ʹ�ܹ����� 
	*/
	
	CAN_FilterInitStructure.CAN_FilterNumber = 0;         //ָ����ʼ�����������ṩ��14��λ��ɱ�Ĺ�������0-13������2��32λ��ʱ��
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;   //ѡ������λģʽ��һ���Ĵ����Ǳ�ʶ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0xAAAA<<3;             // 11λ�ı�ʶ���Ǵӵ�5λ����18λ��������Ҫ����5λ
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffFF<<3;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
}