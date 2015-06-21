/*
 * imc18_bsp_port.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: yuri
 */

#include "imc18_bsp_port.h"

void portInit()
{
	P2DIR |= OUT0 | OUT1 | OUT2; // | OUT3;
	P2DIR |= LED_UNLOCK | LED_LINE | LED_PROG;
}

void portSwitch(PORT_DEV in_iDev, PORT_STATE in_iState)
{
	switch (in_iDev) {
	case PORT_OUT0 :
		if (PORT_ON == in_iState)
			P2OUT |= OUT0;
		else
			P2OUT &= -1 ^ OUT0;
		break;
	case PORT_OUT1 :
		if (PORT_ON == in_iState)
			P2OUT |= OUT1;
		else
			P2OUT &= -1 ^ OUT1;
		break;
	case PORT_OUT2 :
		if (PORT_ON == in_iState)
			P2OUT |= OUT2;
		else
			P2OUT &= -1 ^ OUT2;
		break;
	case PORT_OUT3 :
		if (PORT_ON == in_iState)
			P2OUT |= OUT3;
		else
			P2OUT &= -1 ^ OUT3;
		break;
	case PORT_LEDUNLOCK :
		if (PORT_ON == in_iState)
			P2OUT |= LED_UNLOCK;
		else
			P2OUT &= -1 ^ LED_UNLOCK;
		break;
	case PORT_LEDLINE :
		if (PORT_ON == in_iState)
			P2OUT |= LED_LINE;
		else
			P2OUT &= -1 ^ LED_LINE;
		break;
	case PORT_LEDPEG :
		if (PORT_ON == in_iState)
			P2OUT |= LED_PROG;
		else
			P2OUT &= -1 ^ LED_PROG;
		break;
	default :
		break;
	}
}

