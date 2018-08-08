#include "can.h"

CanTxMsg TxMessage;//���巢����Ϣ�ṹ��


/**********************************************************
** ������:NVIC_Config
** ��������:  �ж����ȼ�����������
** �������: ��
** �������: ��
***********************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
 
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;//����CAN�����ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN | RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO,ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_Remap2_CAN, ENABLE);
	/* ���� CAN �� Rx(PA.11) ���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ���� CAN �� Tx(PA.12) ���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
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
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //��������ѡ����ģʽ���������ֹ���ģʽ
	/*   
   CAN_MODE                                      ����
	 CAN_Mode_Normal                               ����ģʽ
	 CAN_Mode_Silent                               ��Ĭģʽ
   CAN_Mode_LoopBack                             ����ģʽ
   CAN_Mode_Silent_LoopBack                      ��Ĭ����
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;       //����ʱ�� ������=36M/(N*(1+TS1+TS2))
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 4;
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
	CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID<<5;             // 11λ�ı�ʶ���Ǵӵ�5λ����18λ��������Ҫ����5λ,28λ��ʶ������λ���Ǳ�ʶ����������λ
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN_IT_FMP0, ENABLE);
}


/**********************************************************
** ������: SendCan
** ��������:CAN��Ϣ����
** �������: str--ָ�������������ָ��
             id ���͵ı�׼֡ID
** �������: ��
***********************************************************/
void SendCan(u8 *Transdata,u32 id)
{
	u32 i = 0; 
  u8 TransmitMailbox = 0; 
	//TxMessage.ExtId=0x01; // �趨��չ��ʶ��
	TxMessage.StdId =id;// �趨��׼��ʶ��
	TxMessage.IDE=CAN_ID_STD;//��׼��ʶ��
	TxMessage.RTR=CAN_RTR_DATA;//�趨��������Ϣ��Ϊ����֡
	TxMessage.DLC=strlen(Transdata); //�趨��������Ϣ��֡����

	while(*Transdata)
	{
		TxMessage.Data[i++]=*Transdata++;	// ��������������
	}
	TransmitMailbox = CAN_Transmit(&TxMessage);//��ʼһ����Ϣ�Ĵ��� 

  	i = 0; 
 	while((CAN_TransmitStatus(TransmitMailbox)!=CANTXOK)&&(i!=0xFF))//ͨ�����CANTXOKλ��ȷ�Ϸ����Ƿ�ɹ� 
  	{ 
   	 	i++; 
  	} 
}
/**********************************************************
** ������: Init_RxMes
** ��������:  ��ʼ��CAN��Ϣ���յĽṹ��
** �������: RxMessage--���ݽ��յĽṹ��
** �������: ��
***********************************************************/
void Init_RxMes(CanRxMsg *RxMessage)
{
  u8 i = 0;

  RxMessage->StdId = 0x00;
  RxMessage->ExtId = 0x00;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 0;
  RxMessage->FMI = 0;
  for (i = 0;i < 8;i++)
  RxMessage->Data[i] = 0x00;
}

void All_Init(void)
{
	NVIC_Configuration();
	CAN_Configuration();//CAN��ʼ������
}