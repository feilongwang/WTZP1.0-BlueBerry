/*****************************************************************
**                   ����������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-10
** ��    �ߣ�   ����
**---------------------------------------------------------------
** �� �� ����   ph.h
** �ļ�˵����   ��Һph����ͷ�ļ�
*****************************************************************/
#ifndef _ph_H_
#define _ph_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"

/*---------------------DECLARES----------------------*/
void InitPara(void);
uint16 GetADFilter(uint8 n);
uint16 ph(void);


#endif