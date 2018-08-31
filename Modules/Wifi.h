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
extern char xdata WIFIAck[64];
extern uint8 WIFIReccount;//WIFI�����־λ
extern char xdata WIFICommendAck[110];
/*---------------------DECLARES----------------------*/
void WifiLink(void);
void WifiBeat(void);
//void Wifidat(int8 rank1,uint32 DAT);
//uint16 JsonMakePak1(int8 rank,uint32 value);
uint16 JsonMakePak2();
char* JsonKeyRec(char *JsonKey,char *JSONp);
void WifidatPack(void);
uint8 JsonKeyCmp(char *JsonKey,char *JSONp);
uint16 WifiComAck(void);
uint16 WifiPack(void);
#endif