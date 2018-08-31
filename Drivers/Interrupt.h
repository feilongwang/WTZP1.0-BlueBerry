/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Interrupt.h
** 文件说明：   中断服务程序（目前未使用）
*****************************************************************/
#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include "UrstTest.h"

/*---------------------DEFINES-----------------------*/
extern char xdata LCDAck[25];
extern char xdata WIFIAck[64];
extern uint16 Timecount1;

/*---------------------DECLARES----------------------*/
void InterruptKeyIsr(void);
void Uart1Isr(void);
void Uart2Isr(void);
void Uart3Isr(void);
void Time0_Isr(void);

#endif