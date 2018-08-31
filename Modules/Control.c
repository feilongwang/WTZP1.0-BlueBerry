/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-21
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Control.c
** 文件说明：   泵控制功能模块
*****************************************************************/
/*---------------------INCLUDES----------------------*/
#include "Control.h"

/*---------------------VARIABLES---------------------*/
/***********************************************************************
** 参数说明： MOS管的开关状态储存数组，MOSHand（人工现场控制与云平台控制），MOSAuto（系统自动控制），0-关，1-开
***********************************************************************/
uint8 MOSHand[4]={0,0,0,0},MOSAuto[4]={0,0,0,0};
/***********************************************************************
** 参数说明： 控制响应标志，HighControlAckFlag（人工现场控制与云平台控制），ControlAckFlag（系统自动控制），ControlPrmFlag（参数改变）0-无，1-有
***********************************************************************/
static uint8 HighControlAckFlag=0,ControlAckFlag=0,ControlPrmFlag=1;
char AutoCrolAck[4]={0,0,0,0};
char MOSCntFlag=0;
char MesureMode=0;//1-on 0-off
char AutoControlMode=0;//1-on 0-off
char ControlKeyName[6][15]={"PhControl","BNutAdd","WaterCircule","ANutAdd","data","apitag"};//泵控制识别码
int16 PrmEC;
int16 PrmPH;
extern uint8 LCDReccount;
extern uint16 Timecount1;
uint16 Timecount1_MOS1=0;//每一秒储存
uint16 Timecount2_MOS1=0;//每十秒储存
uint16 Timecount1_MOS2=0;//每一秒储存
uint16 Timecount2_MOS2=0;//每十秒储存
uint16 Timecount1_MOS3=0;//每一秒储存
uint16 Timecount2_MOS3=0;//每十秒储存
uint16 Timecount1_MOS4=0;//每一秒储存
uint16 Timecount2_MOS4=0;//每十秒储存
uint8 MOSTimeCotrol=0;//0000 0000 开始计时1bitMOS1 2bitMOS2 3bitMOS3 4bitMOS4 计时完成标志位5bitMOS1 6bitMOS2 7bitMOS3 8bitMOS4 
uint16 Time_MOS[4][2];//4-MOS管编号，3-时间，秒-时(转换成十秒制)

