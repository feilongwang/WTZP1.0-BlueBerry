/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-19
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Wifi.c
** �ļ�˵����   wifi����ģ��
*****************************************************************/
/*---------------------INCLUDES----------------------*/
#include "Wifi.h"

/*---------------------VARIABLES---------------------*/
char xdata Link[110]="{\"t\": 1,\"device\": \"BlueBerry\",\"key\":\"d9b8d549677e42d989f35401b6c0790f\",\"ver\":\"v1.0\"}";
char xdata Date[300]="{\"t\":3,\"datatype\":1,\"datas\":{\"Ph";
char xdata DateMid1[10]="\":0";
char xdata DateMid2[10]=",\"";
char xdata DateBack[14]="},\"msgid\":1}";
char xdata BeatQus[7]="$#AT#\r";
char KeyName[7][9]={{"Ph"},{"LiquidT"},{"Humidity"},{"Lux"},{"Temp"},{"EC"},{"CO2"}};//������ʶ����
int8 KeyLen[7]={2,7,8,3,4,2,3};
char xdata Ack[64],*JSONp=Ack;
extern uint16 DateLiquidT;extern uint16 DateCO2;extern uint16 DatePh;extern uint16 DateHumidity;
extern uint16 DateTemp;extern int16 DateEc;extern uint32 DateLux;

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** �� �� ���� WifiRec()
** ����˵���� ��������WiFiģ���JSON
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� uint8
***********************************************************************/
uint8 WifiRec()
{
	int j=0;
	char k;
	k=UartRec2(Ack);
	{
		while(!k)
		{j++;if(j>300)return 0;}//�ȴ��޹�����0
		*JSONp=k;
	}while(JSONp++);
	return 1;//�ɹ�����1
}
/***********************************************************************
** �� �� ���� JsonKeyRec()
** ����˵���� ��ȡJSON��ֵ
**---------------------------------------------------------------------
** ��������� Ŀ���������ֵ�����ַ
** ���ز����� uint16,��ֵ�ĵ�ַ
***********************************************************************/
uint16 JsonKeyRec(char *JsonKey)
{
	char *value;
	char *JsonKeyStart;//������ʼ�ĵ�ַ
	char *JsonKeyEnd;//���������ĵ�ַ
	char JsonKeyLength;//��������
	JsonKeyStart=strstr(JSONp,JsonKey);
	JsonKeyLength=strlen(JsonKey);
	JsonKeyEnd=JsonKeyStart+JsonKeyLength;
	if(JsonKeyStart != 0 && *(JsonKeyStart - 1) == '\"' && *(JsonKeyEnd) == '\"' && *(JsonKeyEnd + 1) == ':' && *(JsonKeyEnd + 2) == '\"' )
	{
		value=JsonKeyEnd+2;
	}
	return value;
}
/***********************************************************************
** �� �� ���� WifiLink()
** ����˵���� ����ƽ̨̨��������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void WifiLink()
{
	UartSend2_str(Link);
}
/***********************************************************************
** �� �� ���� WifiBeat()
** ����˵���� ����ƽ̨̨������������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void WifiBeat()
{
	UartSend2_str(BeatQus);
}
/***********************************************************************
** �� �� ���� JsonMakePak1()
** ����˵���� ���(ֻ���һ������)
**---------------------------------------------------------------------
** ��������� int8 rank,uint32 value
** ���ز����� uint16,��ֵ�ĵ�ַ
***********************************************************************/
uint16 JsonMakePak1(int8 rank,uint32 value)
{
	char DateKeyStart=30;
	uint8 DateValueLen;
	switch(rank)
	{
		case 0:strcpy(Date+DateKeyStart,KeyName[0]);break;//ʹ����ָ��ָ�������׵�ַ
		case 1:strcpy(Date+DateKeyStart,KeyName[1]);break;
		case 2:strcpy(Date+DateKeyStart,KeyName[2]);break;
		case 3:strcpy(Date+DateKeyStart,KeyName[3]);break;
		case 4:strcpy(Date+DateKeyStart,KeyName[4]);break;
		case 5:strcpy(Date+DateKeyStart,KeyName[5]);break;
		case 6:strcpy(Date+DateKeyStart,KeyName[6]);break;
	}
	DateValueLen=sprintf(DateMid1+2,"%d",value);
	strcat(Date,DateMid1);
	strcat(Date,DateBack);
	return Date;
}
/***********************************************************************
** �� �� ���� JsonMakePak2()
** ����˵���� ���(���һ�鴫��������)
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� uint16,��ֵ�ĵ�ַ
***********************************************************************/
uint16 JsonMakePak2()
{
	uint8 DateValueLen=0;
	uint16 value1=0;
	int8 i=0;
	char xdata *DateKeyStart;
	DateKeyStart=Date+30;//ʹ����ָ��ָ�������׵�ַ
	for(i=0;i<7;i++)
	{
		strcpy(DateKeyStart,KeyName[i]);
		DateKeyStart=DateKeyStart+KeyLen[i];
		*DateKeyStart=0;
		switch(i)
		{
			case 0:value1=DatePh;break;//�������
			case 1:value1=DateLiquidT;break;
			case 2:value1=DateHumidity;break;
			case 3:value1=DateLux;break;
			case 4:value1=DateTemp;break;
			case 5:value1=DateEc;break;
			case 6:value1=DateCO2;break;
		}
		DateValueLen=sprintf(DateMid1+2,"%d",value1);
		strcat(Date,DateMid1);
		DateKeyStart=DateKeyStart+DateValueLen+2;
		*DateKeyStart=0;
		if(i!=6)
		{
			strcat(Date,DateMid2);
			DateKeyStart=DateKeyStart+2;
		}
	}
	strcat(Date,DateBack);
	return Date;
}
/***********************************************************************
** �� �� ���� Wifidat()
** ����˵���� ����һ������������
**---------------------------------------------------------------------
** ��������� int8 rank,int16 DAT
** ���ز����� ��
***********************************************************************/
void Wifidat(int8 rank1,uint32 DAT)
{
	JsonMakePak1(rank1,DAT);
	UartSend2_str(Date);
}
/***********************************************************************
** �� �� ���� WifidatPackt()
** ����˵���� ����һ�鴫��������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
void WifidatPack()
{
	JsonMakePak2();
	UartSend2_str(Date);
}
