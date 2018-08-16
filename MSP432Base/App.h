//-----------------------------------------------------------------------------
// @file: app.hpp
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

#ifndef APP_HPP_
#define APP_HPP_

#define TARGET TI_MSP430
#define APPVERSION	001

#define ON		1
#define OFF		0
#define TRUE	1
#define FALSE	0
#define uBYTE	unsigned char
#define uWORD	unsigned int
#define uLONG   unsigned long
#define boolean unsigned char

#define HIGH    1
#define LOW     0
#define H_ON    ON
#define H_OFF   OFF
#define FORWARD	1
#define REVERSE	0
#define FWD	    FORWARD
#define REV     REVERSE

// A2D input defines
#define VCC_LEVEL A3

// DIO pin assignments
#define HEARTBEAT  13
#define STEPPER1N4 11
#define STEPPER1N3 10
#define STEPPER1N2  9
#define STEPPER1N1  8
#define ECHO_PIN	6
#define TRIG_PIN	5  
#define DHT11PIN	4
#define RELAY1		3

extern boolean SystemPwr(void);
extern void AppInit(void);
extern boolean MainApp(void);

#endif /* APP_HPP_ */
