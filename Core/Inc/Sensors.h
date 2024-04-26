/*
 * sensors.h
 *
 *  Created on: Apr 13, 2024
 *      Author: Dhari
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#define MAX_SENSORS 5

/*
 *
 *
 *
 * */

extern uint16_t ReadingADC[MAX_SENSORS];

void startSensors();
void calibrateSensor(uint16_t *mySensor);
void removeSensorsAmbiance(uint16_t *mySensor);


#endif /* INC_SENSORS_H_ */
