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
** 更新日志：   2018-7-14 串口1,2,3都可用了
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "UrstTest.h"

/*---------------------VARIABLES---------------------*/
uint8 Urst2Rec=0;
uint8 Urst2TI=0;
uint8 Urst2RI=0;
uint8 Urst3TI=0;
uint8 Urst3RI=0;
uint8 Urst3Rec=0;

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
** 函 数 名： UartSend1_str((char *dat)
** 函数说明： 多字节发送程序//先送低8位再送高8位
**---------------------------------------------------------------------
** 输入参数： uint8（发送字符串的首地址）
** 返回参数： 无
***********************************************************************/
void UartSend1_str(char *dat) 
{
	while(*dat)
	{
		UartSend1(*dat);
		dat++;
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
	Urst2TI=1;
	while(Urst2TI);
}
/***********************************************************************
** 函 数 名： UartSend2_str(char *dat)
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
** 函数说明： 字符串接收程序
**---------------------------------------------------------------------
** 输入参数： 接收字符串首地址
** 返回参数： uint8
***********************************************************************/
uint8 UartRec2(char *p)
{
	while(Urst2RI)
	{
		Urst2RI=0;
		Urst2Rec = S2BUF;
		*p=Urst2Rec;
		if(*p){Urst2RI=1;p++;}
		else 	{Urst2RI=0;*p=0;return 1;}
	}
	return 0;
}
/***********************************************************************
** 函 数 名： InitUart3()
** 函数说明： 串口3异步通信初始化程序，选择定时器3
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitUart3(void)
{
	S3CON |= 0x40;		//串口3选择定时器3为波特率发生器
  InitTime3();
}
/***********************************************************************
** 函 数 名： UartSend3(unsigned char dat)
** 函数说明： 单字节发送程序
**---------------------------------------------------------------------
** 输入参数： uint8
** 返回参数： 无
***********************************************************************/
void UartSend3(unsigned char dat)
{
	S3BUF=dat;
	Urst3TI=1;
	while(Urst3TI);
}
/***********************************************************************
** 函 数 名： UartSend3_str(char *dat)
** 函数说明： 多字节发送程序//先送低8位再送高8位
**---------------------------------------------------------------------
** 输入参数： uint8（发送字符串的首地址）
** 返回参数： 无
***********************************************************************/
void UartSend3_str(char *dat)
{
	while(*dat)
	{
		UartSend3(*dat++);
	}
}
/***********************************************************************
** 函 数 名： UartRec3()
** 函数说明： 字符串接收程序
**---------------------------------------------------------------------
** 输入参数： 接收字符
** 返回参数： uint8 接收字符串的首地址
***********************************************************************/
uint8 UartRec3(char *p)
{
	while(Urst3RI)
	{
		Urst3RI=0;
		Urst3Rec = S3BUF;
		*p=Urst3Rec;
		if(*p){Urst3RI=1;p++;}
		else 	{Urst3RI=0;*p=0;return 1;}
	}
	return 0;
}