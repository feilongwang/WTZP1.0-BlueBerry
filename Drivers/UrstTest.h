/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军 
**---------------------------------------------------------------
** 文 件 名：   UrstTest.h
** 文件说明：   串口异步通讯（目前只有串口1）头文件
*****************************************************************/

#ifndef _URETTEST_H_
#define _URESTEST_H_

/*---------------------INCLUDES----------------------*/
#include ".\Board\Board.h"
#include ".\Drivers\Drivers.h"

/*---------------------DEFINES-----------------------*/
extern uint8 Urst2Rec;
extern uint8 Urst2TI;
extern uint8 Urst2RI;
extern uint8 Urst3TI;
extern uint8 Urst3RI;
extern uint8 Urst3Rec;

/*---------------------DECLARES----------------------*/
void InitUart1(void);//初始化串口1
void UartSend1(unsigned char dat);
void UartSend1_Byte(unsigned long dat,unsigned char n);//调用此函数发送
//uint8 UartRec1(char *p);//电脑发送测试
void InitUart2(void);
void UartSend2(unsigned char dat);
void UartSend2_str(unsigned char *dat) ;
//uint8 UartRec2(char *p);
void UartSend1_str(char *dat);
void InitUart3(void);
void UartSend3(unsigned char dat);
void UartSend3_str(char *dat);
//uint8 UartRec3(char *p);

#endif