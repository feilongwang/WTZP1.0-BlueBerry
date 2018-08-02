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

/*---------------------DECLARES----------------------*/
void MOSControl(uint8 MOSNum,uint8 Switch);
uint8 MOSArb(uint8 k);
void MOSMesRec();
void AutoControl();
void ControlPrm();
void AsmControl();


#endif