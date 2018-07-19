/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   王老师
**---------------------------------------------------------------
** 文 件 名：   Board.h
** 文件说明：   库文件引入、常用宏定义、板层定义、数据类型定义
*****************************************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

/*---------------------INCLUDES----------------------*/
#include <absacc.h>
#include <intrins.h>
#include <math.h>
#include <string.h>
#include ".\Board\STC8A8K64S4A12.h"



/*---------------------DEFINES-----------------------*/
#define	TRUE	1
#define	FALSE	0

#define PI 3.1415926

#define MAKEWORD(high,low) (((high)<<8)|(low))
#define TEST P2_6


/*---------------------TYPEDEF-----------------------*/
typedef signed char int8;
typedef unsigned char uint8;

typedef signed int int16;
typedef unsigned int uint16;

typedef signed long int32;
typedef unsigned long uint32;

typedef float f32;



#endif
