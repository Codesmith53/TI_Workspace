/*
 * I2C.h
 *
 * Created: 6/7/2018
 *  Author: Jess Fisher
 */ 

#ifndef I2C_H_
#define I2C_H_

#define I2C_BUFF_SIZE 10
#define I2C_SLAVE_ADX 0x0077
#define I2C_MSTR_ADX  0x00AA

extern void I2CInit(void);
extern uBYTE I2CReadQueue(void);
extern void I2CWriteQueue(uBYTE data);
extern void I2CReadRdy(uBYTE adx);
extern void I2CWriteByte(uBYTE adx, uBYTE data);
extern void I2CSetAdxBytes(uBYTE adx, uBYTE num);
extern uBYTE I2CReadByte(uBYTE adx);

#endif /* I2C_H_ */
