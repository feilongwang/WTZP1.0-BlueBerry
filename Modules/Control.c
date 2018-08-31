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
char AutoCrolAck[4]={0,0,0,0};
char MOSCntFlag=0;
char MesureMode=0;//1-on 0-off
char AutoControlMode=0;//1-on 0-off
char ControlKeyName[6][15]={"PhControl","BNutAdd","WaterCircule","ANutAdd","data","apitag"};//�ÿ���ʶ����
int16 PrmEC;
int16 PrmPH;
extern uint8 LCDReccount;
extern uint16 Timecount1;
uint16 Timecount1_MOS1=0;//ÿһ�봢��
uint16 Timecount2_MOS1=0;//ÿʮ�봢��
uint16 Timecount1_MOS2=0;//ÿһ�봢��
uint16 Timecount2_MOS2=0;//ÿʮ�봢��
uint16 Timecount1_MOS3=0;//ÿһ�봢��
uint16 Timecount2_MOS3=0;//ÿʮ�봢��
uint16 Timecount1_MOS4=0;//ÿһ�봢��
uint16 Timecount2_MOS4=0;//ÿʮ�봢��
uint8 MOSTimeCotrol=0;//0000 0000 ��ʼ��ʱ1bitMOS1 2bitMOS2 3bitMOS3 4bitMOS4 ��ʱ��ɱ�־λ5bitMOS1 6bitMOS2 7bitMOS3 8bitMOS4 
uint16 Time_MOS[4][2];//4-MOS�ܱ�ţ�3-ʱ�䣬��-ʱ(ת����ʮ����)

