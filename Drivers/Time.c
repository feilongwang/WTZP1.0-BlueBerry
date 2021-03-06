/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Time.c
** 文件说明：   定时器管理
** 更新日志：   2018-7-14 定时器1和2
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "Time.h"

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： InitTime1()
** 函数说明： 启动定时器1
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitTime1()
{
	AUXR &= ~(1<<0); //0-选择定时器1, 1-选择定时器2 AUXR |= (1<<0);
	TMOD = (TMOD&0x0F)|0x00; //定时器1为模式0,16位自动重装
	AUXR |= (1<<6); //12分频设置
  TH1 = 0xFD;
	TL1 = 0x8F;	//baud:9600 fosc=24M
	TR1=1;
}
/***********************************************************************
** 函 数 名： InitTime2()
** 函数说明： 启动定时器2
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitTime2()
{
	AUXR |= 0x14; //选择定时器2,12分频，定时器2为16位自动重装;
  T2H = 0xFD;
	T2L = 0x8F;	//baud:9600 fosc=24M
}
/***********************************************************************
** 函 数 名： InitTime3()
** 函数说明： 启动定时器3
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitTime3()
{
	S3CON = 0x10;		//8位数据,可变波特率
	T4T3M |= 0x02;		//定时器3时钟为Fosc,即1T
	T3L = 0x8F;			//baud:9600 fosc=24M
	T3H = 0xFD;			//
	T4T3M |= 0x08;		//启动定时器3
}
/***********************************************************************
** 函 数 名： InitTime0()
** 函数说明： 启动定时器0
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitTime0()
{
	TMOD = 0x00;  
	TH0 = 0xA2;
	TL0 = 0x40;	//24M,定时1ms
	IP |= 0x02;
	IPH |= 0x02;//调整到最高优先级
}