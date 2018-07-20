/*****************************************************************
**                   ��������ѧ ���´�ҵѧԺ
**                       ������Ӧ�ù���
**---------------------------------------------------------------
** ��Ŀ���ƣ�   WTZP1.0-BlueBerry
** ��    �ڣ�   2018-07-14
** ��    �ߣ�   �����
**---------------------------------------------------------------
** �� �� ����   Wifi.c
** �ļ�˵����   wifi����ģ��(��wifiģ��ͨ��������)
*****************************************************************/
/*---------------------INCLUDES----------------------*/
#include "Wifi.h"

/*---------------------VARIABLES---------------------*/
char xdata Link[110]="{\"t\": 1,\"device\": \"BlueBerry\",\"key\":\"d9b8d549677e42d989f35401b6c0790f\",\"ver\":\"v1.0\"}";
char xdata Date[100]="{\"t\":3,\"datatype\":1,\"datas\":{\"Ph";
char xdata DateMid[10]="\":19";
char xdata DateBack[14]="},\"msgid\":1}";
char xdata BeatQus[7]="$#AT#\r";
char KeyName[7][9]={{"Ph"},{"LiquidT"},{"Humidity"},{"Lux"},{"Temp"},{"EC"},{"CO2"}};//������ʶ����
char xdata Ack[64],*JSONp=Ack;
	


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
	k=UartRec2();
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
uint16 WifiLinkAck(char *JsonKey)
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
** �� �� ���� JsonMakePak()
** ����˵���� ���
**---------------------------------------------------------------------
** ��������� int8 rank,int16 value
** ���ز����� uint16,��ֵ�ĵ�ַ
***********************************************************************/
uint16 JsonMakePak(int8 rank,int16 value)
{
	#define DateKeyStart 30
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
  DateValueLen=sprintf(DateMid+2,"%d",value);
	strcat(Date,DateMid);
	strcat(Date,DateBack);
	return Date;
}
/***********************************************************************
** �� �� ���� Wifidat()
** ����˵���� ��������
**---------------------------------------------------------------------
** ��������� int8 rank,int16 DAT
** ���ز����� ��
***********************************************************************/
void Wifidat(int8 rank1,int16 DAT)
{
	JsonMakePak(rank1,DAT);
	UartSend2_str(Date);
}
