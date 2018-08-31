/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   I2C.c
** 文件说明：   调用单片机内I2C通信模块（目前只有端口3）
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "I2C.h"

/*---------------------VARIABLES---------------------*/


/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： InitI2C()
** 函数说明： 使能I2C主机（此处使能端口3）
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitI2C()
{
	P_SW2=0xB0;
	I2CCFG = 0xe0;//时钟数选择端口                              
  I2CMSST = 0x00;
}
/***********************************************************************
** 函 数 名： Wait()
** 函数说明： 查询等待函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Wait()
{
	while(!(I2CMSST&0x40));//卡住了
	I2CMSST&=~0x40;
}
/***********************************************************************
** 函 数 名： Start()
** 函数说明： 发送START命令
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Start()
{
	I2CMSCR=0x01;
	Wait();
}
/***********************************************************************
** 函 数 名： SendData(unsigned char dat)
** 函数说明： 写数据到数据缓冲区，并发送
**---------------------------------------------------------------------
** 输入参数： uint8
** 返回参数： 无
***********************************************************************/
void SendData(unsigned char dat)
{
	I2CTXD=dat;//
	I2CMSCR=0x02;
	Wait();
}
/***********************************************************************
** 函 数 名： RecvACK()
** 函数说明： 发送ACK命令
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RecvACK()
{
	I2CMSCR=0x03;
	Wait();
}
/***********************************************************************
** 函 数 名： RecvData()
** 函数说明： 发送RECV命令,并接收数据
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： uint8
***********************************************************************/
uint8 RecvData()
{
	I2CMSCR = 0x04;                             
	Wait();
	return I2CRXD;
}
/***********************************************************************
** 函 数 名： SendACK()
** 函数说明： 设置ACK信号,发送ACK命令
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
/*void SendACK()
{
	I2CMSST = 0x00;                             
	I2CMSCR = 0x05;                             
	Wait();
}*/
/***********************************************************************
** 函 数 名： SendNAK()
** 函数说明： 设置NCK信号,发送ACK信号
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void SendNAK()
{
	I2CMSST = 0x01;                             
	I2CMSCR = 0x05;                             
	Wait();
}
/***********************************************************************
** 函 数 名： Stop()
** 函数说明： 发送STOP命令
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Stop()
{
	I2CMSCR = 0x06;                             
	Wait();
}
