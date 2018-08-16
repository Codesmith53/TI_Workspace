//-----------------------------------------------------------------------------
// @file: BMP180.h
// @brief: BMP180 Barometric Pressure + Temp sensor interface
//
// @details: Prototype development.
// This is a library for the Adafruit BMP180 Barometric Pressure + Temp sensor
//
//  Designed specifically to work with the Adafruit BMP085 or BMP180 Breakout
//  ----> http://www.adafruit.com/products/391
//  ----> http://www.adafruit.com/products/1603
//
// Jess Fisher Copyright, Hoquiam, WA, USA
//
// @author:  Jess Fisher
// @date: 07/18/2018
// @version: 1.1
//
//-----------------------------------------------------------------------------
#ifndef  BMP180_H
#define  BMP180_H

#include "App.h"

#define BMP085_DEBUG 0

#define BMP180_I2CADDR 0x77

#define BMP085_ULTRALOWPOWER        0
#define BMP085_STANDARD             1
#define BMP085_HIGHRES              2
#define BMP085_ULTRAHIGHRES         3
#define BMP085_CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define BMP085_CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define BMP085_CAL_AC3           0xAE  // R   Calibration data (16 bits)    
#define BMP085_CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define BMP085_CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define BMP085_CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define BMP085_CAL_B1            0xB6  // R   Calibration data (16 bits)
#define BMP085_CAL_B2            0xB8  // R   Calibration data (16 bits)
#define BMP085_CAL_MB            0xBA  // R   Calibration data (16 bits)
#define BMP085_CAL_MC            0xBC  // R   Calibration data (16 bits)
#define BMP085_CAL_MD            0xBE  // R   Calibration data (16 bits)

#define BMP085_CONTROL           0x31 // 0xF4
#define BMP085_TEMPDATA          0x32 // 0xF6
#define BMP085_PRESSUREDATA      0x33 // 0xF6
#define BMP085_READTEMPCMD       0x34 // 0x2e
#define BMP085_READPRESSURECMD   0x35 // 0x34
#define BMP085_CHIPID            0x36 // 0xD0

void BMP180init(void);
float readTemperature(void);
long readPressure(void);
long readSealevelPressure(float);
float readAltitude(float); // std atmosphere
int readRawTemperature(void);
uLONG readRawPressure(void);

#endif //  BMP180_H
