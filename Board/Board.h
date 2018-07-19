/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-07
** ��    �ߣ�   ����ʦ
**---------------------------------------------------------------
** �� �� ����   Board.h
** �ļ�˵����   ���ļ����롢���ú궨�塢��㶨�塢�������Ͷ���
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
