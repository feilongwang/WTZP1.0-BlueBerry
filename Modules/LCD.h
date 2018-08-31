/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-30
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   LCD.h
** �ļ�˵����   ������ͨ��
*****************************************************************/
#ifndef _LCD_H_
#define _LCD_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"


/*---------------------DEFINES-----------------------*/
extern char xdata LCDAck[25];
extern uint8 LCDReccount;

/*---------------------DECLARES----------------------*/
void LCDSend(uint8 site,float dat);
uint8 LCDRec(void);
uint8 LCDAnalyse();
void LCDKeyControl(uint8 site,uint8 dat);
void LCDTypeRead(uint8 FaceID,uint8 site);

#endif