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

char * ptr = "<!DOCTYPE html PUBLIC \"<html><head><meta content=\"text/html; charset=ISO-8859-1\"http-equiv=\"content-type\"><title>Hello World, Embedded Systems</title></head><body>PIC18LF46K22<br></body></html>";

volatile uint8_t cnt = 0; 
//static tcpTCB_t port7TCB; 

void TCP_Handler(void);
void TCP_Blinky(void);

uint8_t buf[255]; 
uint8_t head; 
uint8_t tail; 
void queueInsert(uint8_t ucData);
uint8_t queueRead(void);
uint8_t queuePeek(void);


/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    LED_SetHigh(); 
    while (1)
    {
        // Add your application code
        Network_Manage(); //Manage the network
        //TCP_Handler(); 
        TCP_Blinky();
        if(cnt)
        {
            cnt = 0; 
            TCP_Update(); 
        }
    }
}

void TCP_Handler(void)
{
    // create the socket for the TCP Server
    static tcpTCB_t port7TCB;

    // create the TX and RX Server's buffers
    static uint8_t rxdataPort7[20];
    static uint8_t txdataPort7[20];

    uint16_t rxLen, txLen;
    socketState_t socket_state;

    socket_state = TCP_SocketPoll(&port7TCB); //get the state of port7TCB socket

    switch(socket_state) {
        case NOT_A_SOCKET:
            // Inserting and initializing the socket
            TCP_SocketInit(&port7TCB);
            if (cnt)
                EUSART2_putrs("Not a socket\r\n");
            break;
        case SOCKET_CLOSED:
            //configure the local port
            //28866
            if (cnt)
                EUSART2_putrs("Socket closed\r\n");
            TCP_Bind(&port7TCB, 80);
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
            // start the server
            TCP_Listen(&port7TCB);
            break;
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can send another buffer
            if(cnt)
                EUSART2_putrs("Socket connected\r\n");
            
            if(TCP_SendDone(&port7TCB))
            {
                // check to see  if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if(rxLen > 0)
                {
                    rxLen = TCP_GetReceivedData(&port7TCB);

                    //process received data.
                    //setup data to send back to client
                    // reuse the RX buffer

                    uint16_t temp = rxLen;
                    
                    for (uint16_t cnt = 0; cnt < temp; cnt++) {
                        EUSART2_Write(rxdataPort7[cnt]);
                    }
                                        
                                        
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
                    //send a message back to client
                    //TCP_Send(&port7TCB, txdataPort7, strlen(txdataPort7));
                    if(rxdataPort7[0] == 'G')
                    {
                        TCP_Send(&port7TCB, ptr, strlen(ptr)); 
                        //TCP_SocketRemove(&port7TCB); 
                        
                    }
                }
            }
            
            //EUSART2_putrs("Connected\r\n");
            break;

        case SOCKET_IN_PROGRESS:
            if (cnt)
                EUSART2_putrs("In Progress\r\n");
            break; 
            
        case SOCKET_CLOSING:
            if(cnt)
                EUSART2_putrs("Closing\r\n");
            TCP_SocketRemove(&port7TCB); 
            break; 
                    
        default:   
            break;
    }
}

void TCP_Blinky(void)
{
    // create the socket for the TCP Server
    static tcpTCB_t port7TCB;

    // create the TX and RX Server's buffers
    static uint8_t rxdataPort7[20];
    static uint8_t txdataPort7[20];
    static uint8_t hit_counter;
    uint8_t len;

    uint16_t rxLen, txLen;
    socketState_t socket_state;

    socket_state = TCP_SocketPoll(&port7TCB);

    switch(socket_state)
{
        case NOT_A_SOCKET:
            // Inserting and initializing the socket
            if (cnt)
                EUSART2_putrs("Not a socket\r\n");
            TCP_SocketInit(&port7TCB);
            hit_counter = 0;
            break;
        case SOCKET_CLOSED:
            //configure the local port
            if (cnt)
                EUSART2_putrs("Socket closed\r\n");
            TCP_Bind(&port7TCB, 80);
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
            // start the server
            TCP_Listen(&port7TCB);
            break;
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can send another buffer
            if(cnt)
                EUSART2_putrs("Socket connected\r\n");
            if(TCP_SendDone(&port7TCB))
            {
                // check to see  if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if(rxLen > 0)
                {
                    hit_counter++;
                    rxLen = TCP_GetReceivedData(&port7TCB);
                    
                    unsigned temp = rxLen; 
                    for(uint8_t cnt = 0; cnt < temp; cnt++)
                    {
                        EUSART2_Write(rxdataPort7[cnt]); 
                    }
#if 0                    
                    if(rxdataPort7[0]== '0')
                    {
                        LED_LAT = 0;
                        len = sprintf(txdataPort7,"counter %i. led off\n",hit_counter);
                    }
                    else if(rxdataPort7[0]== '1'){
                        LED_LAT = 1;
                        len = sprintf(txdataPort7,"counter %i. led on\n",hit_counter);
                    }
                    else
                        len = sprintf(txdataPort7,"counter %i. enter 1 or 0\n",hit_counter);
#endif
                    
                    
                    // reuse the RX buffer
                    
                    if(rxdataPort7[0] == 'G')
                    {
                        //TCP_Send(&port7TCB, ptr, strlen(ptr));
                    }
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
                    //send a message back to client
                    TCP_Send(&port7TCB, txdataPort7, strlen(txdataPort7));
                }
            }
            break;

        case SOCKET_IN_PROGRESS:
            if(cnt)
                EUSART2_putrs("In Progress\r\n");
            break;

        case SOCKET_CLOSING:
            if(cnt)
                EUSART2_putrs("Closing\r\n");
            
            TCP_SocketRemove(&port7TCB); 
            //socket_state = NOT_A_SOCKET; 
            break; 
        default:
            // we should not end up here
            break;
    }
}

void queueInsert(uint8_t ucData)
{
    
}

uint8_t queueRead(void)
{
    
}

uint8_t queuePeek(void)
{
    
}
/**
 End of File
*/