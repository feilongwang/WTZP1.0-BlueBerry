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
char xdata DateBack[14]="},\"msgid\":12}";
char xdata BeatQus[7]="$#AT#\r";
char xdata BeatAck[7]="$OK##\r";
char xdata WIFICommendAck[110]="{\"t\":3,\"datatype\":1,\"datas\":{\"PhControl";	
char KeyName[7][9]={{"Ph"},{"LiquidT"},{"Humidity"},{"Lux"},{"Temp"},{"EC"},{"CO2"}};//������ʶ����
extern uint8 MOSHand[4],MOSAuto[4];
extern char ControlKeyName[6][15];//�ÿ���ʶ����
int8 SensorKeyLen[7]={2,7,8,3,4,2,3};//������ʶ���볤��
int8 ControlKeyLen[4]={9,7,12,7};//�ÿ���ʶ���볤��
char xdata WIFIAck[64];
extern uint16 DateLiquidT;extern uint16 DateCO2;extern int16 DatePh;extern uint16 DateHumidity;
extern uint16 DateTemp;extern int16 DateEc;extern uint32 DateLux;
uint8 WIFIReccount=0;//WIFI�����־λ

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** �� �� ���� JsonKeyRec()
** ����˵���� ��ȡJSON��ֵ
**---------------------------------------------------------------------
** ��������� Ŀ���������ֵ�����ַ,����Ŀ���ַ���
** ���ز����� ��ֵ�ĵ�ַ
***********************************************************************/
char* JsonKeyRec(char *JsonKey,char *JSONp)
{
	char *ValueAddr;
	char *JsonKeyStart;//������ʼ�ĵ�ַ
	char *JsonKeyEnd;//���������ĵ�ַ
	char JsonKeyLength;//��������
	JsonKeyStart=strstr(JSONp,JsonKey);
	JsonKeyLength=strlen(JsonKey);
	JsonKeyEnd=JsonKeyStart+JsonKeyLength;
	if(JsonKeyStart != 0 && *(JsonKeyStart - 1) == '\"' && *(JsonKeyEnd) == '\"' && *(JsonKeyEnd + 1) == ':')
	{
		ValueAddr=JsonKeyEnd+3;
	}
	return ValueAddr;
}
/***********************************************************************
** �� �� ���� JsonKeyCmp()
** ����˵���� �ԱȻ�ȡJSON��ֵ
**---------------------------------------------------------------------
** ��������� JsonKeyĿ���������ֵ�����ַ,JSONp����Ŀ���ַ���
** ���ز����� ��ֵ�ĵ�ַ
***********************************************************************/
uint8 JsonKeyCmp(char *JsonKey,char *JSONp)
{
	char *JsonKeyEnd;//���������ĵ�ַ
	char JsonKeyLength;//��������
	char MiusCount=0,i;
	JsonKeyLength=strlen(JsonKey);
	JsonKeyEnd=JSONp+JsonKeyLength;
	for(i=0;i<4;i++)
	{
		MiusCount=MiusCount+JSONp[i]-JsonKey[i];
	}
	return MiusCount;
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
	uint8 *A_Flag=0;
	uint8 *Q_Flag=0;
	A_Flag=strstr(WIFIAck,BeatQus);
	Q_Flag=strstr(WIFIAck,BeatAck);
	if(A_Flag)
	{
		UartSend2_str(BeatAck);
	}
	if(Q_Flag)
	{
		UartSend2_str(BeatQus);
	}
}
/***********************************************************************
** �� �� ���� JsonMakePak1()
** ����˵���� ���(ֻ���һ������)
**---------------------------------------------------------------------
** ��������� int8 rank,uint32 value
** ���ز����� uint16,��ֵ�ĵ�ַ
***********************************************************************/
/*uint16 JsonMakePak1(int8 rank,uint32 value)
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
}*/
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
		DateKeyStart=DateKeyStart+SensorKeyLen[i];
		*DateKeyStart=0;
		switch(i)
		{
			case 0:value1=DatePh/1000.0;break;//�������
			case 1:value1=DateLiquidT/10.0;break;
			case 2:value1=DateHumidity/10.0;break;
			case 3:value1=DateLux;break;
			case 4:value1=DateTemp/10.0;break;
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
/*void Wifidat(int8 rank1,uint32 DAT)
{
	JsonMakePak1(rank1,DAT);
	UartSend2_str(Date);
}*/
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
/***********************************************************************
** �� �� ���� WifiComAck()
** ����˵���� ����һ������������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
uint16 WifiComAck()
{
	uint8 DateValueLen=0;
	uint16 value1=0;
	int8 i=0;
	char xdata *DateKeyStart;
	DateKeyStart=WIFICommendAck+30;//ʹ����ָ��ָ�������׵�ַ
	for(i=0;i<4;i++)
	{
		strcpy(DateKeyStart,ControlKeyName[i]);
		DateKeyStart=DateKeyStart+ControlKeyLen[i];
		*DateKeyStart=0;
		switch(i)
		{
			case 0:value1=MOSAuto[0];break;//�������
			case 1:value1=MOSAuto[1];break;
			case 2:value1=MOSAuto[2];break;
			case 3:value1=MOSAuto[3];break;
		}
		DateValueLen=sprintf(DateMid1+2,"%d",value1);
		strcat(WIFICommendAck,DateMid1);
		DateKeyStart=DateKeyStart+DateValueLen+2;
		*DateKeyStart=0;
		if(i!=3)
		{
			strcat(WIFICommendAck,DateMid2);
			DateKeyStart=DateKeyStart+2;
		}
	}
	strcat(WIFICommendAck,DateBack);
	return WIFICommendAck;
}
/***********************************************************************
** �� �� ���� WifiPack()
** ����˵���� ����ƽ̨��������
**---------------------------------------------------------------------
** ��������� ��
** ���ز����� ��
***********************************************************************/
uint16 WifiPack()
{
	char *datp;
	JsonMakePak2();
	WifiComAck();
	datp=strrchr(Date,'}');
	*datp=0;
	WIFICommendAck[0]=',';
	strcat(Date,WIFICommendAck);
	UartSend2_str(Date);
	return Date;
}