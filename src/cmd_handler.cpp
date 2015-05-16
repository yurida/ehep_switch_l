/*
 * cmd_handler.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: yuri
 */

#include "cmd_handler.h"
#include "version.h"
#include "tools.h"
#include "uart.h"

char 			iInCmdBuffer[32];
int 			iInCmdBufInx;
CMDRCV_STATE 	iState;

void smCmdReceiverReset()
{
	iState = CMDRCV_INIT;
}

int smCmdReceiver()
{
	int iRetCode = -1;

	switch (iState) {
	case CMDRCV_INIT :
		iInCmdBufInx = 0;
//		uartReceiveBuff(iInCmdBuffer, 32);
		iState = CMDRCV_IDLE;
		iRetCode = 0;
		break;
	case CMDRCV_IDLE :
		if (1 <= iInCmdBufInx)
		{
			if ('U' == iInCmdBuffer[0]) {
				iState = CMDRCV_SIGNCHECK;
				iRetCode = 0;
			} else {
				iState = CMDRCV_INIT;
				iRetCode = CMDRCV_IDLE;
			}
		}
		break;
	case CMDRCV_SIGNCHECK :
		if (2 <= iInCmdBufInx)
		{
			// TODO test for Command signature UU
			iState = CMDRCV_SNCHECK;
			iRetCode = 0;
		}
		break;
	case CMDRCV_SNCHECK :
		if (2 + 8 <= iInCmdBufInx)
		{
			// TODO test for Unit Serial number
			if (0 == buffcmp(DEVICE_SN, iInCmdBuffer + 2, 8)) {
				uartSendBuff("SN:Ok\r\n", 7);
				iState = CMDRCV_CMD_DECODE;
				iRetCode = 0;
			} else {
				uartSendBuff("SN:Error\r\n", 10);
				iState = CMDRCV_INIT;
				iRetCode = CMDRCV_SNCHECK;
			}
		}
		break;
	case CMDRCV_CMD_DECODE :


		iState = CMDRCV_INIT;
		iRetCode = 0;
		break;
	default :
		break;


	}



	return iRetCode;
}

