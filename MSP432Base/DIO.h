//-----------------------------------------------------------------------------
// @file: DIO.h
// @brief: Interface file for digital IO
//
// @details: TI Code Composer Studio version
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
// @date: 06/19/2018
// @version: 1.0
//
//-----------------------------------------------------------------------------
#ifndef DIO_H_
#define DIO_H_

#include "App.h"

extern void pinMode(uBYTE pin, uBYTE mode);
extern void digitalWrite(uBYTE pin, uBYTE val);
extern uBYTE digitalRead(uBYTE pin);

#endif /* DIO_H_ */
