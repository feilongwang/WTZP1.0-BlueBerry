/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-14
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   Wifi.c
** 文件说明：   wifi功能模块(与wifi模块通信有问题)
*****************************************************************/
/*---------------------INCLUDES----------------------*/
#include "Wifi.h"

/*---------------------VARIABLES---------------------*/
char xdata Link[110]="{\"t\": 1,\"device\": \"BlueBerry\",\"key\":\"d9b8d549677e42d989f35401b6c0790f\",\"ver\":\"v1.0\"}";
char xdata Date[100]="{\"t\":3,\"datatype\":1,\"datas\":{\"Ph";
char xdata DateMid[10]="\":19";
char xdata DateBack[14]="},\"msgid\":1}";
char xdata BeatQus[7]="$#AT#\r";
char KeyName[7][9]={{"Ph"},{"LiquidT"},{"Humidity"},{"Lux"},{"Temp"},{"EC"},{"CO2"}};//传感器识别码
char xdata Ack[64],*JSONp=Ack;
	


/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： WifiRec()
** 函数说明： 接收来自WiFi模块的JSON
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： uint8
***********************************************************************/
uint8 WifiRec()
{
	int j=0;
	char k;
	k=UartRec2();
	{
		while(!k)
		{j++;if(j>300)return 0;}//等待无果返回0
		*JSONp=k;
	}while(JSONp++);
	return 1;//成功返回1
}
/***********************************************************************
** 函 数 名： JsonKeyRec()
** 函数说明： 获取JSON键值
**---------------------------------------------------------------------
** 输入参数： 目标键名，键值储存地址
** 返回参数： uint16,键值的地址
***********************************************************************/
uint16 WifiLinkAck(char *JsonKey)
{
	char *value;
	char *JsonKeyStart;//键名开始的地址
	char *JsonKeyEnd;//键名结束的地址
	char JsonKeyLength;//键名长度
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
** 函 数 名： WifiLink()
** 函数说明： 与云平台台建立链接
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void WifiLink()
{
	UartSend2_str(Link);
}
/***********************************************************************
** 函 数 名： WifiBeat()
** 函数说明： 与云平台台建立心跳连接
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void WifiBeat()
{
	UartSend2_str(BeatQus);
}
/***********************************************************************
** 函 数 名： JsonMakePak()
** 函数说明： 组包
**---------------------------------------------------------------------
** 输入参数： int8 rank,int16 value
** 返回参数： uint16,键值的地址
***********************************************************************/
uint16 JsonMakePak(int8 rank,int16 value)
{
	#define DateKeyStart 30
	uint8 DateValueLen;
	switch(rank)
	{
		case 0:strcpy(Date+DateKeyStart,KeyName[0]);break;//使数据指针指向数据首地址
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
** 函 数 名： Wifidat()
** 函数说明： 发送数据
**---------------------------------------------------------------------
** 输入参数： int8 rank,int16 DAT
** 返回参数： 无
***********************************************************************/
void Wifidat(int8 rank1,int16 DAT)
{
	JsonMakePak(rank1,DAT);
	UartSend2_str(Date);
}
