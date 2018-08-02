/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-14
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Wifi.h
** �ļ�˵����   wifi����ģ��
*****************************************************************/
#ifndef _WIFI_H_
#define _WIFI_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"
#include ".\System\System.h"

/*---------------------DEFINES-----------------------*/
extern char xdata *JSONp;

/*---------------------DECLARES----------------------*/
void WifiLink(void);
void WifiBeat(void);
//void Wifidat(int8 rank1,uint32 DAT);
//uint16 JsonMakePak1(int8 rank,uint32 value);
uint16 JsonMakePak2();
uint16 JsonKeyRec(char *JsonKey);
void WifidatPack();
#endif