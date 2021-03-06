/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   王老师
**---------------------------------------------------------------
** 文 件 名：   Main.c
** 文件说明：   主函数
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include ".\System\System.h"


/*---------------------VARIABLES---------------------*/


/*---------------------FUNCTIONS---------------------*/

/***********************************************************************
** 函 数 名： main()
** 函数说明： 主函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void main(void)
{
	//系统初始化
	InitSystem();

	//系统工作
	StartSystem();
}