/*
 * File:   i2c.c
 * Author: Nestor
 *
 * Created on 25 April 2020, 6:57 PM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"
#define _XTAL_FREQ  64000000

void I2C_INTIALIZE(uint24_t clock) {    
    TRISCbits.TRISC3 = 1; 
    TRISCbits.TRISC4 = 1; 
    
    ANSELCbits.ANSC3 = 0; 
    ANSELCbits.ANSC4 = 0; 
    
    SSP1STATbits.SMP = 1;
    SSP1STATbits.CKE = 0;
    
    SSP1CON1 |= 0x28; //no collision, no overflow, enable I2C, Master mode
    SSP1CON2 |= 0x00;
    SSP1ADD = (uint8_t)(_XTAL_FREQ / (clock * 4)) - 1; //we multiply by 1000 to define frequency kilo Hertz
}

void i2c_start(void) {
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN); //wait for start to complete
    PIR1bits.SSP1IF = 0; 
}

void i2c_stop(void) {
    SSP1CON2bits.PEN = 1;
    while (SSP1CON2bits.PEN);
    PIR1bits.SSP1IF = 0; //clear Interrupt flag
}

void i2c_RS(void) {
    SSP1CON2bits.RSEN = 1;
    while (SSP1CON2bits.RSEN);
    PIR1bits.SSP1IF = 0;
}

char i2c_read(uint8_t ACK_NACK) 
{
    SSP1STATbits.BF = 0;
    SSP1CON2bits.RCEN = 1;
    while (!SSP1STATbits.BF); //wait for buffer to be full 
    SSP1CON2bits.ACKDT = ACK_NACK;
    SSP1CON2bits.ACKEN = 1;
    while (SSP1CON2bits.ACKEN);
    return SSP1BUF;
}

void i2c_write(uint8_t data) 
{
    SSP1BUF = data;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    //if (SSPCON2bits.ACKSTAT) { //if slave has not responded after the ninth bit stop transmission
    //    i2c_stop();
    //}
}

void i2c_clrBuf(void) 
{
    i2c_start();
    i2c_write(0x00);
    i2c_stop();
}