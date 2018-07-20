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


/*---------------------VARIABLES---------------------*/
extern uint8 Urst2TI;
extern uint8 Urst2Rec;
extern uint8 Urst2RI;

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
  IE2 = 0x01;//打开串口2接收中断
  EA = 1;//总中断打开
}
/***********************************************************************
** 函 数 名： Uart1Isr()
** 函数说明： 串口1中断服务程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
/*
void Uart1Isr() interrupt 4 using 1
{
	if(TI)
	{
		TI=0;
	}
	if(RI)
	{
		RI=0;
	}
} */
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
	}
}