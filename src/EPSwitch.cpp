/*
 * End Point Switch - line control
 * EPSwitch.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: yuri
 */
#include "EPSwitch.h"
#include "imc18_bsp_port.h"
#include "cmd_handler.h"
#include "version.h"

void delay(unsigned int in_iDelayMs);

unsigned char iRxChar;
unsigned char iPout;

/*******************************************************************************
 *
 */
int main(int nargs, char** vargs) {

	int iCnt;
	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

	portInit();
	// After start indication
	portSwitch(PORT_LEDUNLOCK, PORT_ON);
	delay(100);
	portSwitch(PORT_LEDUNLOCK, PORT_OFF);
	delay(100);
	portSwitch(PORT_LEDUNLOCK, PORT_ON);
	delay(100);
	portSwitch(PORT_LEDUNLOCK, PORT_OFF);

	if (CALBC1_1MHZ == 0xFF) // If calibration constant erased
	{
		for (;;) { // Trap for error
			portSwitch(PORT_LEDUNLOCK, PORT_ON);
			delay(100);
			portSwitch(PORT_LEDUNLOCK, PORT_OFF);
			delay(100);
		}
	}
	DCOCTL = 0;                          // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;
	P1SEL = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 8;                              // 1MHz 115200
	UCA0BR1 = 0;                              // 1MHz 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

	__bis_SR_register(GIE);       // interrupts enabled
//	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled

	uartSendBuff(DEVICE_MODEL, 8);
	delay(100);
	uartSendBuff("\r\n", 2);
	delay(100);
	uartSendBuff(DEVICE_SN, 8);
	delay(100);
	uartSendBuff("\r\n", 2);

	smCmdReceiverReset();

//	  P1DIR |= 0xFF;                            // Set P1.0 to output direction
//	  P2DIR |= 0xFF;
//	  P3DIR |= 0xFF;                            // Set P1.0 to output direction

	while (1)                                 // Test P1.4
	{
		smCmdReceiver();
//		  iPout = 0x01;
//		portSwitch(PORT_LEDLINE, PORT_ON);
//		delay(1000);
//		portSwitch(PORT_LEDLINE, PORT_OFF);
//		  for (iCnt = 0; iCnt < 8; iCnt++)
//		  {
//			  P2OUT = iPout;
//			  iPout <<= 1;
//			  delay(1000);
//		  }

//		  P1OUT = 0xFF;
//		  P2OUT = 0xFF;
//		  P3OUT = 0xFF;
//		  delay(1000);
//		  P1OUT = 0x00;
//		  P2OUT = 0x00;
//		  P3OUT = 0x00;
		delay(10);

//	    if ((0x10 & P1IN)) P1OUT |= 0x01;       // if P1.4 set, set P1.0
//	    else P1OUT &= ~0x01;                    // else reset
	}

	return 0;
}

/**
 *
 * @param in_iDelayMs
 */
void delay(unsigned int in_iDelayMs) {
	unsigned int iCnt;
	unsigned int iCntMsec;

	for (iCntMsec = 0; iCntMsec < in_iDelayMs; iCntMsec++) {
		for (iCnt = 0; iCnt < 60; iCnt++)
			asm (" nop ");
	}
}

