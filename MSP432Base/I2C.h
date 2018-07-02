/*
 * I2C.h
 *
 * Created: 6/7/2018
 *  Author: Jess Fisher
 */ 

#ifndef I2C_H_
#define I2C_H_

#define I2C_BUFF_SIZE 5
#define I2C_SLAVE_ADX 0x0044
#define I2C_MSTR_ADX  0x00AA

extern void I2CInit(void);
extern uBYTE I2CReadQueue(void);
extern void I2CWriteQueue(uBYTE data);
extern uBYTE I2CReadRdy(void);
extern void I2CWriteByte(uBYTE adx, uBYTE data);

#endif /* I2C_H_ */
