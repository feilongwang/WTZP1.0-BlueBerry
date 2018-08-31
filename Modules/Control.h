/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-21
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Control.h
** �ļ�˵����   �ÿ��ƹ���ģ��
*****************************************************************/
#ifndef _CONTROL_H_
#define _CONTROL_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"
#include ".\System\System.h"


/*---------------------DEFINES-----------------------*/
#define MOS1 P2_3
#define MOS2 P2_0
#define MOS3 P2_2
#define MOS4 P2_1
extern uint8 MOSHand[4],MOSAuto[4];
extern char ControlKeyName[6][15];//�ÿ���ʶ����
extern uint16 Timecount1_MOS1;//ÿһ�봢��
extern uint16 Timecount2_MOS1;//ÿʮ�봢��
extern uint16 Timecount1_MOS2;//ÿһ�봢��
extern uint16 Timecount2_MOS2;//ÿʮ�봢��
extern uint16 Timecount1_MOS3;//ÿһ�봢��
extern uint16 Timecount2_MOS3;//ÿʮ�봢��
extern uint16 Timecount1_MOS4;//ÿһ�봢��
extern uint16 Timecount2_MOS4;//ÿʮ�봢��
extern uint8 MOSTimeCotrol;
extern char MOSCntFlag;
extern uint16 Time_MOS[4][2];
extern char MesureMode;//1-on 0-off
extern char AutoControlMode;//1-on 0-off

/*---------------------DECLARES----------------------*/
void MOSControl(uint8 MOSNum,uint8 Switch);
uint8 MOSArb();
void MOSMesRec();
void AutoControlOpen();
void AutoContolClose();
void ControlPrm();
void AsmControl();
void AutoControl();
void TimeConvert(uint8 Time_second,uint16 Time_mintius,uint16 Time_hours,uint8 MosN);
void TimeCnt();


#endif