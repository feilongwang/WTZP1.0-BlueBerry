/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   王老师
**---------------------------------------------------------------
** 文 件 名：   System.h
** 文件说明：   系统功能
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
