/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-07
** ��    �ߣ�   ����ʦ
**---------------------------------------------------------------
** �� �� ����   System.h
** �ļ�˵����   ϵͳ����
*****************************************************************/
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Modules\Modules.h"

/*---------------------DEFINES-----------------------*/
extern uint16 DateLiquidT;
extern uint16 DateCO2;
extern uint16 DatePh;
extern uint16 DateHumidity;
extern uint16 DateTemp;
extern int32 DateEc;
extern uint32 DateLux;

/*---------------------DECLARES----------------------*/
extern void InitSystem(void);
extern void StartSystem(void);


#endif
