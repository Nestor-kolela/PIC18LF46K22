/*
 * File:   EEPROM.c
 * Author: Nestor
 *
 * Created on November 18, 2020, 7:04 AM
 */

#include "EEPROM.h"

#define _XTAL_FREQ  64000000

extern void EUSART1_putrs(const uint8_t * ptr);
extern void EUSART1_puts(uint8_t * ptr);

void EEPROM_write(const unsigned char data, const uint24_t address)
{
    i2c_start(); //send start
    //0x0000 to 0xFFFF
    //then from 0x10000 to 0x1FFFF
    i2c_write(0b10100000 | ((address >> 13 ) & 0b00001000));
    
    i2c_write((uint8_t)(address >> 8) & 0xFF);
    
    i2c_write((uint8_t)(address) & 0xFF);
    
    i2c_write(data);
    
    
    i2c_stop(); //send a stop bit
  
    //ACK polling described in the datasheet
    
    SSPCON2bits.ACKSTAT = 1; //set it high
    while(1)
    {
        i2c_start();
        i2c_write(0b10100000 | ((address >> 13 ) & 0b00001000));
        if(!SSPCON2bits.ACKSTAT)
        {
            break;
        }
    }
}//end EEPROM_Write
unsigned char EEPROM_Read(const uint24_t address)
{
    uint8_t tempValue = 0;
    
    i2c_start(); //send start
    //0x0000 to 0xFFFF
    //then from 0x10000 to 0x1FFFF

    i2c_write(0b10100000 | ((address >> 13 ) & 0b00001000));
    
    i2c_write((uint8_t)(address >> 8) & 0xFF);
    
    i2c_write((uint8_t)(address) & 0xFF);

    i2c_start();
    
    i2c_write(0b10100001 | ((address >> 13 ) & 0b00001000));
    
    tempValue = i2c_read(1); //
    
    i2c_stop(); //then send a stop
    
    return tempValue;
    
}//end EEPROM_Read
void EEPROM_putrs(unsigned char * buf, uint24_t startAddress)
{  
    while(*(buf) != '\0')
    {
        EEPROM_write(*(buf++), startAddress++); //keep writing 
        //until a null is encountered
    }
    return;
}//end EEPROM_putrs
unsigned char * EEPROM_gets(unsigned char * buf, const uint24_t startAddress, const uint24_t endAddress)
{
    uint24_t tempValue = 0;
    uint24_t count = 0;
      
    for(tempValue = startAddress; tempValue<=endAddress; tempValue++)
    {
        *(buf + count++)= EEPROM_Read(tempValue);
    }
    *(buf + count) = '\0';
    
    return &buf[0];
}//end EEPROM_gets

void EEPROM_WritePg(const uint16_t page, uint8_t * ptr)
{
    
    if(page < 1024)
    {
        uint32_t product;
        
        product =  page * 128;
        
        i2c_start(); //we need to write this
        
        i2c_write(0b10100000 | ((product >> 13 ) & 0b00001000));

        i2c_write((uint8_t)(product >> 8) & 0xFF);

        i2c_write((uint8_t)(product) & 0xFF);

        for(uint8_t cnt = 0; cnt < 128; cnt++)
        {
            i2c_write(*(ptr + cnt)); //send the data
        }

        i2c_stop();

        while (1) 
        {
            i2c_start();
            i2c_write(0b10100000 | ((product >> 13) & 0b00001000));
            if (!SSPCON2bits.ACKSTAT) 
            {
                break;
            }
        }
    }else
    {
        return ;
    }
    
}

uint8_t * EEPROM_ReadPg(uint16_t page, uint8_t * ptr) 
{
    if (page < 1024) 
    {
        
        uint32_t product = page * 128;
        
       // uint32_t tempVar = product + 128;
        
        i2c_start(); //send a start bit
        
        i2c_write(0b10100000 | ((product >> 13 ) & 0b00001000));
        
        i2c_write((uint8_t)(product >> 8) & 0xFF);
        
        i2c_write((uint8_t)(product) & 0xFF);
        
        i2c_start(); //send a start bit
        
        i2c_write(0b10100001 | ((product >> 13 ) & 0b00001000));
        
        uint8_t cnt;
        
        for(cnt = 0; cnt < 127; cnt++)
        {
            *(ptr + cnt) = i2c_read(0); 
        }
        
        *(ptr + cnt)= i2c_read(1); //read then send a nack
        
        return &ptr[0];
        
    }else
    {
        return (uint8_t *) NULL;
    }
    
}