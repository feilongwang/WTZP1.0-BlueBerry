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


/*---------------------DECLARES----------------------*/
void InitUart1(void);//��ʼ������1
void UartSend1(unsigned char dat);
void UartSend1_Byte(unsigned long dat,unsigned char n);//���ô˺�������
void InitUart2(void);
void UartSend2(unsigned char dat);
void UartSend2_str(unsigned char *dat) ;
uint8 UartRec2(void);

#endif