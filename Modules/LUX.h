/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-09
** 作    者：   王世许
**---------------------------------------------------------------
** 文 件 名：   LUX.h
** 文件说明：   光照强度测量
*****************************************************************/
#ifndef _LUX_H_
#define _LUX_H_
/*---------------------INCLUDES----------------------*/
#include "./Board/Board.h"
#include ".\Drivers\Drivers.h"

/*---------------------DEFINES-----------------------*/
sbit LUX_SCL=P0^7;
sbit LUX_SDA=P0^6;

/*---------------------DECLARES----------------------*/
void  LUX_Start();
void  LUX_Stop();
void  LUX_SendACK(uint8 ack);
uint8 LUX_RecvACK();
void  LUX_SendByte(uint8 dat);
uint8 LUX_ReadByte();
void  LUX_Single_Write(uint8 REG_Address);    //写入单个字节数据    
void  LUX_Multiple_read(void);                //连续的读取内部寄存器数据
void  InitLUX();
uint32 Get_Lux(void);

#endif

