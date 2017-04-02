/*
 * rfid.c
 *
 *  Created on: Apr 2, 2017
 *      Author: dalto
 */


#include "rfid.h"
#include <stdio.h>
#include <stdlib.h>

/* UART config for baud rate of 9600 */
const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    156,                                     // BRDIV = 156
    4,                                       // UCxBRF = 4
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // LSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void rfid_init() {
    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    /* Enabling interrupts */
    //MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    //MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
}

int getID() {
    uint8_t digits[12];
    memset(digits, 0x00, 12);

    int i;
    for(i=0; i<11; i++) {
        while(UCRXIFG == 0) {}
        uint8_t rxdByte = MAP_UART_receiveData(EUSCI_A0_BASE);
        if(rxdByte == '\x0d') {
            break;
        }

        digits[i] = rxdByte;
    }

    int ID = atoi(digits);

    return ID;
}

/* EUSCI A0 UART ISR - Echoes data back to PC host */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        uint8_t test = MAP_UART_receiveData(EUSCI_A0_BASE);
    }
}
