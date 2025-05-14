#include "state_machine.h"
#include "stm32f1xx_hal.h"
#include "Trigger.h"
#include "socket.h"
#include "tcp_handler.h"
#include "app_main.h"
#include "ISR_handler.h"


State_t currentState;
uint32_t stateTick = 0;
uint32_t panicTick = 0;
uint32_t connectTick = 0;
uint32_t cameraTick = 0;
uint32_t paidTick = 0;
uint32_t laneTick = 0;
uint32_t shutdowntick = 0;

volatile bool once = true;
volatile bool shutdowninit = false;
// Individual state handlers
State_t handle_idle(Event_t evt) {
	once = true;
	#if (Mukhterpur == 1)
		switch (evt) {
		    case EVT_CAMERA_TRIGGER:    sendResponse(CMD_CAMERA_TRIGGER_RESP);   return STATE_PAYMENT;
			case EVT_ACTIVATE_SIREN: 	sendResponse(CMD_SIREN_ON); 		return STATE_PANIC;
			case EVT_FORCE_OPEN: 		sendResponse(CMD_BARRIER_OPEN); 	return STATE_FLEET;
			case EVT_SYSTEM_RESET: 									 		return STATE_IDLE;
			default: 					printState("STATE_IDLE");			return STATE_IDLE;

			}

	#else

		switch (evt) {
//Sensoer Based Events
			case EVT_CAR_DETECTED: 		sendResponse(CMD_VEHICLE_DETECTED); return STATE_PAYMENT; 	// Car Detection in 1st loop coil sensor
			case EVT_ACTIVATE_SIREN: 	sendResponse(CMD_SIREN_ON); 		return STATE_PANIC; 	// Car Passes without Payment (case which accounts 1st loop coil malfunction)
//Command Based Events
			case EVT_PAYMENT_COMPLETED: sendResponse(CMD_PAID_DONE); 		return STATE_WAIT_CAR;  // Forceful Payment completion (case which accounts for 1st loop coil malfunction)
			case EVT_FORCE_OPEN: 		sendResponse(CMD_BARRIER_OPEN); 	return STATE_FLEET; 	// Forceful Barrier opening
//			case EVT_FORCE_CLOSE: 		sendResponse(CMD_BARRIER_CLOSE);	return STATE_CLOSE;		// Forceful Barrier Closing   (case which accounts Boom Barrier Malfunction)
			default: 					printState("STATE_IDLE"); 			return STATE_IDLE;
			}

	#endif
}

State_t handle_payment(Event_t evt) {

	#if (Mukhterpur == 1)
		switch (evt) {
			case EVT_PAYMENT_COMPLETED: sendResponse(CMD_PAID_DONE);  		return STATE_CLOSE;
			case EVT_ACTIVATE_SIREN: 	sendResponse(CMD_SIREN_ON); 		return STATE_PANIC;
			case EVT_SYSTEM_RESET: 									 		return STATE_IDLE;
			default: 					printState("STATE_PAYMENT"); 		return STATE_PAYMENT;
		}
	#else
		switch (evt) {
//Sensoer Based Events
			case EVT_PAYMENT_COMPLETED: sendResponse(CMD_PAID_DONE); 		return STATE_WAIT_CAR;  // Payment Done
			case EVT_ACTIVATE_SIREN:	sendResponse(CMD_SIREN_ON);  		return STATE_PANIC;		// Car Passes without Payment
//Command Based Events
			case EVT_FORCE_OPEN:  		sendResponse(CMD_BARRIER_OPEN); 	return STATE_FLEET;		// Forceful Barrier opening
			case EVT_FORCE_CLOSE: 		sendResponse(CMD_BARRIER_CLOSE);	return STATE_CLOSE;		// Forceful Barrier Closing
//			case EVT_SIREN_OFF: 		sendResponse(CMD_SIREN_OFF);		return STATE_IDLE;		// Turning siren off (Starting from Beginning) (case which accounts siren malfunction)
			case EVT_SYSTEM_RESET: 		sendResponse(CMD_RESET_DONE); 		return STATE_IDLE;
			default: 					printState("STATE_PAYMENT"); 		return STATE_PAYMENT;
		}

	#endif
}

