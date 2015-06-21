/*
 * uart.h
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */

#include <msp430g2303.h>

#ifndef SRC_UART_H_
#define SRC_UART_H_

int uartReceiveBuff(char* ou_iBuff, int in_iBuffSize);
int uartSendBuff(const char* in_ariBuff, int in_iSize);
int getUartRxCnt();
void clearRx();


#endif /* SRC_UART_H_ */
