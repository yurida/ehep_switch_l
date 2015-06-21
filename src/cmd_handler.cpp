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

void delay(unsigned int in_iDelayMs);

char 			iInCmdBuffer[32];
char*			pCommand;
//int 			iInCmdBufInx;
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
		uartReceiveBuff(iInCmdBuffer, 32);
		pCommand = 0;
		iState = CMDRCV_IDLE;
		iRetCode = 0;
		break;
	case CMDRCV_IDLE :
		if (1 <= getUartRxCnt())
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
		if (2 <= getUartRxCnt())
		{
			if ('U' == iInCmdBuffer[0] && 'U' == iInCmdBuffer[1]) {
				iState = CMDRCV_SNCHECK;
				iRetCode = 0;
			} else {
				iState = CMDRCV_INIT;
				iRetCode = CMDRCV_IDLE;
			}
		}
		break;
	case CMDRCV_SNCHECK :
		if (2 + 4 + 8 <= getUartRxCnt())
		{
			// Test Command for Unit right unit address
			if (0 == buffcmp(DEVICE_ADDR, iInCmdBuffer + 2, 4)) {
				pCommand = iInCmdBuffer + 2 + 4;
				iState = CMDRCV_CMD_DECODE;
				iRetCode = 0;
			} else {
				iState = CMDRCV_INIT;
				iRetCode = CMDRCV_IDLE;
			}
		}
		break;
	case CMDRCV_CMD_DECODE :
//		uartSendBuff(pCommand, 8);
		iRetCode = cmdDecoder(pCommand);
		if (0 == iRetCode)
			iRetCode = CMDRCV_REZ_OK;
		iState = CMDRCV_INIT;
		break;
	default :
		break;


	}

	return iRetCode;
}


int cmdDecoder(char* in_pCommand)
{
	int iRetCode = 0;
	int iCmd = -1;

	if (0 == buffcmp("ON_", in_pCommand + 5, 3))
		iCmd = 1;
	else if (0 == buffcmp("OFF", in_pCommand + 5, 3))
		iCmd = 2;
	else
		iRetCode = -3; // Set result as unsupported command

	if (-1 < iCmd)
	{
		// Switch for End device
		switch (*(in_pCommand + 4)) {
		case '0' :
			if (1 == iCmd)
				portSwitch(PORT_OUT0, PORT_ON);
			else if (2 == iCmd)
				portSwitch(PORT_OUT0, PORT_OFF);
			break;
		case '1' :
			if (1 == iCmd)
				portSwitch(PORT_OUT1, PORT_ON);
			else if (2 == iCmd)
				portSwitch(PORT_OUT1, PORT_OFF);
			break;
		case '2' :
			if (1 == iCmd)
				portSwitch(PORT_OUT2, PORT_ON);
			else if (2 == iCmd)
				portSwitch(PORT_OUT2, PORT_OFF);
			break;
		case '3' :
			if (1 == iCmd)
				portSwitch(PORT_OUT3, PORT_ON);
			else if (2 == iCmd)
				portSwitch(PORT_OUT3, PORT_OFF);
			break;
		case 'L' :
			if (1 == iCmd)
				portSwitch(PORT_LEDLINE, PORT_ON);
			else if (2 == iCmd)
				portSwitch(PORT_LEDLINE, PORT_OFF);
			break;
		default: // Set result as unsupported device
			iRetCode = -2;
			break;
		}
	}

	return iRetCode;
}
