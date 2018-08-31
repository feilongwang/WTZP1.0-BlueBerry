/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Delay.h
** 文件说明：   延时程序汇总(晶振24Mhz)
*****************************************************************/
#ifndef _DELAY_H_
#define _DELAY_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"

/*---------------------DECLARES----------------------*/
void delay10ms(void);
void delay1us(unsigned int b);
//void delay1s(void);
void Delay5us(void);
void delay_ms(uint16 k);
void Delay_N10us(uint8 n);
void Delay_100us(void);
void TDelay_N1ms(uint8 n);

#endif