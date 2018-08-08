#include"adc.h"		//�������е�ͷ�ļ�


/**********************************************************
** ������: ADC1__Config
** ��������: ADC1��DMA��ʽ����
** �������: ��
** �������: ��
***********************************************************/
void ADC1_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;//����ADC�ṹ��
  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	ADC_DeInit(ADC1);
  
  /*��ΪADC1��6ͨ��ģ�������GPIO��ʼ������*/
  //PA2,3,4,5,6,7����Ϊģ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 
  
  /*����ΪADC1������*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1�����ڶ���ģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//ģ��ת�������ڵ�ͨ��
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ģ��ת�������ڵ���ɨ��
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC�����Ҷ���
  ADC_InitStructure.ADC_NbrOfChannel = 1;//ת����ADCͨ������ĿΪ1
  ADC_Init(ADC1, &ADC_InitStructure);//Ҫ�����²�����ʼ��ADC_InitStructure

  /* ����ADC1��1��������ͨ�����������ǵ�ת��˳��Ͳ���ʱ��*/ 
  //ת��ʱ��Tconv=����ʱ��+12.5������
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_7Cycles5); //ADC1ͨ��2ת��˳��Ϊ1������ʱ��Ϊ7.5������ 
 
  
 /* ʹ�� ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* ��λ ADC1 ��У׼�Ĵ��� */   
	ADC_ResetCalibration(ADC1);
	/* �ȴ� ADC1 У׼�Ĵ�����λ��� */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* ��ʼ ADC1 У׼ */
	ADC_StartCalibration(ADC1);
	/* �ȴ� ADC1 У׼��� */
	while(ADC_GetCalibrationStatus(ADC1));
	/* ���� ADC1 ת�� */ 
  ADC_ClearFlag(ADC1,ADC_FLAG_EOC); 
}



u16 Get_ADC_Value(void)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1,ADC_SampleTime_7Cycles5); //ADC1ͨ��2ת��˳��Ϊ1������ʱ��Ϊ7.5������ 		  			   
	ADC_Cmd(ADC1, ENABLE);			 
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
  ADC_ClearFlag(ADC1,ADC_FLAG_EOC); 
  return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/*ȷ���������*/
float CurrentZeroPoint;
void CurrentZeroPointConfirm(void)
{
	u16 i;
	float sum = 0;
		for (i = 0; i <10000;i++)
	{
		kalmanfilter((Get_ADC_Value()*1.0f/4096*3.3));
	}
	
	CurrentZeroPoint = sum / 52000.f;
	for (i = 0; i <3000;i++)
	{
		sum +=kalmanfilter((Get_ADC_Value()*1.0f/4096*3.3));
	}
	
	CurrentZeroPoint = sum / 3000.f;
//	CurrentZeroPoint=kalmanfilter((Get_ADC_Value()*1.0f/4096*3.3));
}

///*������ֵ�˲�*/
//float CurrentFitlter(float current)
//{
//	static float current_buff[5] = {0};
//	float sum = 0;
//	u8 i;
//	
//	for ( i = 0;i < 3;i++)
//	{
//		current_buff[i] = current_buff[i+1];
//	}
//	current_buff[3] = current;
//	
//	for ( i = 0;i < 4;i++)
//	{
//		sum += current_buff[i];
//	}
//	
//	return sum / 4.0f;
//	
//}

/*
	mode ȡ0 ����adc�������
			 ȡ1 ����ʵ�ʵ���ֵ ��λ������
*/
float Get_Current(u8 mode)
{
	float tmp;
	
//	  tmp = Get_ADC_Value();	
////  tmp = Get_ADC_Value();	
//	  tmp = (Get_ADC_Value()*1.0f/(4096-0))*3.3;	
//	    tmp=(Get_ADC_Value()*1.0f/(4096-0))*3.3;
    tmp = kalmanfilter((Get_ADC_Value()*1.0f/(4096-0))*3.3)-CurrentZeroPoint;	
	
	if (mode==1)
	{
		tmp = tmp*1000.f/0.1;
//		  tmp = kalmanfilter((Get_ADC_Value()*1.0f/(4096-0))*3.3);	
	}
	
		
	return (float)tmp;
}


