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


//const char * KOLELA = "<html><head><meta http-equiv=\"refresh\" content=\"5\"><title>Embedded WebServer ENC28J60</title></head><body style=\"color: rgb(0, 0, 0); background-color: rgb(51, 51, 255);\"alink=\"#000099\" link=\"#000099\" vlink=\"#990099\"><big style=\"font-weight: bold; color: white;\"><big><big>Hello World!</big></big></big><br><br><br><big style=\"color: rgb(255, 255, 102); font-weight: bold;\">This is a dynamic website hosted by the embedded Web Server<br><br>Hardware: PIC18LF46K22, 64MHz, 64 KB Flash, 3KB SRAM<br><br>ENC28J60 Crystal Ethernet Controller</big><br><br><br><br><br><big style=\"font-weight: bold; font-style: italic;\"><span style=\"color: rgb(255, 255, 102);\">Time: </span><span style=\"color: yellow;\">00:00:00</span><br style=\"color: rgb(255, 255, 102);\"><span style=\"color: rgb(255, 255, 102);\">Date: 14:12:2021</span><br style=\"color: rgb(255, 255, 102);\"><span style=\"color: rgb(255, 255, 102);\">Temperature: </span></big><span style=\"font-weight: bold; color: rgb(255, 255, 102);\">00 Celsius</span><br><span style=\"color: rgb(255, 255, 102); font-weight: bold;\"><br><br>GPIOs Control <br><br><input name=\"LED1\" value=\"Toggle LED1\" type=\"submit\"><br><br><input name=\"LED2\" value=\"Toggle LED2\" type=\"submit\"><br><br>Designer: Nestor&nbsp;Kalambay</span><br></body></html>"; 
char KOLELA[] = "<html><head><meta http-equiv=\"refresh\" content=\"10\"><title>Embedded WebServer ENC28J60</title></head><body style=\"color: rgb(0, 0, 0); background-color: rgb(51, 51, 255);\"alink=\"#000099\" link=\"#000099\" vlink=\"#990099\"><big style=\"font-weight: bold; color: white;\"><big><big>Hello World!</big></big></big><br><br><br><big style=\"color: rgb(255, 255, 102); font-weight: bold;\">This is a dynamic website hosted by the embedded Web Server<br><br>Hardware: PIC18LF46K22, 64MHz, 64 KB Flash, 3KB SRAM<br><br>ENC28J60 Crystal Ethernet Controller</big><br><br><br><br><br><big style=\"font-weight: bold; font-style: italic;\"><span style=\"color: rgb(255, 255, 102);\">Time: </span><span style=\"color: yellow;\">00:00:00</span><br style=\"color: rgb(255, 255, 102);\"><span style=\"color: rgb(255, 255, 102);\">Date: 14:12:2021</span><br style=\"color: rgb(255, 255, 102);\"><span style=\"color: rgb(255, 255, 102);\">Temperature: </span></big><span style=\"font-weight: bold; color: rgb(255, 255, 102);\">+25.00 Celsius</span><br><span style=\"color: rgb(255, 255, 102); font-weight: bold;\"><br><br>GPIOs Status <br><br>LED1 is OFF<br>LED2 is OFF<br>LED3 is OFF<br><br><br><br>Designer: Nestor&nbsp;Kalambay</span><br></body></html>";
void TCP_Handle(void); 
time now;

char temporaryTime[] = "00:00:00";
char temporaryDate[] = "14:12:2021"; 
char temperatureBuf[] = "+25.00"; 
char ledOneStatus[12] = "LED1 is OFF";
char ledTwoStatus[12] = "LED2 is OFF";
char ledThreeStatus[12] = "LED3 is OFF";


