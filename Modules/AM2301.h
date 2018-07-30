/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-30
** ��    �ߣ�   ������
**---------------------------------------------------------------
** �� �� ����   AM2301.h
** �ļ�˵����   ������ʪ��ģ��
*****************************************************************/
#ifndef _AM2301_H_
#define _AM2301_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"


/*---------------------DEFINES-----------------------*/
extern uint16 DateHumidity;
extern uint16 DateTemp;
sbit TEMP_SDA=P1^3; //������Ҫ�޸Ķ˿�

/*---------------------DECLARES----------------------*/
void AM2301Start(void);
unsigned char AM2301SingleRec(void);
unsigned char DataCheck(void);
unsigned int H_T_Caculate(unsigned char a[]);
unsigned char AM2301(void);


#endif