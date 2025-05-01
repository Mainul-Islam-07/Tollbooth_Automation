#include "Trigger.h"


const Switch_Config_t LED_Configs[LED_COUNT] = {
    {LED_CAMERA_GPIO_Port, LED_CAMERA_Pin},
	{LED_PAYMENT_GPIO_Port, LED_PAYMENT_Pin},
    {LED_PING_GPIO_Port, LED_PING_Pin}
};

const Switch_Config_t Trigger_Configs[TRIGGER_COUNT] = {
    {SIREN_GPIO_Port, SIREN_Pin},
    {BOOM_BARRIER_GPIO_Port, BOOM_BARRIER_Pin},
    {LANE_OPERATION_GPIO_Port, LANE_OPERATION_Pin},
	{OVERHEAD_LIGHT_GPIO_Port, OVERHEAD_LIGHT_Pin},
};


void LED_Control(LED_Name_t led, Switch_State_t state) {
    if (led < LED_COUNT) {
        HAL_GPIO_WritePin(LED_Configs[led].port, LED_Configs[led].pin, (GPIO_PinState)state);
    }
}

void LED_Toggle(LED_Name_t led){
	if (led < LED_COUNT) {
		HAL_GPIO_TogglePin(LED_Configs[led].port, LED_Configs[led].pin);
	}
}

Switch_State_t LED_State(LED_Name_t led){
	return HAL_GPIO_ReadPin(LED_Configs[led].port, LED_Configs[led].pin);
}


void Trigger_Control(Trigger_Pin_t output, Switch_State_t state) {
    if (output < TRIGGER_COUNT) {
        HAL_GPIO_WritePin(Trigger_Configs[output].port, Trigger_Configs[output].pin, (GPIO_PinState)state);
    }
}

void state_Trigger (State_t state){
	switch (state){
	case STATE_IDLE :
		idleAction();
		break;

	case STATE_PAYMENT :
		paymentAction();
		break;

	case STATE_WAIT_CAR :
		waitCarAction();
		break;

	case STATE_CLOSE :
		closeAction();
		break;

	case STATE_PANIC :
		panicAction();
		break;

	case STATE_FLEET :
		fleetAction();
		break;
	default:
		return;

	}

}

void idleAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, OFF);
	Trigger_Control(TRIGGER_SIREN, OFF);
}
void paymentAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, OFF);
	Trigger_Control(TRIGGER_SIREN, OFF);
}
void waitCarAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, ON);
	Trigger_Control(TRIGGER_SIREN, OFF);
}
void closeAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, ON);
	Trigger_Control(TRIGGER_SIREN, OFF);
}
void fleetAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, ON);
	Trigger_Control(TRIGGER_SIREN, OFF);
}
void panicAction(){

	Trigger_Control(TRIGGER_BOOM_BARRIER, OFF);
	Trigger_Control(TRIGGER_SIREN, ON);

}

void lightOn(){
	Trigger_Control(TRIGGER_OVERHEAD_LIGHT, ON);
}

void lightoff(){
	Trigger_Control(TRIGGER_OVERHEAD_LIGHT, OFF);
}

void laneOn(){
	Trigger_Control(TRIGGER_LANE_OPERATION, ON);
}

void laneOff(){
	Trigger_Control(TRIGGER_LANE_OPERATION, OFF);
}

