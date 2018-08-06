# include"stm32f10x_lib.h"
# include"usart.h"
# include<stdio.h>

//void usart_Configuration(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStructure; //GPIO�⺯���ṹ��
//	 USART_InitTypeDef USART_InitStructure;//USART�⺯���ṹ��
//	 USART_ClockInitTypeDef USART_ClockInitStructure;
//	 //ʹ�ܴ���1��GPIOA��AFIO����
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1,ENABLE);
//	 /* Configure USART1 Tx (PA9) as alternate function push-pull */
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//PA9ʱ���ٶ�50MHz
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������
//	 GPIO_Init(GPIOA, &GPIO_InitStructure);
//	 /* Configure USART1 Rx (PA10) as input floating */
//	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
//	 GPIO_Init(GPIOA, &GPIO_InitStructure);
//	 
//	 USART_InitStructure.USART_BaudRate =9600; //������9600
//	 USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8λ����
//	 USART_InitStructure.USART_StopBits = USART_StopBits_1; //1��ֹͣλ
//	 USART_InitStructure.USART_Parity = USART_Parity_No; //��żʧ��
//	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
//	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���͡�����ʹ��
//	
//	 USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
//	 USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;//����ʱ��Ϊ�͵�ƽ
//	 USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;//ʱ�ӵ�һ�����ؽ������ݲ���
//	 USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;//���һλ���ݵ�ʱ�����岻��SCLK���
//	
//	 USART_ClockInit(USART1, &USART_ClockInitStructure);
//	 USART_Init(USART1, &USART_InitStructure);	//��ʼ���ṹ��
//	
//	 USART_Cmd(USART1, ENABLE); //ʹ�ܴ���1	
//}



///*******************************************************************************
//* Function Name  : GPIO_Configuration
//* Description    : ��ʼ��GPIO����
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void GPIO_Configuration(void)
// { //GPIO_InitTypeDef GPIO_InitStructure;

////  /* Configure USARTx_Tx as alternate function push-pull */
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
////  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
////  GPIO_Init(GPIOA, &GPIO_InitStructure);

////  /* Configure USARTx_Rx as input floating */
////  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
////  GPIO_Init(GPIOA, &GPIO_InitStructure);
////	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO�ṹ��	
////	/*��������CLOCK,��ʹ��GPIO֮ǰ����������Ӧ�˵�ʱ��.
////	��STM32����ƽǶ���˵,û������Ķ˽�������ʱ��,Ҳ�Ͳ������,
////	����STM32���ܵ�һ�ּ���,*/
//////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA��ʱ��
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOB��ʱ��

////	/* PA1,2���*/
//////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2; //PA1,PA2����
//////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
//////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
//////	GPIO_Init(GPIOA, &GPIO_InitStructure); //�������ϲ�����ʼ���ṹ��
//////	
////	/*PB1,���*/
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PB1
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
//} 

///**********************************************************
//** ������:u32tostr
//** ��������: ��һ��32λ�ı���datתΪ�ַ����������1234תΪ"1234"
//** �������: dat:��ת��long�͵ı���
//             str:ָ���ַ������ָ�룬ת������ֽڴ��������� 
//** �������: ��
//***********************************************************/
//void u32tostr(unsigned long dat,char *str) 
//{
//	char temp[20];
//	unsigned char i=0,j=0;
//	i=0;
//	while(dat)
//	{
//		temp[i]=dat%10+0x30;
//		i++;
//		dat/=10;
//	}
//	j=i;
//	for(i=0;i<j;i++)
//	{
//	  	str[i]=temp[j-i-1];
//	}
//	if(!i) {str[i++]='0';}
//	str[i]=0;
//}

///**********************************************************
//** ������:USART1_Putc
//** ��������: ����1����һ�ַ�
//** �������: c
//** �������: ��
//***********************************************************/
//void USART1_Putc(unsigned char c)
//{
//    USART1->DR = (u8)c; //Ҫ���͵��ַ������������ݼĴ���  
//	while((USART1->SR&0X40)==0); //�ȴ��������  
//}
///**********************************************************
//** ������:USART1_Puts
//** ��������: ����1����һ�ַ���
//** �������: ָ��str
//** �������: ��
//***********************************************************/
//void USART1_Puts(char * str)
//{
//    while(*str)
//    {
//        USART1->DR= *str++;
//		while((USART1->SR&0X40)==0);//�ȴ��������  
//    }
//}
///**********************************************************
//** ������:UART_Send_Enter
//** ��������: ����1����һ���з�
//** �������: ��
//** �������: ��
//***********************************************************/
//void UART_Send_Enter(void)
//{
//	USART1_Putc(0x0d);
//	USART1_Putc(0x0a);
//}
///**********************************************************
//** ������:UART_Send_Str
//** ��������: ����1����һ�ַ��������س����й���
//** �������: ָ��s
//** �������: ��
//***********************************************************/
//void UART_Send_Str(char *s)
//{
// 
// 	for(;*s;s++)
// 	{
//	 	if(*s=='\n') 
//	  		UART_Send_Enter();
//	 	else
//	  		USART1_Putc(*s);
// 	}
//}
