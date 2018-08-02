/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-14
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Wifi.h
** 文件说明：   wifi功能模块
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