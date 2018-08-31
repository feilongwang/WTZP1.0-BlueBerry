/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-07
** 作    者：   王老师
**---------------------------------------------------------------
** 文 件 名：   System.c
** 文件说明：   系统功能
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include ".\Drivers\Drivers.h"
#include ".\Modules\Modules.h"
#include ".\System\System.h"
#include ".\Board\Board.h"

/*---------------------VARIABLES---------------------*/
//生长参数变量储存区
uint16 DateLiquidT;uint16 DateCO2;int16 DatePh;
uint16 DateHumidity;uint16 DateTemp;
int16 DateEc;
uint32 DateLux;
//其他控制参数区
extern char MesureMode;//1-on 0-off
extern char AutoControlMode;//1-on 0-off

/*---------------------FUNCTIONS---------------------*/

/***********************************************************************
** 函 数 名： InitSystem()
** 函数说明： 初始化系统
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitSystem(void)
{
	//泵初始化
	MOS1=0;MOS2=0;MOS3=0;MOS4=0;
	//传感器初始化区域
	InitI2C();
	InitLUX();
  Init_AD();
	InitPh();
	//串口初始化区域
	InitUart1();
	InitUart2();
  InitUart3();
	//中断或定时器初始化区域
	InterruptKeyIsr();
	//定时器初始化
	InitTime0();
	//植物生长参数控制初始化
  //EEPROMWrite(0x0100,0x08);//PH=8
	//EEPROMWrite(0x0101,0x08);//低位，EC=1800
	//EEPROMWrite(0x0102,0x07);//高位
}
/***********************************************************************
** 函 数 名： Sensor()
** 函数说明： 传感器数据获取
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Sensor()
{
	AM2301();
	DS18B20Start();
	Read_AD5933_Temperature(); 
	DateEc=(int)EC();
	DateLiquidT=DS18B20();
	DateLux=Get_Lux();
	DateCO2=Get_CO2();
	DatePh=ph();
}
/***********************************************************************
** 函 数 名： LCDdisplay()
** 函数说明： 将数据上传至串口屏
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void LCDdisplay()
{
	LCDSend(0x2A,DateLiquidT/10.0);//溶液温度
	LCDSend(0x0A,DateCO2);//CO2浓度
	LCDSend(0x0B,DatePh/1000.0);//PH
	LCDSend(0x08,DateHumidity/10.0);//空气湿度
	LCDSend(0x07,DateTemp/10.0);//空气温度
	LCDSend(0x0C,DateEc);//溶液电导率
	LCDSend(0x09,DateLux);//光照
	//显示状态
	LCDKeyControl(0x11,MOSAuto[0]);//MOS1
	LCDKeyControl(0x13,MOSAuto[1]);//MOS2
	LCDKeyControl(0x14,MOSAuto[2]);//MOS3
	LCDKeyControl(0x15,MOSAuto[3]);//MOS4
	LCDKeyControl(0x25,MesureMode);
	LCDKeyControl(0x23,AutoControlMode);
}
/***********************************************************************
** 函 数 名： WIFIControl()
** 函数说明： 与云平台连接函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void WIFIControl()
{
	static uint8 SysCheck=1;//系统检测次数
	if(SysCheck%200==0||SysCheck<9)WifiLink();//云平台连接//
	WifiBeat();//与云平台保持连接
	//if(SysCheck%3==0)WifiPack();//向云平台发送数据
	if(SysCheck%3==0)WifidatPack();
	if(SysCheck%4==0)WifiPack();
	SysCheck++;
	if(SysCheck>250)SysCheck=1;
}
/***********************************************************************
** 函 数 名： StartSystem()
** 函数说明： 运行系统
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void StartSystem(void)
{
	//存储变量区
	char cnt=0;
	TEST=0;//LED亮
	MesureMode=1;
	//
	while(1)
	{
		WIFIControl();
		Sensor();
		LCDdisplay();
		AsmControl();
		WIFIReccount=0;
		LCDReccount=0;
		TEST = ~TEST;
	}
	cnt++;
	if(cnt>254)cnt=0;
}
