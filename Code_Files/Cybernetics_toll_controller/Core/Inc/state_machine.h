#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include "main.h"
#include "sensors.h"
#include "commands.h"
#include "stdbool.h"

#define Mukhterpur 1
#define Kalna 0
// **System States**
typedef enum {
    STATE_IDLE,
    STATE_PAYMENT,
    STATE_WAIT_CAR,
    STATE_FLEET,
    STATE_PANIC,
    STATE_CLOSE,
    STATE_COUNT
} State_t;

typedef enum {
    EVT_CAR_DETECTED,
    EVT_PAYMENT_COMPLETED,
    //EVT_FORCE_PAYMENT,
    EVT_FORCE_OPEN,
    EVT_FORCE_CLOSE,
    EVT_CAR_PASSED,
    //EVT_DETECTION_FAIL,
    EVT_SIREN_OFF,
    EVT_SYSTEM_RESET,
    EVT_ACTIVATE_SIREN,
	EVT_IR_CHECK,
	EVT_CAMERA_TRIGGER,
	EVT_RX_TEST,
    EVT_UNKNOWN
} Event_t;


State_t handle_idle(Event_t evt);
State_t handle_payment(Event_t evt);
State_t handle_wait_car(Event_t evt);
State_t handle_fleet(Event_t evt);
State_t handle_panic(Event_t evt);
State_t handle_close(Event_t evt);


extern volatile bool First_command;
void run_state_machine(State_t* current_state, Event_t event);
Event_t generate_event(SensorSystem_t *sensorSystem, uint8_t cmdID, State_t Current_State);

const char* state_to_str(State_t state);

extern State_t currentState;

void connectionFeedback(void);
void check_and_execute(uint8_t cmdID, State_t Current_State);
void printState(const char* message);

#endif /* INC_STATE_MACHINE_H_ */