State_t handle_wait_car(Event_t evt) {

	#if (Mukhterpur == 1)
		switch (evt) {
			default: 					printState("STATE_WAIT_CAR");	    return STATE_WAIT_CAR;
		}

	#else
		switch (evt) {
//Sensoer Based Events
			case EVT_IR_CHECK: 												return STATE_CLOSE;		// Car passed 2nd loop coil sensor
//Command Based Events
//	        case EVT_DETECTION_FAIL: 										return STATE_CLOSE;		// Forceful state skip (case which accounts 2nd loop coil malfunction)
//	        case EVT_SIREN_OFF: 		sendResponse(CMD_SIREN_OFF);		return STATE_IDLE;		// Turning siren off (Starting from Beginning) (case which accounts siren malfunction)
			case EVT_SYSTEM_RESET: 		sendResponse(CMD_RESET_DONE); 		return STATE_IDLE;
			default: 					printState("STATE_WAIT_CAR");	    return STATE_WAIT_CAR;
		}

	#endif
}

State_t handle_fleet(Event_t evt) {
	#if (Mukhterpur == 1)
		switch (evt)
		{
			case EVT_FORCE_CLOSE:		sendResponse(CMD_BARRIER_CLOSE);	 return STATE_CLOSE;
			case EVT_SYSTEM_RESET: 									 		 return STATE_IDLE;
			default: 					printState("STATE_FLEET"); 			 return STATE_FLEET;
		}
	#else
		switch (evt) {
//Command Based Events
			case EVT_FORCE_CLOSE:		sendResponse(CMD_BARRIER_CLOSE);	 return STATE_CLOSE; // Forceful Barrier Closing
//	        case EVT_SIREN_OFF: 		sendResponse(CMD_SIREN_OFF);		 return STATE_IDLE;	 // Turning siren off (Starting from Beginning) (case which accounts siren malfunction)
			case EVT_SYSTEM_RESET: 		sendResponse(CMD_RESET_DONE); 		 return STATE_IDLE;
			default: 					printState("STATE_FLEET"); 			 return STATE_FLEET;
		}
	#endif
}
State_t handle_panic(Event_t evt) {
	#if (Mukhterpur == 1)
		switch (evt) {
			case EVT_SIREN_OFF: 			sendResponse(CMD_SIREN_OFF); 		return STATE_IDLE;
			case EVT_SYSTEM_RESET: 										 		return STATE_IDLE;
			default:
				while(once){
					panicTick = HAL_GetTick();
					once = false;
				}
				if (HAL_GetTick() - panicTick > 5000)
					{
						panicTick = HAL_GetTick();
						return STATE_IDLE;
					}
					else{
						printState("STATE_PANIC");
						return STATE_PANIC;
					}
		}
	#else
		switch (evt) {
//Command Based Events
			case EVT_FORCE_CLOSE: 		sendResponse(CMD_BARRIER_CLOSE); 	return STATE_CLOSE;	//Forceful Barrier Closing
			case EVT_SIREN_OFF:			sendResponse(CMD_SIREN_OFF); 		return STATE_IDLE;	// Turning siren off and Start from Beginning
			case EVT_SYSTEM_RESET: 		sendResponse(CMD_RESET_DONE); 		return STATE_IDLE;
			default: 					printState("STATE_PANIC"); 			return STATE_PANIC;

		}
	#endif
}

