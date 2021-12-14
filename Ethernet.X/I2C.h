/* 
 * File:   i2c.h
 * Author: CEDRIC
 *
 * Created on 25 April 2020, 7:05 PM
 */

#ifndef I2C_H
#define	I2C_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

void I2C_INTIALIZE(uint24_t clock);
void i2c_start(void);
void i2c_stop(void);
void i2c_RS(void);
char i2c_read(uint8_t ACK_NACK); 
void i2c_write(uint8_t data);
void i2c_scanBus(void);
void i2c_clrBuf(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

