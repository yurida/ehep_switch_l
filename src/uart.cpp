/*
 * uart.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */
#include "uart.h"

int uartTxNumber, uartTxIndex;
int uartRxNumber, uartRxIndex;
const char* uartTxChars;
char* uartRxBuff;

/*******************************************************************************
 *
 */
int uartSendBuff(const char* in_ariBuff, int in_iSize)
{
	int iRetCode = 0;

	if (0 != (IE2 & UCA0TXIE))
		return -1; // uart still transmit something
    uartTxChars = in_ariBuff;
    uartTxNumber = in_iSize;
    uartTxIndex = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = uartTxChars[uartTxIndex++];
    return iRetCode;
}

/*******************************************************************************
 *
 */
int uartReceiveBuff(char* ou_iBuff, int in_iBuffSize)
{
	int iRetCode = 0;
	IE2 &= (-1 ^ UCA0RXIE);     // Disable USCI_A0 RX interrupt
	clearRx();
	uartRxBuff = ou_iBuff;
	IE2 |= UCA0RXIE;     // Enable USCI_A0 RX interrupt
    return iRetCode;
}

int getUartRxCnt()
{
	return uartRxIndex;
}

void clearRx()
{
	uartRxIndex = 0;
}

/*******************************************************************************
 *
 */
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR(void)
{
//	while (!(IFG2 & UCA0TXIFG))
//		;                // USCI_A0 TX buffer ready?
	uartRxBuff[uartRxIndex] = UCA0RXBUF; // TX -> RXed character
	uartRxIndex++;
	// TODO check when disable interrupt
}

void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCI0TX_ISR (void)
{
	UCA0TXBUF = uartTxChars[uartTxIndex++];                 // TX next character
	if (uartTxIndex >= uartTxNumber)              // TX over?
		IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}