State_t handle_close(Event_t evt) {
	#if (Mukhterpur == 1)
		switch (evt) {
			case EVT_CAR_PASSED: 		sendResponse(CMD_BARRIER_CLOSE);	return STATE_IDLE;
			case EVT_SYSTEM_RESET: 									 		return STATE_IDLE;
			default: 					printState("STATE_CLOSE");			return STATE_CLOSE;
		}
	#else
		switch (evt) {
//Sensor Based Events
			case EVT_CAR_PASSED: 		sendResponse(CMD_BARRIER_CLOSE);	return STATE_IDLE;	// Car exited the Tollbooth safely
//Command Based Events
			case EVT_FORCE_CLOSE: 		sendResponse(CMD_BARRIER_CLOSE); 	return STATE_IDLE; 	// Forceful Barrier Closing
	//      case EVT_SIREN_OFF:  		sendResponse(CMD_SIREN_OFF); 		return STATE_IDLE;	// Turning siren off and Start from Beginning (case which accounts siren malfunction)
			default: 					printState("STATE_CLOSE");			return STATE_CLOSE;
		}
	#endif
	}

// Main event handler delegating to individual handlers
State_t handle_event(State_t current, Event_t evt) {

		switch (current) {
		case STATE_IDLE: 		return handle_idle(evt);
		case STATE_PAYMENT: 	return handle_payment(evt);
		case STATE_WAIT_CAR: 	return handle_wait_car(evt);
		case STATE_FLEET:		return handle_fleet(evt);
		case STATE_PANIC: 		return handle_panic(evt);
		case STATE_CLOSE: 		return handle_close(evt);
		default: 				return STATE_IDLE;
    }
}

const char* state_to_str(State_t state) {
    static const char* state_names[] = {"IDLE", "PAYMENT", "WAIT_CAR", "FLEET", "PANIC", "CLOSE"};
    return state_names[state];
}

void run_state_machine(State_t* current_state, Event_t event) {
    State_t new_state = handle_event(*current_state, event);
    if (new_state != *current_state) {
        //printf("State Transition: %s -> %s\n", state_to_str(*current_state), state_to_str(new_state));
        *current_state = new_state;
    }
}



