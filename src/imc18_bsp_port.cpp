/*
 * imc18_bsp_port.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: yuri
 */

#include "imc18_bsp_port.h"

void portInit()
{
	P2DIR |= LED_UNLOCK | LED_LINE | LED_PROG;
}

void portSwitch(PORT_DEV in_iDev, PORT_STATE in_iState)
{
	switch (in_iDev) {
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

