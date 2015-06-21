/*
 * cmd_handler.h
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */

#ifndef SRC_CMD_HANDLER_H_
#define SRC_CMD_HANDLER_H_

#include "imc18_bsp_port.h"

typedef enum {
	CMDRCV_INIT,
	CMDRCV_IDLE,
	CMDRCV_SIGNCHECK,
	CMDRCV_SNCHECK,
	CMDRCV_CMD_DECODE,
	CMDRCV_REZ_OK,
	CMDRCV_MAX
} CMDRCV_STATE;

void smCmdReceiverReset();
int smCmdReceiver();
int cmdDecoder(char* in_pCommand);

#endif /* SRC_CMD_HANDLER_H_ */