/*---------------------FUNCTIONS---------------------*/
/*{
MOS1=0;PH
MOS2=0;BҺ
MOS3=0;ˮѭ��
MOS4=0;AҺ
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
		case 0:MOS1=(!Switch)?0:1;break;
		case 1:MOS2=(!Switch)?0:1;break;
		case 2:MOS3=(!Switch)?0:1;break;
		case 3:MOS4=(!Switch)?0:1;break;
	}
}
/***********************************************************************
** �� �� ���� MOSArb()
** ����˵���� MOS�ܵĿ����ٲ�
**---------------------------------------------------------------------
** ��������� uint8 MOSNum����Ҫ�ٲõ�MOS��ţ�
** ���ز����� uint8,�õ�״̬��0-�أ�1-��,FF-û�бò���
***********************************************************************/
uint8 MOSArb()
{
	static uint8 HighInterruptCnt=0;
	//�ٲ�ԭ���˹�����ƽ̨ͬ����߼����жϣ����Ⱥ��жϣ����Զ��������ڵͼ����ж�
						UartSend1_Byte(HighControlAckFlag,1);
						UartSend1_Byte(ControlAckFlag,1);
						UartSend1_Byte(AutoControlMode,1);
	if((!HighControlAckFlag)&&ControlAckFlag&&AutoControlMode)//����ƽ̨���˹��޲���ʱ���Զ�������Ӧ
	{
		MOSControl(0,MOSAuto[0]);//���Ʊ�
		MOSControl(1,MOSAuto[1]);
		MOSControl(2,MOSAuto[2]);
		MOSControl(3,MOSAuto[3]);
		ControlAckFlag=0;//�����־
		MOSHand[0]=MOSAuto[0];//ͳһ��״̬
		MOSHand[1]=MOSAuto[1];
		MOSHand[2]=MOSAuto[2];
		MOSHand[3]=MOSAuto[3];
		return 0;
	}
	else if(HighControlAckFlag&ControlAckFlag)//��ƽ̨�����˹�����ʱ�������Զ�������Ӧ
	{
		MOSControl(0,MOSHand[0]);//���Ʊ�
		MOSControl(1,MOSHand[1]);
		MOSControl(2,MOSHand[2]);
		MOSControl(3,MOSHand[3]);
		ControlAckFlag=0;//�����־���߼��жϲ������´θ߼��жϲ���ʱ���
		MOSAuto[0]=MOSHand[0];//ͳһ��״̬
		MOSAuto[1]=MOSHand[1];
		MOSAuto[2]=MOSHand[2];
		MOSAuto[3]=MOSHand[3];
		HighInterruptCnt++;
		if(HighInterruptCnt==2)//����߼��жϱ�־
		{
			HighInterruptCnt=0;
			HighControlAckFlag=0;
		}
		return 0;
	}
	else if(!ControlAckFlag)//�ޱò���ʱ��Ӧ
	{
		return 0XFF;
	}
	return 0XFF;
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
	/*PrmEC=IapRead(0x0102);
  PrmEC=PrmEC<<8;
  PrmEC=PrmEC|IapRead(0x0101);//��ȡEC����ֵ
	PrmPH=IapRead(0x0100);//��ȡPH����*/
	PrmPH=0x1388;//5000
	PrmEC=0x03E8;//1000
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
	char Ackcmp[4]={0,0,0,0},i,j;
	char OptionCode;//������
	i=LCDRec();//���ձ�־λ
	if(i)//�˹��ֳ�����
	{
		LCDAck[LCDReccount]=0;
		OptionCode=LCDAnalyse();
		switch(OptionCode)
		{
			case 0x10:MOSHand[0]=0;i=0;break;
			case 0x11:MOSHand[0]=1;i=0;break;
			case 0x20:MOSHand[1]=0;i=0;break;
			case 0x21:MOSHand[1]=1;i=0;break;
			case 0x30:MOSHand[2]=0;i=0;break;
			case 0x31:MOSHand[2]=1;i=0;break;
			case 0x40:MOSHand[3]=0;i=0;break;
			case 0x41:MOSHand[3]=1;i=0;break;
			case 0xF1:MesureMode=1;break;
			case 0xF4:MesureMode=0;break;
			case 0xF2:AutoControlMode=1;HighControlAckFlag=0;MesureMode=0;MOSTimeCotrol=0;ControlAckFlag=0;ControlAckFlag=1;for(j=0;j<3;j++){AutoCrolAck[j]=0;}TR0=0;Timecount1=0;break;//�����Զ����Ʊ�����λ
			case 0xF3:AutoControlMode=0;break;
			default:i=0xFF;
		}
		LCDAck[1]=0;
		if(!i)
		{
			HighControlAckFlag=1;
			ControlAckFlag=1;
		}
	}
	if(Urst2Rec)//��ƽ̨����
	{
		
		NetKey=JsonKeyRec(ControlKeyName[5],WIFIAck);
		for(i=0;i<4;i++)
		{
			OptionCode=JsonKeyCmp(ControlKeyName[i],NetKey);//�˴����ں�������ֵ��ת
			Ackcmp[i]=!OptionCode;
			if(Ackcmp[i])
			{
				NetData=JsonKeyRec(ControlKeyName[4],WIFIAck)-1;
				MOSHand[i]=*NetData-0x30;
				HighControlAckFlag=1;
				ControlAckFlag=1;
			}
		}
		Urst2Rec=0;
	}
}
/*
void TimeMesRec()
{
	char i,cnt=0;
	uint16 t1,t2,t3;
	if(ControlPrmFlag)//�˹��ֳ�����
	{
		//for(i=0;i<3;i++)
		{
			UartSend1_str(LCDAck+9);
			LCDReccount=0;
			LCDTypeRead(3,2);
			
			while(cnt>200)cnt++;cnt=0;
						UartSend1_str(LCDAck+9);
			t1=atoi(LCDAck+9);
						LCDReccount=0;
			UartSend1_Byte(t1,1);
			LCDTypeRead(3,3+i*3);
						while(cnt>200)cnt++;cnt=0;
			t2=atoi(LCDAck+8);
			UartSend1_Byte(t2,1);
						LCDReccount=0;
			LCDTypeRead(3,4+i*3);
						while(cnt>200)cnt++;cnt=0;
			t3=atoi(LCDAck+8);
			UartSend1_Byte(t3,1);
			if((t1+t2+t3)!=0)
			{
				TimeConvert(t1,t2,t3,i);
				MOSAuto[i]=1;
				HighControlAckFlag=1;
				ControlAckFlag=1;
			}
		}
		ControlPrmFlag=0;
	}
}*/
/***********************************************************************
** �� �� ���� AutoControl()
** ����˵���� ϵͳ�Զ����ƿ��ú���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AutoControl()
{
	char i;
	UartSend1_Byte(AutoCrolAck[0],1);
	for(i=0;i<3;i++)
	{
		if(AutoCrolAck[i]==0)
		{
			AutoControlOpen();
			AutoCrolAck[i]++;
		}
	}
}
/***********************************************************************
** �� �� ���� AutoControlOpen()
** ����˵���� ϵͳ�Զ����ƿ��ú���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AutoControlOpen()
{
	char ControlSecond[4]={0,0,0,0},i;//0-MOS1 1-MOS2
	//char ZFFlag[2];//����������־
	//char AddLiquidSecond=1.5;//(ml)ÿһ�������Һ����
	//char HoldLquidV=1;//(L)ϵͳ��Һ�����
	uint16 Difference_value[4];//0-MOS1 1-MOS2
	if(1)
	{
		Difference_value[0]=abs(DatePh-PrmPH);
		/*for(i=0;i<3;i++)
		{
			if(Difference_value[i]&80){Difference_value[i]=abs(Difference_value[i]);ZFFlag[i]=1;}
		}*/
		if(Difference_value[0]>=500)
		{
			ControlSecond[0]=Difference_value[0]/500;
			TimeConvert(ControlSecond[0],0,0,0);
			MOSAuto[0]=1;
			ControlAckFlag=1;
	UartSend1_Byte(ControlAckFlag,1);
		}
		Difference_value[1]=abs(DateEc-PrmEC);
		if(Difference_value[1]>=400)
		{
			ControlSecond[1]=Difference_value[1]/400;
			TimeConvert(ControlSecond[1],0,0,1);
			MOSAuto[1]=1;
			ControlAckFlag=1;
		}
		ControlSecond[2]=ControlSecond[0]>=ControlSecond[1]?ControlSecond[0]:ControlSecond[1];
		if(ControlSecond[2]&&(!AutoCrolAck[2]))
		{
			TimeConvert(ControlSecond[2]*10,0,0,2);
			MOSAuto[2]=1;
			ControlAckFlag=1;
		}
	}
}
/***********************************************************************
** �� �� ���� TimeConvert()
** ����˵���� ʱ�䴫�ݺ���
**---------------------------------------------------------------------
** ��������� uint8 Time_second//�����,uint16 Time_mintius//���ӿ���,uint16 Time_hours_MOS1;//Сʱ����,uint8 MosN//MOS�ܱ��
** ���ز����� ��
***********************************************************************/
void TimeConvert(uint8 Time_second,uint16 Time_mintius,uint16 Time_hours,uint8 MosN)
{
	switch(MosN)
	{
		case 0:MOSTimeCotrol|=0x01;TR0=1;Time_MOS[0][0]=Time_second+Time_mintius*60,Time_MOS[0][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS1��ʱ����
		case 1:MOSTimeCotrol|=0x02;TR0=1;Time_MOS[1][0]=Time_second+Time_mintius*60,Time_MOS[1][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS2��ʱ����
		case 2:MOSTimeCotrol|=0x04;TR0=1;Time_MOS[2][0]=Time_second+Time_mintius*60,Time_MOS[2][1]=Time_hours*360+Time_MOS[0][0]/10;;break;//MOS3��ʱ����
		case 3:MOSTimeCotrol|=0x08;TR0=1;Time_MOS[3][0]=Time_second+Time_mintius*60,Time_MOS[3][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS4��ʱ����
	}
}
/***********************************************************************
** �� �� ���� TimeCnt()
** ����˵���� ʱ����㺯��
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void TimeCnt()
{
	if(MOSTimeCotrol)
	{
		if(MOSTimeCotrol&0x01)
		{
			if(MOSCntFlag&0x01&&MOSCntFlag&0x10)
			{MOSTimeCotrol|=0x10;MOSCntFlag=0;}
		}
		if(MOSTimeCotrol&0x02)
		{
			if(MOSCntFlag&0x02&&MOSCntFlag&0x20)
			{MOSTimeCotrol|=0x20;MOSCntFlag=0;}
		}
		if(MOSTimeCotrol&0x04)
		{
			if(MOSCntFlag&0x04&&MOSCntFlag&0x40)
			{MOSTimeCotrol|=0x40;MOSCntFlag=0;}
		}
		if(MOSTimeCotrol&0x08)
		{
			if(MOSCntFlag&0x08&&MOSCntFlag&0x80)
			{MOSTimeCotrol|=0x80;MOSCntFlag=0;}
		}
	}
}
/***********************************************************************
** �� �� ���� AutoContolClose()
** ����˵���� ϵͳ�Զ����ƹرú���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AutoContolClose()
{
	TimeCnt();
	if(MOSTimeCotrol)
	{
		if(MOSTimeCotrol&0x10)
		{
			MOSAuto[0]=0;
			MOSTimeCotrol=MOSTimeCotrol&0xEE;
			Timecount1_MOS1=0;Timecount2_MOS1=0;
			if(MOSTimeCotrol&0x40)
			{
					AutoCrolAck[0]=0;
			}
			ControlAckFlag=1;
		}
		if(MOSTimeCotrol&0x20)
		{
			MOSAuto[1]=0;
			MOSTimeCotrol=MOSTimeCotrol&0xDD;
			Timecount1_MOS2=0;Timecount2_MOS2=0;
			if(MOSTimeCotrol&0x40)
			{
					AutoCrolAck[1]=0;
			}
			ControlAckFlag=1;
		}
		if(MOSTimeCotrol&0x40)
		{
			MOSAuto[2]=0;
			MOSTimeCotrol=MOSTimeCotrol&0xBB;
			Timecount1_MOS3=0;Timecount2_MOS3=0;
			AutoCrolAck[2]=0;
			ControlAckFlag=1;
		}
		if(MOSTimeCotrol&0x80)
		{
			MOSAuto[3]=0;
			MOSTimeCotrol=MOSTimeCotrol&0x77;
			Timecount1_MOS4=0;Timecount2_MOS4=0;
			AutoCrolAck[3]=0;
			ControlAckFlag=1;
		}
		if(!MOSTimeCotrol){TR0=0;MesureMode=1;}
	}
}
/***********************************************************************
** �� �� ���� AsmControl()
** ����˵���� ����ϵͳ�ܺ���
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void AsmControl()//����˳�����Ҫ
{
	if(ControlPrmFlag)//�鿴ֲ�����������Ƿ�ı�
	{
		ControlPrm();
		ControlPrmFlag=0;
	}
	MOSMesRec();//��������ָ��
	//TimeMesRec();
	if(AutoControlMode)
	{
		AutoControl();//�Զ�����ָ��
		AutoContolClose();
	}
	MOSArb();//MOS�ܿ����ٲ�
}