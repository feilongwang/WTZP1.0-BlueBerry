/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-08
** ��    �ߣ�   ����� 
**---------------------------------------------------------------
** �� �� ����   UrstTest.h
** �ļ�˵����   �����첽ͨѶ��Ŀǰֻ�д���1��ͷ�ļ�
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
void InitUart1(void);//��ʼ������1
void UartSend1(unsigned char dat);
void UartSend1_Byte(unsigned long dat,unsigned char n);//���ô˺�������
void InitUart2(void);
void UartSend2(unsigned char dat);
void UartSend2_str(unsigned char *dat) ;
uint8 UartRec2(char *p);
void UartSend1_str(char *dat);
void InitUart3(void);
void UartSend3(unsigned char dat);
void UartSend3_str(char *dat);
//uint8 UartRec3()(void);

#endif