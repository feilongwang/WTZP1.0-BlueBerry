/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-09
** ��    �ߣ�   ������
**---------------------------------------------------------------
** �� �� ����   LUX.h
** �ļ�˵����   ����ǿ�Ȳ���
*****************************************************************/
#ifndef _LUX_H_
#define _LUX_H_
/*---------------------INCLUDES----------------------*/
#include "./Board/Board.h"
#include ".\Drivers\Drivers.h"

/*---------------------DEFINES-----------------------*/
sbit LUX_SCL=P0^7;
sbit LUX_SDA=P0^6;

/*---------------------DECLARES----------------------*/
void  LUX_Start();
void  LUX_Stop();
void  LUX_SendACK(uint8 ack);
uint8 LUX_RecvACK();
void  LUX_SendByte(uint8 dat);
uint8 LUX_ReadByte();
void  LUX_Single_Write(uint8 REG_Address);    //д�뵥���ֽ�����    
void  LUX_Multiple_read(void);                //�����Ķ�ȡ�ڲ��Ĵ�������
void  InitLUX();
uint32 Get_Lux(void);

#endif

