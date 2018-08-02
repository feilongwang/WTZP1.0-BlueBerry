/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-08-02
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   EEPROM.h
** 文件说明：   EEPROM读写功能
*****************************************************************/
#ifndef _EEPROM_H_
#define _EEPROM_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"


/*---------------------DEFINES-----------------------*/


/*---------------------DECLARES----------------------*/
void IapIdle(void);
char IapRead(int addr);
void IapProgram(int addr, char dat);
void IapErase(int addr);
void EEPROMWrite(int addr, char dat);


#endif