/*---------------------FUNCTIONS---------------------*/
/*{
MOS1=0;PH
MOS2=0;B液
MOS3=0;水循环
MOS4=0;A液
}*///0 off 1 on
/***********************************************************************
** 函 数 名： MOSControl()
** 函数说明： MOS管的控制函数
**---------------------------------------------------------------------
** 输入参数： uint8 MOSNum（需要打开的MOS序号）uint8 Switch(开关状态)
** 返回参数： 无，泵的状态，0-关，1-开
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
** 函 数 名： MOSArb()
** 函数说明： MOS管的开关仲裁
**---------------------------------------------------------------------
** 输入参数： uint8 MOSNum（需要仲裁的MOS序号）
** 返回参数： uint8,泵的状态，0-关，1-开,FF-没有泵操作
***********************************************************************/
uint8 MOSArb()
{
	static uint8 HighInterruptCnt=0;
	//仲裁原则：人工与云平台同属最高级别中断（由先后判断），自动控制属于低级别中断
						UartSend1_Byte(HighControlAckFlag,1);
						UartSend1_Byte(ControlAckFlag,1);
						UartSend1_Byte(AutoControlMode,1);
	if((!HighControlAckFlag)&&ControlAckFlag&&AutoControlMode)//当云平台与人工无操作时，自动控制响应
	{
		MOSControl(0,MOSAuto[0]);//控制泵
		MOSControl(1,MOSAuto[1]);
		MOSControl(2,MOSAuto[2]);
		MOSControl(3,MOSAuto[3]);
		ControlAckFlag=0;//清除标志
		MOSHand[0]=MOSAuto[0];//统一泵状态
		MOSHand[1]=MOSAuto[1];
		MOSHand[2]=MOSAuto[2];
		MOSHand[3]=MOSAuto[3];
		return 0;
	}
	else if(HighControlAckFlag&ControlAckFlag)//云平台或者人工操作时，屏蔽自动控制响应
	{
		MOSControl(0,MOSHand[0]);//控制泵
		MOSControl(1,MOSHand[1]);
		MOSControl(2,MOSHand[2]);
		MOSControl(3,MOSHand[3]);
		ControlAckFlag=0;//清除标志，高级中断操作在下次高级中断操作时清除
		MOSAuto[0]=MOSHand[0];//统一泵状态
		MOSAuto[1]=MOSHand[1];
		MOSAuto[2]=MOSHand[2];
		MOSAuto[3]=MOSHand[3];
		HighInterruptCnt++;
		if(HighInterruptCnt==2)//清除高级中断标志
		{
			HighInterruptCnt=0;
			HighControlAckFlag=0;
		}
		return 0;
	}
	else if(!ControlAckFlag)//无泵操作时响应
	{
		return 0XFF;
	}
	return 0XFF;
}
/***********************************************************************
** 函 数 名： ControlPrm()
** 函数说明： 植物生长控制参数调整
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void ControlPrm()
{
	/*PrmEC=IapRead(0x0102);
  PrmEC=PrmEC<<8;
  PrmEC=PrmEC|IapRead(0x0101);//获取EC参数值
	PrmPH=IapRead(0x0100);//获取PH参数*/
	PrmPH=0x1388;//5000
	PrmEC=0x03E8;//1000
}
/***********************************************************************
** 函 数 名： MOSMesRec()
** 函数说明： MOS管控制数据采集(对人工操作和云平台)
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void MOSMesRec()
{
	char *NetData;
	char *NetKey;
	char Ackcmp[4]={0,0,0,0},i,j;
	char OptionCode;//操作码
	i=LCDRec();//接收标志位
	if(i)//人工现场控制
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
			case 0xF2:AutoControlMode=1;HighControlAckFlag=0;MesureMode=0;MOSTimeCotrol=0;ControlAckFlag=0;ControlAckFlag=1;for(j=0;j<3;j++){AutoCrolAck[j]=0;}TR0=0;Timecount1=0;break;//所有自动控制变量复位
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
	if(Urst2Rec)//云平台控制
	{
		
		NetKey=JsonKeyRec(ControlKeyName[5],WIFIAck);
		for(i=0;i<4;i++)
		{
			OptionCode=JsonKeyCmp(ControlKeyName[i],NetKey);//此处用于函数返回值中转
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
	if(ControlPrmFlag)//人工现场控制
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
** 函 数 名： AutoControl()
** 函数说明： 系统自动控制开泵函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： AutoControlOpen()
** 函数说明： 系统自动控制开泵函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void AutoControlOpen()
{
	char ControlSecond[4]={0,0,0,0},i;//0-MOS1 1-MOS2
	//char ZFFlag[2];//数据正负标志
	//char AddLiquidSecond=1.5;//(ml)每一秒加入溶液的量
	//char HoldLquidV=1;//(L)系统总液体体积
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
** 函 数 名： TimeConvert()
** 函数说明： 时间传递函数
**---------------------------------------------------------------------
** 输入参数： uint8 Time_second//秒控制,uint16 Time_mintius//分钟控制,uint16 Time_hours_MOS1;//小时控制,uint8 MosN//MOS管编号
** 返回参数： 无
***********************************************************************/
void TimeConvert(uint8 Time_second,uint16 Time_mintius,uint16 Time_hours,uint8 MosN)
{
	switch(MosN)
	{
		case 0:MOSTimeCotrol|=0x01;TR0=1;Time_MOS[0][0]=Time_second+Time_mintius*60,Time_MOS[0][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS1计时启动
		case 1:MOSTimeCotrol|=0x02;TR0=1;Time_MOS[1][0]=Time_second+Time_mintius*60,Time_MOS[1][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS2计时启动
		case 2:MOSTimeCotrol|=0x04;TR0=1;Time_MOS[2][0]=Time_second+Time_mintius*60,Time_MOS[2][1]=Time_hours*360+Time_MOS[0][0]/10;;break;//MOS3计时启动
		case 3:MOSTimeCotrol|=0x08;TR0=1;Time_MOS[3][0]=Time_second+Time_mintius*60,Time_MOS[3][1]=Time_hours*360+Time_MOS[0][0]/10;break;//MOS4计时启动
	}
}
/***********************************************************************
** 函 数 名： TimeCnt()
** 函数说明： 时间计算函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： AutoContolClose()
** 函数说明： 系统自动控制关泵函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： AsmControl()
** 函数说明： 控制系统总函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void AsmControl()//控制顺序很重要
{
	if(ControlPrmFlag)//查看植物生长参数是否改变
	{
		ControlPrm();
		ControlPrmFlag=0;
	}
	MOSMesRec();//其他控制指令
	//TimeMesRec();
	if(AutoControlMode)
	{
		AutoControl();//自动控制指令
		AutoContolClose();
	}
	MOSArb();//MOS管控制仲裁
}