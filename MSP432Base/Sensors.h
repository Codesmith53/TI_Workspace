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

#ifndef SENSORS_H_
#define SENSORS_H_

extern void InitSensors(void);
extern int	Temp(void);
extern int	Humid(void);
extern int	Pressure(void);
extern int	Distance(void);
extern void RelayOn(void);
extern void RelayOff(void);
extern void ProcessSensors(void);

#endif /* SENSORS_H_ */
