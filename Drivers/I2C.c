/*****************************************************************
**                   大连理工大学 创新创业学院
**                       物联网应用工坊
**---------------------------------------------------------------
** 项目名称：   WTZP1.0-BlueBerry
** 日    期：   2018-07-08
** 作    者：   温武军
**---------------------------------------------------------------
** 文 件 名：   I2C.c
** 文件说明：   调用单片机内I2C通信模块（目前只有端口3）
*****************************************************************/

/*---------------------INCLUDES----------------------*/
#include "I2C.h"

/*---------------------VARIABLES---------------------*/


/*---------------------FUNCTIONS---------------------*/
void InitI2C()
{
	P_SW2=P_SW2|0X30;
	I2CCFG = 0xe0;                              //使能I2C主机
   I2CMSST = 0x00;
}

void Wait()
{
	while(!(I2CMSST&0x40));
	I2CMSST&=~0x40;
}

void Start()
{
	I2CMSCR=0x01;
	Wait();
}

void SendData(unsigned char dat)
{
	I2CTXD=dat;
	I2CMSCR=0x02;
	Wait();
}

void RecvACK()
{
	I2CMSCR=0x03;
	Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                             //发送RECV命令
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                             //设置NCK信号
    I2CMSCR = 0x05;                             //发送ACK信号
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                             //发送STOP命令
    Wait();
}

void Delay()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

void I2C_AD5933()
{
    Start();                                    //发送起始命令
    SendData(0xa0);                             //发送设备码加写命令
    RecvACK();
    SendData(0x00);                             //发送存储器地址高字节
    RecvACK();
    SendData(0x00);                             //发送存储器地址低字节
    RecvACK();
    SendData(0x12);                             //写数据
    RecvACK();
    Stop();                                     //发送停止命令

    Delay();                                    //等待设备写数据

    Start();                                    //发送起始命令
    SendData(0xa0);                             //
    RecvACK();
    SendData(0x00);                             //?????????
    RecvACK();
    SendData(0x00);                             //?????????
    RecvACK();
    Start();                                    //??????
    SendData(0xa1);                             //??????+???
    RecvACK();
    P0 = RecvData();                            //????1
    SendACK();
    P2 = RecvData();                            //????2
    SendNAK();
    Stop();                                     //??????

    P_SW2 = 0x00;

    while (1);
}