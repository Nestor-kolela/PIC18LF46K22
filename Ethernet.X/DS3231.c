/*
 * File:   DS1307.c
 * Author: Nestor
 *
 * Created on January 19, 2021, 1:10 PM
 */
#include "DS3231.h"
#include "mcc_generated_files/eusart2.h"
#include <stdint.h>
#include "I2C.h"



const char *eish[7] = {",Sunday", ",Monday", ",Tuesday",
    ",Wednesday", ",Thursday", ",Friday",
    ",Saturday"};

void DS3231_write(time myTime) {
    i2c_start();

    i2c_write(0xD0);

    i2c_write(0x00);

    i2c_write(myTime.seconds);

    i2c_write(myTime.minutes);

    i2c_write(myTime.hours);

    i2c_write(myTime.day);

    i2c_write(myTime.date);

    i2c_write(myTime.month);

    i2c_write(myTime.year);

    i2c_stop();
}

void DS3231_read(time * myTime) {
    i2c_start();

    i2c_write(0xD0);

    i2c_write(0x00);

    i2c_RS();

    i2c_write(0xD1);

    myTime->seconds = i2c_read(0);

    myTime->minutes = i2c_read(0);

    myTime->hours = i2c_read(0);

    myTime->day = i2c_read(0);

    myTime->date = i2c_read(0);

    myTime->month = i2c_read(0);

    myTime->year = i2c_read(1);

    i2c_stop();
}

void DS3231_Display_UART(time myTime) {
    uint8_t timeStr[11] = "00:00:00";
    uint8_t dateStr[13] = "00/00/2000";

    BCD_to_ASCII((uint8_t) (myTime.hours), timeStr);
    *(timeStr + 2) = ':';

    BCD_to_ASCII((uint8_t) (myTime.minutes), &timeStr[3]);

    *(timeStr + 5) = ':';

    BCD_to_ASCII((uint8_t) (myTime.seconds), &timeStr[6]);
    
    *(timeStr + 10) = '\0';

    //for date

    BCD_to_ASCII((uint8_t) (myTime.date), dateStr);
    *(dateStr + 2) = '/';

    BCD_to_ASCII((uint8_t) (myTime.month), &dateStr[3]);

    *(dateStr + 5) = '/';

    BCD_to_ASCII((uint8_t) (myTime.year), &dateStr[8]);
    
    *(dateStr + 12) = '\0';

    EUSART2_puts(timeStr);
    EUSART2_putrs("\r\n"); 
    EUSART2_puts(dateStr);
    EUSART2_putrs(eish[myTime.day - 1]); 
}

static void BCD_to_ASCII(uint8_t valueInBCD, uint8_t * ptr) {
    *ptr++ = ((valueInBCD >> 4) | 0x30);
    *ptr = ((valueInBCD & 0x0F) | 0x30);
}