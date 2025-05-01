/*
 * sensors.h
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_
#include "main.h"




//#define DEBOUNCE_DELAY 500
// Enum for Sensor Types
typedef enum {
    ENTRYLOOP_COIL,
    EXITLOOP_COIL,
    IR_SENSOR,
	TCU_BOX_STATUS
} SensorType_t;

// Enum for Sensor States
typedef enum {
    SENSOR_INACTIVE = 0,
    SENSOR_ACTIVE = 1
} SensorState_t;

// Structure for a Single Sensor
typedef struct {
    SensorType_t sensorType;  // Type of sensor
    SensorState_t state;      // Current state (ACTIVE/INACTIVE)
    SensorState_t prev_state; // Previous state (ACTIVE/INACTIVE)
    uint32_t lastTriggered;   // Timestamp of last activation (optional)
} SensorData_t;

// Structure for All Sensors
typedef struct {
    SensorData_t entryloopCoil;
    SensorData_t exitloopCoil;
    SensorData_t irSensor;
    SensorData_t tcubox;
} SensorSystem_t;


//// Global Sensor System Instance
extern SensorSystem_t sensorSystem;
//void disable_interrupts();
//void enable_interrupts();


// Function Prototype
void updateSensorState(SensorType_t sensorType, SensorSystem_t *sensors, SensorState_t state)  ;
void updatePrevSensorState(SensorSystem_t *sensors);
void pollSensors(void);

void entryloopcoil_handler(void);
void exitloopcoil_handler(void);
void ir_handler(void);
void tcubox_handler(void);
#endif /* INC_SENSORS_H_ */
