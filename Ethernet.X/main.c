/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18LF46K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/TCPIPLibrary/tcpv4.h"
#include <string.h>
#include "I2C.h"
#include "EEPROM.h"
#include "DS3231.h"
volatile bool flag; 
bool sentFlag = false; 
tcpTCB_t port7TCB;
/*
                         Main application
 */

//char * KOLELA = "<!DOCTYPE html PUBLIC \"<html><head><meta content=\"text/html; charset=ISO-8859-1\"http-equiv=\"content-type\"><title>Hello World</title></head><body><br>PIC18LF46L22</body></html>"; 
//const char * KOLELA = "<!DOCTYPE html PUBLIC \"<html><head><title>HTML in 10 Simple Steps or Less</title><meta http-equiv=\"refresh\" content=\"5\"><!-- See the difference? --></head><body>Nestor Kolela Kalambay</body></html>";
//const char * KOLELA = "<html><head><title>Remote Control With Push Button</title></head><body><form name=\"input\" method=\"get\"><table align=\"center\" width=\"500\" bgcolor =\"LightGray\" border=\"2\"><tr><td align=\"center\" colspan=\"2\"><font size=\"5\" color=\"RoyalBlue\" face=\"verdana\"><b>Web-Based Control and Monitoring</br></font></td></tr><tr><td height=\"200\" align=\"center\" bgcolor=\"LightGray\"><input name=\"TA\" type=\"submit\" value=\"TOGGLE RELAY A\"/></td></tr></table></form></body></html>";
const char * KOLELA = "<html><head><meta http-equiv=\"refresh\" content=\"5\"><title>easyWEB - dynamic Webside</title></head><body bgcolor=\"#3030A0\" text=\"#FFFF00\"><p><b><font color=\"#FFFFFF\" size=\"6\"><i>Hello World!</i></font></b></p><p><b>This is a dynamic webside hosted by the embedded Webserver</b><b>easyWEB.</b></p><p><b>Hardware:</b></p><ul><li><b>MSP430F149, 8 MHz, 60KB Flash, 2KB SRAM</b></li><li><b>CS8900A Crystal Ethernet Controller</b></li></ul><p><b>A/D Converter Value Port P6.7:</b></p><table bgcolor=\"#ff0000\" border=\"5\" cellpadding=\"0\" cellspacing=\"0\" width=\"500\"><tr><td><table width=\"AD7%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td bgcolor=\"#00ff00\">&nbsp;</td></tr></table></td></tr></table><table border=\"0\" width=\"500\"><tr><td width=\"20%\">0V</td><td width=\"20%\">0,5V</td><td width=\"20%\">1V</td><td width=\"20%\">1,5V</td><td width=\"20%\">2V</td></tr></table><p><b>MCU Temperature:</b></p><table bgcolor=\"#ff0000\" border=\"5\" cellpadding=\"0\" cellspacing=\"0\" width=\"500\"><tr><td><table width=\"ADA%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td bgcolor=\"#00ff00\">&nbsp;</td></tr></table></td></tr></table><table border=\"0\" width=\"500\"><tr><td width=\"20%\">20°C</td><td width=\"20%\">25°C</td><td width=\"20%\">30°C</td><td width=\"20%\">35°C</td><td width=\"20%\">40°C</td></tr></table></body></html>"; 
//const char * KOLELA = "<html><head><meta http-equiv=\"refresh\" content=\"5\"><title>easyWEB - dynamic Webside</title></head><body><p><b><font color=\"?#FFFFFF?\" size=\"6\"><i>HelloWorld!</i></font></b></p><p><b>This is a dynamic webside hosted by the embeddedWebserver</b><b>easyWEB.</b></p><p><b>Hardware:</b></p><ul><li><b>PIC18LF46K22, 64 MHz, 64KB Flash, 3KB SRAM</b></li><li><b>ENC28J60 Crystal Ethernet Controller</b></li></ul><p><b>A/D Converter Value Port AN1:</b></p><table bgcolor=\"?#ff0000?\" border=\"5\" cellpadding=\"0\"cellspacing=\"0\" width=\"500\"><tbody><tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"width=""><tbody><tr><td bgcolor=\"?#00ff00?\">&nbsp;</td></tr></tbody></table></td></tr></tbody></table><table border=\"0\" width=\"500\"><tbody><tr><td width=\"20%\">0V</td><td width=\"20%\">0,5V</td><td width=\"20%\">1V</td><td width=\"20%\">1,5V</td><td width=\"20%\">2V</td></tr></tbody></table><p><b>MCU Temperature:</b></p><table bgcolor=\"?#ff0000?\" border=\"5\" cellpadding=\"0\"cellspacing=\"0\" width=\"500\"><tbody><tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"width=""><tbody><tr><td bgcolor=\"?#00ff00?\">&nbsp;</td></tr></tbody></table></td></tr></tbody></table><table border=\"0\" width=\"500\"><tbody><tr><td width=\"20%\">20°C</td><td width=\"20%\">25°C</td><td width=\"20%\">30°C</td><td width=\"20%\">35°C</td><td width=\"20%\">40°C</td></tr></tbody></table></body></html>";
void TCP_Handle(void); 
void main(void)
{
    // Initialize the device
    time now; 
    
    now.date = 0x06;
    
    now.day = 0x02;
    
    now.hours = 0x19; 
    now.minutes = 0x29; 
    
    now.month = 0x12; 
    
    now.seconds = 0; 
    
    now.year = 0x21; 
    
    
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    I2C_INTIALIZE(400000);
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    //DS3231_write(now); 
    
    while (1)
    {
        // Add your application code
        Network_Manage(); 
        TCP_Handle(); 
        if(flag == true)
        {
            LED1_Toggle(); 
            flag = false; 
            DS3231_read(&now);
            
            DS3231_Display_UART(now); 
            EUSART2_putrs("\r\n"); 
            if(sentFlag == true)
            {
                if(TCP_Close(&port7TCB) == SUCCESS)
                {
                    
                    sentFlag = false; 
                }
            }
            TCP_Update();
        }
    }
}

