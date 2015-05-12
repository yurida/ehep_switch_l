/*
 * imc18_bsp_port.h
 *
 *  Created on: Apr 9, 2015
 *      Author: yuri
 */

#ifndef SRC_IMC18_BSP_PORT_H_
#define SRC_IMC18_BSP_PORT_H_

#include <msp430g2303.h>

#define LED_UNLOCK			(1 << 0)
#define LED_LINE			(1 << 1)
#define LED_PROG			(1 << 2)

typedef enum {
	PORT_LEDUNLOCK,
	PORT_LEDLINE,
	PORT_LEDPEG
} PORT_DEV;

typedef enum {
	PORT_OFF,
	PORT_ON
} PORT_STATE;

void portInit();
void portSwitch(PORT_DEV iDev, PORT_STATE iState);

#endif /* SRC_IMC18_BSP_PORT_H_ */
