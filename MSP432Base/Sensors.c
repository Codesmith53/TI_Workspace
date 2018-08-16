//-----------------------------------------------------------------------------
// @file: Sensors.c
// @brief: Sensors interface
//
// @details: Prototype development.
//
// @copyright: CONFIDENTIAL Property of Jess Fisher
//
// @All rights reserved: Copying or other reproduction of this program except
// for archival purposes is prohibited without the prior written consent of
// JessFisher.
//
// Jess Fisher Copyright, Hoquiam, WA, USA
//
// @author:  Jess Fisher
// @date: 07/18/2018
// @version: 1.1
//
//-----------------------------------------------------------------------------
#include "App.h"
#include "I2C.h"
#include "Sensors.h"
#include "BMP180.h"

static int t,h,p,d;

//-----------------------------------------------------------------------------
int Temp(void)
{	
    t = readRawTemperature();
//    t = I2CReadByte(BMP180_I2CADDR); // receive DATA
	return (int)t;
}
//-----------------------------------------------------------------------------
int Humid(void)
{	
	return (int)h;
}
//-----------------------------------------------------------------------------
int Pressure(void)
{	
	return (int)p;
}
//-----------------------------------------------------------------------------
int Distance(void)
{		
	return (int)d;
}
//-----------------------------------------------------------------------------
void InitSensors(void)
{
	BMP180init();
}
//-----------------------------------------------------------------------------
void ProcessSensors(void)
{
	
}
//-----------------------------------------------------------------------------
void RelayOn(void)
{

}
//-----------------------------------------------------------------------------
void RelayOff(void)
{

}
