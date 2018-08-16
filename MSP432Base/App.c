//-----------------------------------------------------------------------------
// @file: app.cpp
// @brief: main app support for system
//
// @details: TI CCP complier support
//
// @copyright: CONFIDENTIAL Property of Jess Fisher Copyright 2018
//
// @All rights reserved: Copying or other reproduction of this program except
// for archival purposes is prohibited without the prior written consent of
// Jess Fisher.
//
// Jess Fisher Copyright, Hoquiam, WA, USA
//
// @author:  Jess Fisher
// @date: 07/14/2018
// @version: 1.0
//
//-----------------------------------------------------------------------------
#include <msp.h>
#include "App.h"
#include "I2C.h"
#include "Sensors.h"

static boolean pwr = OFF;
//-----------------------------------------------------------------------------
boolean SystemPwr(void)
{
    return pwr;
}

//-----------------------------------------------------------------------------
void AppInit(void)
{
	pwr = ON;
//	InitSensors();
}

//-----------------------------------------------------------------------------
boolean MainApp(void)
{
    Temp();
    return TRUE;
}
