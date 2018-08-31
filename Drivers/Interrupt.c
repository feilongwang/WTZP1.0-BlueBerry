/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-08
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Interrupt.c
** �ļ�˵����   �жϷ������Ŀǰδʹ�ã�
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "Interrupt.h"
extern char xdata *JSONp;
uint16 Timecount1=0;
extern uint16 Timecount2_MOS1;//����ʮ��
extern uint16 Timecount1_MOS1;//ÿһ�봢��
extern uint16 Timecount1_MOS2;//ÿһ�봢��
extern uint16 Timecount2_MOS2;//ÿʮ�봢��
extern uint16 Timecount1_MOS3;//ÿһ�봢��
extern uint16 Timecount2_MOS3;//ÿʮ�봢��
extern uint16 Timecount1_MOS4;//ÿһ�봢��
extern uint16 Timecount2_MOS4;//ÿʮ�봢��
extern uint8 MOSTimeCotrol;
extern char MOSCntFlag;

/*---------------------VARIABLES---------------------*/
extern uint8 Urst2TI;
extern uint8 Urst2Rec;
extern uint8 Urst2RI;
extern uint8 LCDReccount;
extern uint8 WIFIReccount;//WIFI�����־λ
extern uint16 Time_MOS[4][2];

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** �� �� ���� KeyIsr()
** ����˵���� �жϷ������,����
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void InterruptKeyIsr()
{
  IE2 = 0x09;//�򿪴���2,3�����ж�
	ET0=1; //�򿪶�ʱ��0�ж�
	//ES = 1; //�򿪴���1�ж�
  EA = 1;//���жϴ�
}
/***********************************************************************
** �� �� ���� Uart1Isr()
** ����˵���� ����1�жϷ������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
/*void Uart1Isr() interrupt 4 using 1
{
	if(TI)
	{
		TI=0;
	}
	if(RI)
	{
		RI=0;
		WIFIAck[WIFIReccount]=SBUF;//�޸Ĵ˴��ı���յ��ַ���
		WIFIReccount++;
	}
}*/
/***********************************************************************
** �� �� ���� Uart2Isr()
** ����˵���� ����2�жϷ������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Uart2Isr() interrupt 8 using 1
{
	if (S2CON & 0x02)
	{
		S2CON &= ~0x02;
		Urst2TI=0;
	}
	if (S2CON & 0x01)
	{
		S2CON &= ~0x01;
		Urst2RI=1;
		Urst2Rec = S2BUF;
		WIFIAck[WIFIReccount]=Urst2Rec;
		WIFIReccount++;
	}
}
/***********************************************************************
** �� �� ���� Uart3Isr()
** ����˵���� ����3�жϷ������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Uart3Isr() interrupt 17
{
	if (S3CON & 0x02)
	{
		S3CON &= ~0x02;
		Urst3TI=0;
	}
	if (S3CON & 0x01)
	{
		S3CON &= ~0x01;
		Urst3RI=1;
		Urst3Rec = S3BUF;
		LCDAck[LCDReccount]=Urst3Rec;
		LCDReccount++;
	}
}
/***********************************************************************
** �� �� ���� Time0_Isr()
** ����˵���� ��ʱ��0�жϷ������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void Time0_Isr() interrupt 1 using 1//���ǵü���һ��ʱ����ȷ
{
	Timecount1++;
	if(Timecount1%85==0)
	{
		if(MOSTimeCotrol)
		{
			Timecount1_MOS1++;//ÿһ�봢��
			Timecount1_MOS2++;
			Timecount1_MOS3++;
			Timecount1_MOS4++;
		}
	}
	if(Timecount1==850)
	{
		Timecount1=0;
		if(MOSTimeCotrol)
		{
			Timecount2_MOS1++;//ÿʮ�봢��
			Timecount2_MOS2++;
			Timecount2_MOS3++;
			Timecount2_MOS4++;
		}
	}
	if(MOSTimeCotrol)
	{
		if(MOSTimeCotrol&0x01)
		{
			if(Time_MOS[0][0]==Timecount1_MOS1)MOSCntFlag|=0x01;
			if(Time_MOS[0][1]==Timecount2_MOS1)MOSCntFlag|=0x10;
		}
		if(MOSTimeCotrol&0x02)
		{
			if(Time_MOS[0][0]==Timecount1_MOS2)MOSCntFlag|=0x02;
			if(Time_MOS[0][1]==Timecount2_MOS2)MOSCntFlag|=0x20;
		}
		if(MOSTimeCotrol&0x04)
		{
			if(Time_MOS[0][0]==Timecount1_MOS3)MOSCntFlag|=0x04;
			if(Time_MOS[0][1]==Timecount2_MOS3)MOSCntFlag|=0x40;
		}
		if(MOSTimeCotrol&0x08)
		{
			if(Time_MOS[0][0]==Timecount1_MOS4)MOSCntFlag|=0x08;
			if(Time_MOS[0][1]==Timecount2_MOS4)MOSCntFlag|=0x80;
		}
	}
}