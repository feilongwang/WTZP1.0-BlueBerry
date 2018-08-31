/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-21
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Control.h
** 文件说明：   泵控制功能模块
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
extern char ControlKeyName[6][15];//泵控制识别码
extern uint16 Timecount1_MOS1;//每一秒储存
extern uint16 Timecount2_MOS1;//每十秒储存
extern uint16 Timecount1_MOS2;//每一秒储存
extern uint16 Timecount2_MOS2;//每十秒储存
extern uint16 Timecount1_MOS3;//每一秒储存
extern uint16 Timecount2_MOS3;//每十秒储存
extern uint16 Timecount1_MOS4;//每一秒储存
extern uint16 Timecount2_MOS4;//每十秒储存
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