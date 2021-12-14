/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef DS3231_H
#define	DS3231_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} time;


void DS3231_write(time myTime);
static void BCD_to_ASCII(uint8_t valueInBCD, uint8_t * ptr);
void DS3231_Display_UART(time myTime);
void DS3231_read(time * myTime);
#endif

