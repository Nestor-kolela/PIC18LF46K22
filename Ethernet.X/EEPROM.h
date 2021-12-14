/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
extern void i2c_start(void);
extern void i2c_stop(void);
extern void i2c_RS(void);
extern char i2c_read(uint8_t ACK_NACK); 
extern void i2c_write(uint8_t data);

void EEPROM_write(const unsigned char data, const uint24_t address); 
void EEPROM_WritePg(const uint16_t page, uint8_t * ptr);
uint8_t * EEPROM_ReadPg(uint16_t page, uint8_t * ptr);
unsigned char EEPROM_Read(const uint24_t address);
unsigned char * EEPROM_gets(unsigned char * buf, const uint24_t startAddress, const uint24_t endAddress);
void EEPROM_putrs(unsigned char * buf, uint24_t startAddress);
#endif	

