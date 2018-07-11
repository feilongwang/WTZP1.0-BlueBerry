/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   EC.h
** 文件说明：   电导率测量
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "EC.h"

/*---------------------VARIABLES---------------------*/
int16 ECTemp;
int16 ECRealValue;
int16 ECImageValue;

float ECMagnitude;
float ECRads;
float ECRes;
float ECCon;

/*---------------------FUNCTIONS---------------------*/
/***********************************************************************
** 函 数 名： AD5933Init()
** 函数说明： 初始化AD5933
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void InitAD5933(void)
{
	AD5933WriteByte(0x82,0x0E); //起始频率 30kHz 1k/(16.776M/4)*2^27 =  30000*32	0x0EA600
	AD5933WriteByte(0x83,0xA6);
	AD5933WriteByte(0x84,0x00);

	AD5933WriteByte(0x85,0x00); //频率增量 100Hz 5/(16.776M/4)*2^27 =  5*32	0x000064
	AD5933WriteByte(0x86,0x00);
	AD5933WriteByte(0x87,0x64);

	AD5933WriteByte(0x88,0x00); //增量数 100 	0x0064
	AD5933WriteByte(0x89,0x64);

	AD5933WriteByte(0x8A,0x00); //建立时间周期数 100 	0x0064
	AD5933WriteByte(0x8B,0x64);

   	AD5933WriteByte(0x80,0xB1); //控制寄存器，1011 0001 0000 0000待机模式，2V，一倍放大，内部时钟 	0xB100
	AD5933WriteByte(0x81,0x00);

	AD5933WriteByte(0x80,0x11); //控制寄存器，0001 0001 0000 0000 以起始频率初始化，2V，一倍放大，内部时钟 	0x1100
	delay10ms();
	AD5933WriteByte(0x80,0x21); //控制寄存器，0010 0001 0000 0000 启动频率扫描，2V，一倍放大，内部时钟 	0x2100
}
/***********************************************************************
** 函 数 名： Read_AD5933_Temperature(void)
** 函数说明： 读取温AD5933测量的温度
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void Read_AD5933_Temperature(void)
{
	uint8 s;
    
	//启动温度测量
	AD5933WriteByte(0x80,0x93); //1001 0011

	do
    {
    	s=AD5933Read(0x8F);
  
	}while(!(s&0x01));
	
	//读出温度，保存在ECTemp中
	ECTemp=(int16)((AD5933Read(0x92)*256+AD5933Read(0x93))<<2);
	ECTemp=(ECTemp>>2)/32;
}
/***********************************************************************
** 函 数 名： EC(void)
** 函数说明： 完成电导率转换
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
float EC(void)
{
	uint8 s;

	while(1)
	{
		s=AD5933Read(0x8F);  //读取状态寄存器检查DFT是否完成
		if(s&0x02) break;
	}                  

	ECRealValue = (int16)(AD5933Read(0x94)*256+AD5933Read(0x95)); //实部
	ECImageValue = (int16)(AD5933Read(0x96)*256+AD5933Read(0x97)); //虚部
	ECMagnitude=sqrt(1.0*ECRealValue*ECRealValue+1.0*ECImageValue*ECImageValue);
	
	if((ECRealValue>0)&&(ECImageValue>0))
	{
		ECRads=180*atan2(ECImageValue,ECRealValue)/PI;
	}
	else if((ECRealValue<0)&&(ECImageValue>0))
	{
		ECRads=180*atan2(ECImageValue,ECRealValue)/PI + 180;
	}
	else if((ECRealValue<0)&&(ECImageValue<0))
	{
		ECRads=180*atan2(ECImageValue,ECRealValue)/PI + 180;
	}
	else if((ECRealValue>0)&&(ECImageValue<0))
	{
		ECRads=180*atan2(ECImageValue,ECRealValue)/PI + 360;
	}//计算相位

	ECRes=Cgain/ECMagnitude; //Ω
	ECCon=1000000L*Cce/(ECRes*cos(PI*(ECRads-SysPhase)/180)-SysRes); //μS/cm	 
    
	AD5933WriteByte(0x80,0xA1); //控制寄存器，1010 0001 0000 0000 省电模式，2V，一倍放大，内部时钟 	0xA100
	
	InitAD5933();
	return ECCon;
}