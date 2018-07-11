/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   王老师
**---------------------------------------------------------------
** 文 件 名：   System.c
** 文件说明：   系统功能
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include ".\Drivers\Drivers.h"
#include ".\Modules\Modules.h"
#include ".\System\System.h"

/*---------------------VARIABLES---------------------*/



/*---------------------FUNCTIONS---------------------*/

/***********************************************************************
** 函 数 名： InitSystem()
** 函数说明： 初始化系统
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitSystem(void)
{
	InitI2C();
	InitUart1();
	LUX_Init();
  Init_AD();
	InitPara();
}

/***********************************************************************
** 函 数 名： StartSystem()
** 函数说明： 运行系统
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void StartSystem(void)
{
	//存储变量区
	/*int LiquidT*/;
	//
		DS18B20Start();
	 

	//
    while(1)
    {
			DS18B20Start();
			//delay1s();
			delay1s();
			//LiquidT=DS18B20();
			//UartSend_Byte(LiquidT,2);
			//UartSend_Byte(Get_Lux(),4);
			UartSend_Byte(ph(),2);
    }

}