void TCP_Handle(void) {
    // create the socket for the TCP Server
    
    // create the TX and RX buffers
    static uint8_t rxdataPort7[512];
    static uint8_t txdataPort7[512];
    uint16_t rxLen, txLen, i;
    
    //socketState_t;
    socketState_t socket_state;
    rxLen = 0;
    // checking the status of the socket
    socket_state = TCP_SocketPoll(&port7TCB);
    switch (socket_state) {
        case NOT_A_SOCKET:
            //Inserting and initializing the socket
            if(flag == true)
                EUSART2_putrs("Not a socket.\r\n"); 
            TCP_SocketInit(&port7TCB);
        case SOCKET_CLOSED:
            //configure the local port
            if(flag == true)
                EUSART2_putrs("Socket closed.\r\n");
            TCP_Bind(&port7TCB, 80); //make it listen on port 80 
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof (rxdataPort7));
            // start the server
            TCP_Listen(&port7TCB);
            break;
            
        case SOCKET_IN_PROGRESS:
        {
            if(flag == true)
            {
                EUSART2_putrs("In Progress.\r\n");
            }
        }break; 
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can reuse the //buffer
            
            if(flag == true)
                EUSART2_putrs("Connected.\r\n");
            
            if (TCP_SendDone(&port7TCB)) {
                // check to see if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if (rxLen > 0) {
                    //make sure it safe to use the receive buffer
                    rxLen = TCP_GetReceivedData(&port7TCB);
                    //simulate some buffer processing copy from //the RX buffer to the TX buffer
                    for (i = 0; i < rxLen; i++) 
                    {
                        EUSART2_Write(txdataPort7[i] = rxdataPort7[i]);
                    }
                    
                    char tempBuf[50]; 
                    sprintf(tempBuf, "\r\nThe size is %u\r\n", rxLen); 
                    EUSART2_puts(tempBuf); 
                    // reuse the rx buffer
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof (rxdataPort7));
                    txLen = rxLen;
                    //send data back to the source
                    //TCP_Send(&port7TCB, txdataPort7, txLen);
                    if(TCP_Send(&port7TCB, KOLELA, strlen(KOLELA)) == SUCCESS)
                    {
                        //TCP_SocketRemove(&port7TCB);
                        
                        sentFlag = true; 
                        
                        if(TCP_SocketRemove(&port7TCB) == SUCCESS)
                        {
                            EUSART2_puts("It was closed succesffully \r\n");
                        }
                        EUSART2_puts("It was sent successfully\r\n"); 
                    }
                }
            }
            break;
        case SOCKET_CLOSING:
            
            if(flag == true)
                EUSART2_putrs("Closing socket.\r\n");
            TCP_SocketRemove(&port7TCB);
            break;
        default:
            // we should not end up here
            break;
    }
}

/**
 End of File
*/