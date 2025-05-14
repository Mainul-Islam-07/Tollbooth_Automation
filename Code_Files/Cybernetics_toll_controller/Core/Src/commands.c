/*
 * commands.c
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */
#include "commands.h"
#include "app_main.h"
#include "tcp_handler.h"

PC_TO_MCU_Command_t currentCommand;

uint32_t count = 0;


// Define MCU-to-PC command list
Command_t mcuToPcCommands[] = {
    {"VEHICLE_DETECTED\n", CMD_VEHICLE_DETECTED},
    {"BARRIER_ON\n", CMD_BARRIER_OPEN},
    {"BARRIER_OFF\n", CMD_BARRIER_CLOSE},
    {"SIREN_ON\n", CMD_SIREN_ON},
    {"SIREN_OFF\n", CMD_SIREN_OFF},
    {"RESET_DONE\n", CMD_RESET_DONE},
    {"PAID_DONE\n", CMD_PAID_DONE},
	{"CONNECT_ON\n", CMD_CONNECTED},
	{"CAMERA_ACK\n", CMD_CAMERA_TRIGGER_RESP},
	{"TCU_OPEN\n" , CMD_TCU_OPEN},
	{"TCU_CLOSE\n", CMD_TCU_CLOSE},
	{"UNKNOWN\n" , CMD_UNKNOWN}
};

// Define PC-to-MCU command list
Command_t pcToMcuCommands[] = {
    {"RESET", CMD_RESET},
    {"PAID", CMD_PAID},
    {"BARRIER_ON", CMD_OPEN_BARRIER},
    {"BARRIER_OFF", CMD_CLOSE_BARRIER},
    {"SIREN_ON", CMD_ON_SIREN},
	{"CAMERA_CAPTURE", CMD_CAMERA_TRIGGER},
	{"LIGHT_ON", CMD_LIGHT_ON},
	{"LIGHT_OFF", CMD_LIGHT_OFF},
	{"LANE_ON", CMD_LANE_ON},
	{"LANE_OFF", CMD_LANE_OFF},
    {"SIREN_OFF", CMD_OFF_SIREN},
	{"PC_OFF", CMD_SHUT_DOWN},
	{"HARD_RESET", CMD_HARD_RESET}
};

// Function to get Command ID from String
PC_TO_MCU_Command_t getCommandID(const char *commandName) {
    for (uint8_t i = 0; i < sizeof(pcToMcuCommands) / sizeof(Command_t); i++) {
        if (strcmp(commandName, pcToMcuCommands[i].name) == 0) {
            return pcToMcuCommands[i].commandID;
        }
    }
    return CMD_NOCOMMAND;  // Default to CMD_RESET if command is unknown
}

const char* getCommandName(MCU_TO_PC_Command_t commandID) {
    for (size_t i = 0; i < (sizeof(mcuToPcCommands) / sizeof(mcuToPcCommands[0])); i++) {
        if (mcuToPcCommands[i].commandID == commandID) {
            return mcuToPcCommands[i].name;
        }
    }
    return "UNKNOWN";
}

void sendResponse (MCU_TO_PC_Command_t commandID){
	const char* responseName;
	responseName = getCommandName(commandID);
	printf("%ld ", count++);
	uartTransmitDMA(global.comm_uart,responseName);
	for (sn = 0; sn < MAX_SOCK_NUM; sn++) {
		if (sock_status[sn] == SOCK_STATUS_ESTABLISHED){
				SendToSocket(sn,responseName);
		}
	}
}



void processReceivedCommand(char *command, CommandSource_t source) {
    PC_TO_MCU_Command_t cmdID = getCommandID(command);
    currentCommand = cmdID;

    if (source == SOURCE_UART) {
        printf("Received UART Command: %s -> ID: %d\n", command, cmdID);
    } else if (source == SOURCE_TCP) {
        printf("Received TCP Command: %s -> ID: %d\n", command, cmdID);
    }
}
