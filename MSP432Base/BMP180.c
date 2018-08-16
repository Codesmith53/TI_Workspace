//-----------------------------------------------------------------------------
// @file: BMP180.c
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

#include <stdint.h>
/* Include the iqmathlib header files */
// #include <ti/iqmathlib/QmathLib.h>
// #include <ti/iqmathlib/IQmathLib.h>

#include "App.h"
#include "I2C.h"
#include "Sensors.h"
#include "BMP180.h"

#define I2CHOLDOFF 3

static float sealevelPressure = 101325;
static float altitude_meters = 0;

uBYTE oversampling;
int ac1, ac2, ac3, b1, b2, mb, mc, md;
uWORD ac4, ac5, ac6;

//-----------------------------------------------------------------------------
void delay(uWORD t)
{
    int cnt;

    while(t)
    {
        for(cnt = 10; cnt > 0; cnt--);
        t--;
    }
}
//-----------------------------------------------------------------------------
void requestFrom(uBYTE b)
{
    I2CSetAdxBytes(BMP180_I2CADDR,b);
}
//-----------------------------------------------------------------------------
void write8(uBYTE a, uBYTE d)
{
    I2CWriteByte(BMP180_I2CADDR, a); // internal reg address in 180 to write to
    delay(I2CHOLDOFF);
    I2CWriteByte(BMP180_I2CADDR, d); // data to write to reg address
    delay(I2CHOLDOFF);
}
//-----------------------------------------------------------------------------
uBYTE read8(uBYTE a)
{
    uBYTE ret = 0;

    I2CWriteByte(BMP180_I2CADDR, a);   // internal reg address in 180 to write to
    delay(I2CHOLDOFF);
    ret = I2CReadByte(BMP180_I2CADDR); // receive DATA

    return ret;
}
//-----------------------------------------------------------------------------
uWORD read16(uBYTE a)
{
  uWORD ret = 0;

  ret = read8(a);   // receive upper byte
  ret <<= 8;
  ret |= read8(a);  // receive lower byte

  return ret;
}
//-----------------------------------------------------------------------------
long computeB5(long UT)
{
  long X1 = (UT - (long)ac6) * ((long)ac5) >> 15;
  long X2 = ((long)mc << 11) / (X1+(long)md);
  return X1 + X2;
}
//-----------------------------------------------------------------------------
boolean init(uBYTE mode)
{


  if (mode > BMP085_ULTRAHIGHRES) mode = BMP085_ULTRAHIGHRES;
  oversampling = mode;
/*
  stat = read8(BMP085_CHIPID);
  if (stat != 0x55) return FALSE;

  // read calibration data
  ac1 = read16(BMP085_CAL_AC1);
  ac2 = read16(BMP085_CAL_AC2);
  ac3 = read16(BMP085_CAL_AC3);
  ac4 = read16(BMP085_CAL_AC4);
  ac5 = read16(BMP085_CAL_AC5);
  ac6 = read16(BMP085_CAL_AC6);

  b1 = read16(BMP085_CAL_B1);
  b2 = read16(BMP085_CAL_B2);

  mb = read16(BMP085_CAL_MB);
  mc = read16(BMP085_CAL_MC);
  md = read16(BMP085_CAL_MD);
*/
  return TRUE;
}

//-----------------------------------------------------------------------------
void BMP180init(void)
{
	boolean startup;
	startup = init(BMP085_STANDARD);
}
//-----------------------------------------------------------------------------
int readRawTemperature(void)
{
  write8(BMP085_CONTROL, BMP085_READTEMPCMD);
  delay(I2CHOLDOFF);
  return read16(BMP085_TEMPDATA);
}
//-----------------------------------------------------------------------------
uLONG readRawPressure(void)
{
  uLONG raw;

  write8(BMP085_CONTROL, BMP085_READPRESSURECMD + (oversampling << 6));

  if (oversampling == BMP085_ULTRALOWPOWER) 
    delay(I2CHOLDOFF);
  else if (oversampling == BMP085_STANDARD) 
    delay(I2CHOLDOFF);
  else if (oversampling == BMP085_HIGHRES) 
    delay(I2CHOLDOFF);
  else 
    delay(I2CHOLDOFF);

  raw = read16(BMP085_PRESSUREDATA);

  raw <<= 8;
  raw |= read8(BMP085_PRESSUREDATA+2);
  raw >>= (8 - oversampling);

  return raw;
}
//-----------------------------------------------------------------------------
long readPressure(void)
{
  long UT, UP, B3, B5, B6, X1, X2, X3, p;
  uLONG B4, B7;

  UT = readRawTemperature();
  UP = readRawPressure();

  B5 = computeB5(UT);

  // do pressure calcs
  B6 = B5 - 4000;
  X1 = ((long)b2 * ( (B6 * B6)>>12 )) >> 11;
  X2 = ((long)ac2 * B6) >> 11;
  X3 = X1 + X2;
  B3 = ((((long)ac1*4 + X3) << oversampling) + 2) / 4;

  X1 = ((long)ac3 * B6) >> 13;
  X2 = ((long)b1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((uLONG)ac4 * (uLONG)(X3 + 32768)) >> 15;
  B7 = ((uLONG)UP - B3) * (uLONG)( 50000UL >> oversampling );

  if (B7 < 0x80000000) p = (B7 * 2) / B4;
  else p = (B7 / B4) * 2;

  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;

  p = p + ((X1 + X2 + (long)3791)>>4);

  return p;
}
//-----------------------------------------------------------------------------
long readSealevelPressure(float altitude_meters)
{
  float pressure = readPressure();
//  return (long)(pressure / pow(1.0-altitude_meters/44330, 5.255));
  return (long)pressure;
}
//-----------------------------------------------------------------------------
float readTemperature(void)
{
  long UT, B5;     // following ds convention
  float temp;

  UT = readRawTemperature();

  B5 = computeB5(UT);
  temp = (B5+8) >> 4;
  temp /= 10;
  
  return temp;
}
//-----------------------------------------------------------------------------
float readAltitude(float sealevelPressure)
{
  float altitude = 1.0;
  float pressure = readPressure();

  // altitude = 44330 * (1.0 - pow(pressure /sealevelPressure,0.1903));

  return altitude;
}