void main(void)
{
    // Initialize the device
     
    
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
    
    //LED2_SetHigh(); 
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
    static uint8_t rxdataPort7[500];
    static uint8_t txdataPort7[500];
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
            
            if (TCP_SendDone(&port7TCB)) 
            {
                // check to see if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if (rxLen > 0) 
                {
                    //make sure it safe to use the receive buffer
                    rxLen = TCP_GetReceivedData(&port7TCB);
                    //simulate some buffer processing copy from //the RX buffer to the TX buffer
                    for (i = 0; i < rxLen; i++) 
                    {
                        EUSART2_Write(txdataPort7[i] = rxdataPort7[i]);
                    }
                    // reuse the rx buffer
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof (rxdataPort7));

                    char * ptr = strstr(KOLELA, temporaryTime);
                    char * ptrDate = strstr(KOLELA, temporaryDate); 
                    char * ptrTemp = strstr(KOLELA, temperatureBuf); //read the temperature 

                    char * ptrLED1 = strstr(KOLELA, ledOneStatus);
                    char * ptrLED2 = strstr(KOLELA, ledTwoStatus); 
                    char * ptrLED3 = strstr(KOLELA, ledThreeStatus); 
                    
                    if(ptr != NULL && ptrDate != NULL && ptrTemp != NULL && ptrLED1 != NULL && ptrLED2 != NULL && ptrLED3 != NULL) 
                    {

                        char tempBuf[10]; 
                        char dateBuf[12]; 
                        
                        DS3231_GetTime(now, tempBuf); 
                        DS3231_GetDate(now, dateBuf); 
                        char buf[20];
                        uint16_t temperature = DS3231_GetTemperature();

                        float tempInFloat = 0.25 * ((temperature & 0x00C0) >> 6);

                        tempInFloat += (float) ((temperature & 0x7F00) >> 8);

                        sprintf(buf, (temperature & 0x8000) ? "-%.2f": "+%.2f", tempInFloat);
            
                        uint8_t i; 
                        for(i = 0; i < strlen(tempBuf); i++)
                        {
                            *ptr++ = temporaryTime[i] = tempBuf[i]; 
                        }
                        temporaryTime[i] = '\0'; 
                        
                         
                        for(i = 0; i < strlen(dateBuf); i++)
                        {
                            *ptrDate++ = temporaryDate[i] = dateBuf[i]; 
                        }
                        temporaryDate[i] = '\0'; 
                        //EUSART2_putrs(temporaryDate); 
                        
                        for(i = 0; i < strlen(temperatureBuf); i++)
                        {
                            *ptrTemp++ = temperatureBuf[i] = buf[i]; 
                        }
                        temperatureBuf[i] = '\0'; 
                        
                        //read the stuff for LED 1
                        //buf
                        strcpy(buf, LED1_GetValue() ? "LED1 is ON ": "LED1 is OFF");
                        
                        for(i = 0; i < strlen(ledOneStatus); i++)
                        {
                            *ptrLED1++ = ledOneStatus[i] = buf[i]; 
                        }
                        ledOneStatus[i] = '\0';
                        
                        //read the stuff for LEd 2
                        
                        strcpy(buf, LED2_GetValue() ? "LED2 is ON ": "LED2 is OFF");
                        
                        for(i = 0; i < strlen(ledTwoStatus); i++)
                        {
                            *ptrLED2++ = ledTwoStatus[i] = buf[i]; 
                        }
                        ledTwoStatus[i] = '\0';
                        
                        //read the stuff for LED3
                        
                        strcpy(buf, LED3_GetValue() ? "LED3 is ON ": "LED3 is OFF");
                        
                        for(i = 0; i < strlen(ledThreeStatus); i++)
                        {
                            *ptrLED3++ = ledThreeStatus[i] = buf[i]; 
                        }
                        ledThreeStatus[i] = '\0';
                        
                        if (TCP_Send(&port7TCB, KOLELA, strlen(KOLELA)) == SUCCESS) {
                            //TCP_SocketRemove(&port7TCB);

                            sentFlag = true;

                            if (TCP_SocketRemove(&port7TCB) == SUCCESS) 
                            {
                                EUSART2_puts("It was closed succesffully \r\n");
                            }
                            EUSART2_puts("It was sent successfully\r\n");
                        }

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