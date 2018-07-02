/*
 * App.h
 *
 * Created: 8/19/2017 11:36:57 AM
 *  Author: Jess Fisher
 */ 

#ifndef APP_H_
#define APP_H_

#define TARGET TI_MSP430
#define APPVERSION	001

#define ON		1
#define OFF		0
#define TRUE	1
#define FALSE	0
#define uBYTE	unsigned char
#define uWORD	unsigned int

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

extern uBYTE SystemPwr;
extern void AppInit(void);
extern unsigned char MainApp(void);

#endif /* APP_H_ */
