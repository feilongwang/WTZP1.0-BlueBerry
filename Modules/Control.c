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
		case 0:MOS1=Switch;break;
		case 1:MOS2=Switch;break;
		case 2:MOS3=Switch;break;
		case 3:MOS4=Switch;break;
	}
}
/***********************************************************************
** 函 数 名： MOSArb()
** 函数说明： MOS管的开关仲裁
**---------------------------------------------------------------------
** 输入参数： uint8 MOSNum（需要仲裁的MOS序号）
** 返回参数： uint8,泵的状态，0-关，1-开,FF-没有泵操作
***********************************************************************/
uint8 MOSArb(uint8 MOSNum)
{
	static uint8 HighInterruptCnt=0;
	//仲裁原则：人工与云平台同属最高级别中断（由先后判断），自动控制属于低级别中断
	if((!HighControlAckFlag)&ControlAckFlag)//当云平台与人工无操作时，自动控制响应
	{
		MOSControl(MOSNum,MOSAuto[MOSNum]);//控制泵
		ControlAckFlag=0;//清除标志
		MOSHand[MOSNum]=MOSAuto[MOSNum];//统一泵状态
		return MOSAuto[MOSNum];
	}
	else if(HighControlAckFlag&ControlAckFlag)//云平台或者人工操作时，屏蔽自动控制响应
	{
		MOSControl(MOSNum,MOSHand[MOSNum]);//控制泵
		ControlAckFlag=0;//清除标志，高级中断操作在下次高级中断操作时清除
		MOSAuto[MOSNum]=MOSHand[MOSNum];//统一泵状态
		HighInterruptCnt++;
		if(HighInterruptCnt==2)//清除高级中断标志
		{
			HighInterruptCnt=0;
			HighControlAckFlag=0;
		}
		return MOSHand[MOSNum];
	}
	else if(!ControlAckFlag)//无泵操作时响应
	{
		return 0XFF;
	}
	return 0XFF;
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
	char Ackcmp[4],i;
	if(Urst3Rec)//人工现场控制
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
** 函 数 名： ControlPrm()
** 函数说明： 植物生长控制参数调整
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void ControlPrm()
{
	PrmEC=IapRead(0x0102);
  PrmEC=PrmEC<<8;
  PrmEC=PrmEC|IapRead(0x0101);//获取EC参数值
	PrmPH=IapRead(0x0100);//获取PH参数
}
/***********************************************************************
** 函 数 名： AutoControl()
** 函数说明： 系统自动控制泵函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： AsmControl()
** 函数说明： 控制系统总函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void AsmControl()
{
	if(ControlPrmFlag)//查看植物生长参数是否改变
	{
		ControlPrm();
		ControlPrmFlag=0;
	}
	AutoControl();//自动控制指令
	MOSMesRec();//其他控制指令
	MOSArb(0);MOSArb(1);MOSArb(2);MOSArb(3);//MOS管控制仲裁
}





























