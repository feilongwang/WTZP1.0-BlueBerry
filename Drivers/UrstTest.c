/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   UrstTest.c
** 文件说明：   串口异步通讯
** 更新日志：   2018-7-14 串口0，1都可用了
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "UrstTest.h"

/*---------------------VARIABLES---------------------*/
uint8 Urst2Rec;
uint8 Urst2busy=0;

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： InitUart1()
** 函数说明： 串口1异步通信初始化程序，选择定时器1
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitUart1()
{
	SCON = 0x50; //(0101 0000) 工作方式为方式1,允许接收
	InitTime1();																																	
}
/***********************************************************************
** 函 数 名： UartSend1(unsigned char dat)
** 函数说明： 单字节发送程序
**---------------------------------------------------------------------
** 输入参数： uint8
** 返回参数： 无
***********************************************************************/
//
void UartSend1(unsigned char dat)
{
	SBUF=dat;
	while(!TI);
	TI=0;
}
/***********************************************************************
** 函 数 名： UartSend1_Byte(unsigned long int dat,unsigned char n)
** 函数说明： 多字节发送程序//先送低8位再送高8位
**---------------------------------------------------------------------
** 输入参数： uint32（发送数据），uint8（发送数据字节数）
** 返回参数： 无
***********************************************************************/
void UartSend1_Byte(unsigned long dat,unsigned char n)
{
	unsigned char i,ch;
	for(i=0;i<n;i++)
	{
		ch=dat;
		UartSend1(ch);
		dat=dat>>8;
	}
}
/***********************************************************************
** 函 数 名： InitUart2()
** 函数说明： 串口1异步通信初始化程序，选择定时器1
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitUart2()
{
	S2CON = 0x50; //(0001 0000) 允许接收,9位数据，有起始与终止位 
	InitTime2();																																	
}
/***********************************************************************
** 函 数 名： UartSend2(unsigned char dat)
** 函数说明： 单字节发送程序
**---------------------------------------------------------------------
** 输入参数： uint8
** 返回参数： 无
***********************************************************************/
void UartSend2(char dat)
{
	S2BUF=dat;
	while(!(S2CON & 0x02));
	S2CON &= ~0x02;
}
/***********************************************************************
** 函 数 名： UartSend2_str(unsigned long int dat,unsigned char n)
** 函数说明： 多字节发送程序//先送低8位再送高8位
**---------------------------------------------------------------------
** 输入参数： uint8（发送字符串的首地址）
** 返回参数： 无
***********************************************************************/
void UartSend2_str(char *dat) 
{
	while(*dat)
	{
		UartSend2(*dat);
		dat++;
	}
}
/***********************************************************************
** 函 数 名： UartRec2()
** 函数说明： 字符接收程序
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： uint8
***********************************************************************/
uint8 UartRec2()
{
	if(S2CON & 0x01)
	{
		S2CON &= ~0x01;
		Urst2Rec = S2BUF;
		return Urst2Rec;
	}
	return 0;
}