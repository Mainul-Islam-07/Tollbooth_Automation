/*
 * commands.h
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include <stdint.h>
#include "stdio.h"
#include "string.h"
#include "print_active.h"
#include "state_machine.h"
#include "usart.h"


#define CMD_BUFFER_SIZE 128

// Enum for MCU-to-PC Commands
typedef enum {
    CMD_VEHICLE_DETECTED,
    CMD_BARRIER_OPEN,
    CMD_BARRIER_CLOSE,
    CMD_SIREN_ON,
    CMD_SIREN_OFF,
    CMD_RESET_DONE,
    CMD_PAID_DONE,
	CMD_CONNECTED,
	CMD_CAMERA_TRIGGER_RESP,
	CMD_TCU_OPEN,
	CMD_TCU_CLOSE,
	CMD_UNKNOWN
} MCU_TO_PC_Command_t;

// Enum for PC-to-MCU Commands
typedef enum {
    CMD_RESET,
    CMD_PAID,
    CMD_OPEN_BARRIER,
    CMD_CLOSE_BARRIER,
    CMD_ON_SIREN,
    CMD_OFF_SIREN,
	CMD_CAMERA_TRIGGER,
	CMD_LIGHT_ON,
	CMD_LIGHT_OFF,
	CMD_LANE_ON,
	CMD_LANE_OFF,
	CMD_HARD_RESET,
	CMD_NOCOMMAND
} PC_TO_MCU_Command_t;


typedef enum {
    SOURCE_UART,
    SOURCE_TCP
} CommandSource_t;

extern PC_TO_MCU_Command_t currentCommand;


// Structure to define command properties
typedef struct {
    char *name;         // Command string name
    uint8_t commandID;  // Command code ID
} Command_t;


void processReceivedCommand(char *command, CommandSource_t source);


PC_TO_MCU_Command_t getCommandID(const char *commandName);

const char* getCommandName(MCU_TO_PC_Command_t commandID);
void sendResponse (MCU_TO_PC_Command_t commandID);

#endif /* INC_COMMANDS_H_ */
