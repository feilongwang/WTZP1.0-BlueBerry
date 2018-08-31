/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-08
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Interrupt.h
** �ļ�˵����   �жϷ������Ŀǰδʹ�ã�
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