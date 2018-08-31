/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Interrupt.c
** 文件说明：   中断服务程序（目前未使用）
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "Interrupt.h"
extern char xdata *JSONp;
uint16 Timecount1=0;
extern uint16 Timecount2_MOS1;//计算十秒
extern uint16 Timecount1_MOS1;//每一秒储存
extern uint16 Timecount1_MOS2;//每一秒储存
extern uint16 Timecount2_MOS2;//每十秒储存
extern uint16 Timecount1_MOS3;//每一秒储存
extern uint16 Timecount2_MOS3;//每十秒储存
extern uint16 Timecount1_MOS4;//每一秒储存
extern uint16 Timecount2_MOS4;//每十秒储存
extern uint8 MOSTimeCotrol;
extern char MOSCntFlag;

/*---------------------VARIABLES---------------------*/
extern uint8 Urst2TI;
extern uint8 Urst2Rec;
extern uint8 Urst2RI;
extern uint8 LCDReccount;
extern uint8 WIFIReccount;//WIFI数组标志位
extern uint16 Time_MOS[4][2];

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： KeyIsr()
** 函数说明： 中断服务程序,开关
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InterruptKeyIsr()
{
  IE2 = 0x09;//打开串口2,3接收中断
	ET0=1; //打开定时器0中断
	//ES = 1; //打开串口1中断
  EA = 1;//总中断打开
}
/***********************************************************************
** 函 数 名： Uart1Isr()
** 函数说明： 串口1中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
		WIFIAck[WIFIReccount]=SBUF;//修改此处改变接收的字符串
		WIFIReccount++;
	}
}*/
/***********************************************************************
** 函 数 名： Uart2Isr()
** 函数说明： 串口2中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： Uart3Isr()
** 函数说明： 串口3中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
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
** 函 数 名： Time0_Isr()
** 函数说明： 定时器0中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Time0_Isr() interrupt 1 using 1//最后记得计算一下时间正确
{
	Timecount1++;
	if(Timecount1%85==0)
	{
		if(MOSTimeCotrol)
		{
			Timecount1_MOS1++;//每一秒储存
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
			Timecount2_MOS1++;//每十秒储存
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