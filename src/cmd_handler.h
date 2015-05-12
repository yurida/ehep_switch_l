/*
 * cmd_handler.h
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */

#ifndef SRC_CMD_HANDLER_H_
#define SRC_CMD_HANDLER_H_

typedef enum {
	CMDRCV_INIT,
	CMDRCV_IDLE,
	CMDRCV_SIGNCHECK,
	CMDRCV_SNCHECK,
	CMDRCV_CMD_DECODE,
	CMDRCV_MAX
} CMDRCV_STATE;

void smCmdReceiverReset();
int smCmdReceiver();

#endif /* SRC_CMD_HANDLER_H_ */
