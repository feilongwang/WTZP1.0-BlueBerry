/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-21
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Control.c
** �ļ�˵����   �ÿ��ƹ���ģ��
*****************************************************************/
/*---------------------INCLUDES----------------------*/
#include "Control.h"

/*---------------------VARIABLES---------------------*/
/***********************************************************************
** ����˵���� MOS�ܵĿ���״̬�������飬MOSHand���˹��ֳ���������ƽ̨���ƣ���MOSAuto��ϵͳ�Զ����ƣ���0-�أ�1-��
***********************************************************************/
uint8 MOSHand[4]={0,0,0,0},MOSAuto[4]={0,0,0,0};
/***********************************************************************
** ����˵���� ������Ӧ��־��HighControlAckFlag���˹��ֳ���������ƽ̨���ƣ���ControlAckFlag��ϵͳ�Զ����ƣ���ControlPrmFlag�������ı䣩0-�ޣ�1-��
***********************************************************************/
static uint8 HighControlAckFlag=0,ControlAckFlag=0,ControlPrmFlag=1;
char ControlKeyName[6][15]={"ControlPh","","","","data","apitag"};
uint16 PrmEC;
uint16 PrmPH;

/*---------------------FUNCTIONS---------------------*/
/*{
MOS1=0;PH
MOS2=0;EC
MOS3=0;
MOS4=0;
}*///0 off 1 on
/***********************************************************************
** �� �� ���� MOSControl()
** ����˵���� MOS�ܵĿ��ƺ���
**---------------------------------------------------------------------
** ��������� uint8 MOSNum����Ҫ�򿪵�MOS��ţ�uint8 Switch(����״̬)
** ���ز����� �ޣ��õ�״̬��0-�أ�1-��
***********************************************************************/
void MOSControl(uint8 MOSNum,uint8 Switch)
{
	switch(MOSNum)
	{
		case 0:MOS1=Switch;break;
		case 1:MOS2=Switch;break;
		case 2:MOS3=Switch;break;
		case 3:MOS4=Switch;break;
	}
}
/***********************************************************************
** �� �� ���� MOSArb()
** ����˵���� MOS�ܵĿ����ٲ�
**---------------------------------------------------------------------
** ��������� uint8 MOSNum����Ҫ�ٲõ�MOS��ţ�
** ���ز����� uint8,�õ�״̬��0-�أ�1-��,FF-û�бò���
***********************************************************************/
uint8 MOSArb(uint8 MOSNum)
{
	static uint8 HighInterruptCnt=0;
	//�ٲ�ԭ���˹�����ƽ̨ͬ����߼����жϣ����Ⱥ��жϣ����Զ��������ڵͼ����ж�
	if((!HighControlAckFlag)&ControlAckFlag)//����ƽ̨���˹��޲���ʱ���Զ�������Ӧ
	{
		MOSControl(MOSNum,MOSAuto[MOSNum]);//���Ʊ�
		ControlAckFlag=0;//�����־
		MOSHand[MOSNum]=MOSAuto[MOSNum];//ͳһ��״̬
		return MOSAuto[MOSNum];
	}
	else if(HighControlAckFlag&ControlAckFlag)//��ƽ̨�����˹�����ʱ�������Զ�������Ӧ
	{
		MOSControl(MOSNum,MOSHand[MOSNum]);//���Ʊ�
		ControlAckFlag=0;//�����־���߼��жϲ������´θ߼��жϲ���ʱ���
		MOSAuto[MOSNum]=MOSHand[MOSNum];//ͳһ��״̬
		HighInterruptCnt++;
		if(HighInterruptCnt==2)//����߼��жϱ�־
		{
			HighInterruptCnt=0;
			HighControlAckFlag=0;
		}
		return MOSHand[MOSNum];
	}
	else if(!ControlAckFlag)//�ޱò���ʱ��Ӧ
	{
		return 0XFF;
	}
	return 0XFF;
}
/***********************************************************************
** �� �� ���� MOSMesRec()
** ����˵���� MOS�ܿ������ݲɼ�(���˹���������ƽ̨)
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void MOSMesRec()
{
	char *NetData;
	char *NetKey;
	char Ackcmp[4],i;
	if(Urst3Rec)//�˹��ֳ�����
	{
		switch(Urst3Rec)
		{
			case 0x10:MOSHand[0]=0;break;
			case 0x11:MOSHand[0]=1;break;
			case 0x20:MOSHand[1]=0;break;
			case 0x21:MOSHand[1]=1;break;
			case 0x30:MOSHand[2]=0;break;
			case 0x31:MOSHand[2]=1;break;
			case 0x40:MOSHand[3]=0;break;
			case 0x41:MOSHand[3]=1;break;
		}
		Urst3Rec=0;
		HighControlAckFlag=1;
		ControlAckFlag=1;
	}
	if(Urst2Rec)
	{
		(int)NetKey=JsonKeyRec(ControlKeyName[5]);
		Ackcmp[0]=!strcmp(NetKey,ControlKeyName[0]);
		Ackcmp[1]=!strcmp(NetKey,ControlKeyName[1]);
		Ackcmp[2]=!strcmp(NetKey,ControlKeyName[2]);
		Ackcmp[3]=!strcmp(NetKey,ControlKeyName[3]);
		for(i=0;i<4;i++)
		{
			if(Ackcmp[i])
			{
				(int)NetData=JsonKeyRec(ControlKeyName[4]);
				MOSHand[i]=*NetData;
				HighControlAckFlag=1;
				ControlAckFlag=1;
			}
		}
		Urst2Rec=0;
	}
}
/***********************************************************************
** �� �� ���� ControlPrm()
** ����˵���� ֲ���������Ʋ�������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void ControlPrm()
{
	PrmEC=IapRead(0x0102);
  PrmEC=PrmEC<<8;
  PrmEC=PrmEC|IapRead(0x0101);//��ȡEC����ֵ
	PrmPH=IapRead(0x0100);//��ȡPH����
}
/***********************************************************************
** �� �� ���� AutoControl()
** ����˵���� ϵͳ�Զ����Ʊú���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AutoControl()
{
	static char AlamCnt[2]={0,0};//0-PH 1-EC
	if(DatePh>PrmPH)
	{
		AlamCnt[0]++;
		if(AlamCnt[0]>4)
		{
			AlamCnt[0]=0;
			MOSAuto[0]=1;
			ControlAckFlag=1;
		}
	}
	if(DateEc<PrmEC)
	{
		AlamCnt[1]++;
		if(AlamCnt[1]>4)
		{
			AlamCnt[1]=0;
			MOSAuto[1]=1;
			ControlAckFlag=1;
		}
	}
}
/***********************************************************************
** �� �� ���� AsmControl()
** ����˵���� ����ϵͳ�ܺ���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AsmControl()
{
	if(ControlPrmFlag)//�鿴ֲ�����������Ƿ�ı�
	{
		ControlPrm();
		ControlPrmFlag=0;
	}
	AutoControl();//�Զ�����ָ��
	MOSMesRec();//��������ָ��
	MOSArb(0);MOSArb(1);MOSArb(2);MOSArb(3);//MOS�ܿ����ٲ�
}





























