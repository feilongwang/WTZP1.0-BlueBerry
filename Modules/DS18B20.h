<<<<<<< HEAD
/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   DS18B20.h
** 文件说明：   溶液温度测量头文件
*****************************************************************/
#ifndef _DS18B20_H_
#define _DS18B20_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"

/*---------------------DEFINES-----------------------*/
#define DQ P1_4

/*---------------------DECLARES----------------------*/
void delayus(unsigned int b);
uint8 DS18B20rest(void);
void write_byte(unsigned char dat);
uint8 read_byte();
uint8 DS18B20Start();//初始化DS18B20
int16 DS18B20();//获得温度

	
=======
/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   DS18B20.h
** 文件说明：   溶液温度测量头文件
*****************************************************************/
#ifndef _DS18B20_H_
#define _DS18B20_H_

/*---------------------INCLUDES----------------------*/
#include <STC8.H>
#include "Board.h"

/*---------------------DEFINES-----------------------*/
#define DQ P14

/*---------------------DECLARES----------------------*/
void delayus(unsigned int b);
unsigned char start(void);
void write_byte(unsigned char dat);
unsigned char read_byte();
unsigned char DS18B20Start();
int DS18B20();

	
>>>>>>> e5d573584f862271cf5337b8bcc1000895a28f7f
#endif