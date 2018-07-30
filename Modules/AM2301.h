/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-30
** 作    者：   王飞龙
**---------------------------------------------------------------
** 文 件 名：   AM2301.h
** 文件说明：   环境温湿度模块
*****************************************************************/
#ifndef _AM2301_H_
#define _AM2301_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"


/*---------------------DEFINES-----------------------*/
extern uint16 DateHumidity;
extern uint16 DateTemp;
sbit TEMP_SDA=P1^3; //根据需要修改端口

/*---------------------DECLARES----------------------*/
void AM2301Start(void);
unsigned char AM2301SingleRec(void);
unsigned char DataCheck(void);
unsigned int H_T_Caculate(unsigned char a[]);
unsigned char AM2301(void);


#endif