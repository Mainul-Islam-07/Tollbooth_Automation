#ifndef INC_TRIGGER_H_
#define INC_TRIGGER_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "state_machine.h"


typedef enum {
    LED_CAMERA,
	LED_PAYMENT,
    LED_PING,
    LED_COUNT  // Keeps track of total LEDs
} LED_Name_t;

typedef enum {
    TRIGGER_SIREN,
    TRIGGER_BOOM_BARRIER,
	TRIGGER_LANE_OPERATION,
	TRIGGER_OVERHEAD_LIGHT,
    TRIGGER_COUNT  // Keeps track of total output pins
} Trigger_Pin_t;

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} Switch_Config_t;

typedef enum {
    OFF = 0,  // Maps to GPIO_PIN_RESET
    ON        // Maps to GPIO_PIN_SET
} Switch_State_t;

void state_Trigger(State_t state);
void LED_Control(LED_Name_t led, Switch_State_t state);
void Trigger_Control(Trigger_Pin_t output, Switch_State_t state);
void LED_Toggle(LED_Name_t led);
Switch_State_t LED_State(LED_Name_t led);

void idleAction();
void paymentAction();
void waitCarAction();
void closeAction();
void fleetAction();
void panicAction();
void lightOn();
void lightoff();
void laneOn();
void laneOff();


#endif /* INC_TRIGGER_H_ */
