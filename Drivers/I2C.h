/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   I2C.h
** 文件说明：   调用单片机内I2C通信模块（目前只有端口3）头文件
*****************************************************************/
#ifndef _I2C_H_
#define _I2C_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"

/*---------------------DEFINES-----------------------*/
sbit    SDA         =   P3^3;
sbit    SCL         =   P3^2;

/*---------------------DECLARES----------------------*/
void InitI2C(void);
void Wait(void);
void Start(void);
void SendData(unsigned char dat);
void RecvACK(void);
uint8 RecvData(void);
void SendACK(void);
void SendNAK(void);
void Stop(void);
	
#endif