// Function to generate events from sensors and commands
Event_t generate_event(SensorSystem_t *sensorSystem, uint8_t cmdID, State_t Current_State) {
	oneCycleIgnore = false;
	#if Mukhterpur == 1
//		if (sensorSystem->tcubox_status.prev_state == SENSOR_INACTIVE && sensorSystem->tcubox_status.state == SENSOR_ACTIVE)  { sendResponse(CMD_TCU_CLOSE); }
//		if (sensorSystem->tcubox_status.prev_state == SENSOR_ACTIVE && sensorSystem->tcubox_status.state == SENSOR_INACTIVE)  { sendResponse(CMD_TCU_OPEN); }
		if (sensorSystem->exitloopCoil.prev_state == SENSOR_ACTIVE 	 && sensorSystem->exitloopCoil.state == SENSOR_INACTIVE && Current_State == STATE_IDLE )   {sensorSystem->exitloopCoil.prev_state = sensorSystem->exitloopCoil.state;  return EVT_ACTIVATE_SIREN;}
		if (sensorSystem->exitloopCoil.prev_state == SENSOR_ACTIVE 	 && sensorSystem->exitloopCoil.state == SENSOR_INACTIVE && Current_State == STATE_PAYMENT ) {sensorSystem->exitloopCoil.prev_state = sensorSystem->exitloopCoil.state;  return EVT_ACTIVATE_SIREN;}
		if (sensorSystem->exitloopCoil.prev_state == SENSOR_ACTIVE	 && sensorSystem->exitloopCoil.state == SENSOR_INACTIVE && Current_State == STATE_CLOSE )   {sensorSystem->exitloopCoil.prev_state = sensorSystem->exitloopCoil.state;	return EVT_CAR_PASSED;}

	#else

// Sensor-based events
// IDLE STATE SCENARIO

		if (sensorSystem->entryloopCoil.prev_state == SENSOR_ACTIVE && sensorSystem->entryloopCoil.state == SENSOR_ACTIVE && Current_State == STATE_IDLE ) 		 return EVT_CAR_DETECTED;
		if (sensorSystem->exitloopCoil.prev_state  == SENSOR_ACTIVE && sensorSystem->exitloopCoil.state  == SENSOR_INACTIVE && Current_State == STATE_IDLE ) 	 return EVT_ACTIVATE_SIREN;
// PAYNENT STATE SCENARIO
		if (sensorSystem->exitloopCoil.prev_state  == SENSOR_ACTIVE && sensorSystem->exitloopCoil.state  == SENSOR_INACTIVE && Current_State == STATE_PAYMENT )  return EVT_ACTIVATE_SIREN;
// WAIT_CAR STATE SCENARIO
		if (sensorSystem->exitloopCoil.prev_state  == SENSOR_ACTIVE && sensorSystem->exitloopCoil.state  == SENSOR_INACTIVE && Current_State == STATE_WAIT_CAR ) return EVT_IR_CHECK;
// CLSOE STATE SCENARIO
		if (sensorSystem->irSensor.prev_state 	   == SENSOR_ACTIVE && sensorSystem->irSensor.state 	 == SENSOR_INACTIVE && Current_State == STATE_CLOSE ) 	 return EVT_CAR_PASSED;
		if (sensorSystem->irSensor.prev_state      == SENSOR_INACTIVE && sensorSystem->irSensor.state 	 == SENSOR_INACTIVE && Current_State == STATE_CLOSE ) 	 return EVT_CAR_PASSED; // optional code to avoid IR
		//if (sensorSystem->irSensor.prev_state == SENSOR_INACTIVE && sensorSystem->irSensor.state == SENSOR_INACTIVE && Current_State == STATE_CLOSE ) return EVT_CAR_PASSED;


	#endif
// Command-based events
#if Mukhterpur == 1
		switch (cmdID) {
		case CMD_RESET: 			return EVT_SYSTEM_RESET;
		case CMD_PAID: 				return EVT_PAYMENT_COMPLETED;
		case CMD_OPEN_BARRIER: 		return EVT_FORCE_OPEN;
		case CMD_CLOSE_BARRIER: 	return EVT_FORCE_CLOSE;
		case CMD_ON_SIREN: 			return EVT_ACTIVATE_SIREN;
		case CMD_OFF_SIREN: 		return EVT_SIREN_OFF;
		case CMD_CAMERA_TRIGGER: 	return EVT_CAMERA_TRIGGER;
		case CMD_LANE_ON:           laneOn(); return EVT_UNKNOWN;
		case CMD_LANE_OFF:          laneOff(); return EVT_UNKNOWN;
		case CMD_LIGHT_ON:			lightOn(); return EVT_UNKNOWN;
		case CMD_LIGHT_OFF:  		lightoff(); return EVT_UNKNOWN;

		default: 					return EVT_UNKNOWN;

		}
#else
	switch (cmdID) {
		case CMD_RESET: 		return EVT_SYSTEM_RESET;
		case CMD_PAID: 			return EVT_PAYMENT_COMPLETED;
		case CMD_OPEN_BARRIER: 	return EVT_FORCE_OPEN;
		case CMD_CLOSE_BARRIER: return EVT_FORCE_CLOSE;
		case CMD_ON_SIREN: 		return EVT_ACTIVATE_SIREN;
		case CMD_OFF_SIREN: 	return EVT_SIREN_OFF;
		case CMD_RX_TEST: 		return EVT_RX_TEST;
		default: 				return EVT_UNKNOWN;
		}
#endif

}

void printState(const char* message) {
	if (HAL_GetTick() - stateTick >= 2000)
	{
		stateTick = HAL_GetTick();
		printf("%s\n", message);
	}

}

