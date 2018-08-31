/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-30
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   LCD.h
** 文件说明：   串口屏通信
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