void connectionFeedback(void){
	if (HAL_GetTick() - connectTick >= 500)
		{
			connectTick = HAL_GetTick();
//			sendResponse(CMD_CONNECTED);
			const char* connectionStatus = "CONNECT_ON ";
			const char* sendBarrierData = (HAL_GPIO_ReadPin(BOOM_BARRIER_GPIO_Port, BOOM_BARRIER_Pin) == GPIO_PIN_SET) ?
					"BARRIER_ON " : "BARRIER_OFF ";
//			send(0, (uint8_t*)sendBarrierData, strlen(sendBarrierData));
			const char* sendSirenData = (HAL_GPIO_ReadPin(SIREN_GPIO_Port, SIREN_Pin) == GPIO_PIN_SET) ?
					"SIREN_ON " : "SIREN_OFF ";
			const char* sendLightData = (HAL_GPIO_ReadPin(OVERHEAD_LIGHT_GPIO_Port, OVERHEAD_LIGHT_Pin) == GPIO_PIN_SET) ?
					"LIGHT_ON " : "LIGHT_OFF ";
			const char* sendLaneData = (HAL_GPIO_ReadPin(LANE_OPERATION_GPIO_Port, LANE_OPERATION_Pin) == GPIO_PIN_SET) ?
					"LANE_ON " : "LANE_OFF ";
			const char* sendTcuStatusData = (HAL_GPIO_ReadPin(TCU_BOX_STATUS_GPIO_Port, TCU_BOX_STATUS_Pin) == GPIO_PIN_RESET) ?
					 "TCU_OPEN " : "TCU_CLOSE ";
			global.msg_counter++;
//			const char* sendTcuStatusData = (sensorSystem.tcubox.state == SENSOR_ACTIVE) ?
//								 "TCU_CLOSE " : "TCU_OPEN ";



			char result[127];  // Ensure the buffer is large enough
			snprintf(result, sizeof(result), "%s%s%s%s%s%s%010lu\n", connectionStatus, sendBarrierData, sendSirenData, sendLightData, sendLaneData, sendTcuStatusData, global.msg_counter);
			for (sn = 0; sn < MAX_SOCK_NUM; sn++) {
				if (sock_status[sn] == SOCK_STATUS_ESTABLISHED){
						send(sn, (uint8_t*)result, strlen(result));
				}
			}

		}
}

void check_and_execute(uint8_t cmdID, State_t Current_State){
	if (cmdID == CMD_CAMERA_TRIGGER && (LED_State(LED_CAMERA) == OFF)){
		LED_Control(LED_CAMERA,ON);
		cameraTick = HAL_GetTick();
	}
	if (cmdID == CMD_PAID && (LED_State(LED_PAYMENT) == OFF)){
		LED_Control(LED_PAYMENT,ON);
		paidTick = HAL_GetTick();
	}
	if (cmdID == CMD_LANE_ON){
		LED_Toggle(LED_PING);
		laneTick = HAL_GetTick();
	}
	if ((LED_State(LED_CAMERA) == ON) && ( HAL_GetTick() - cameraTick >= 1500)){
		LED_Control(LED_CAMERA,OFF);
	}
	if ((LED_State(LED_PAYMENT) == ON) && ( HAL_GetTick() - paidTick >= 1500)){
		LED_Control(LED_PAYMENT,OFF);
	}
	if (HAL_GetTick() - laneTick >= 7000){
		LED_Control(LED_PING, OFF);
		Trigger_Control(TRIGGER_LANE_OPERATION, OFF);
	}
	if (cmdID == CMD_HARD_RESET)
	{
		Trigger_Control(TRIGGER_BOOM_BARRIER,OFF);
		for (int i = 0; i<5; i++){
			Trigger_Control(TRIGGER_SIREN,ON);
			HAL_Delay(500);
			Trigger_Control(TRIGGER_SIREN,OFF);
			HAL_Delay(500);
		}
		NVIC_SystemReset();
	}
	if (cmdID == CMD_SHUT_DOWN)
	{
		shutdowntick = HAL_GetTick();
		shutdowninit = true;
	}

	if (shutdowninit == true && HAL_GetTick() - shutdowntick >= 10000 && Current_State == STATE_IDLE)
	{
		HAL_Delay(10000);
		Trigger_Control(TRIGGER_POWER, OFF);
		HAL_Delay(10000);
		shutdowninit = false;
		NVIC_SystemReset();
	}


}



