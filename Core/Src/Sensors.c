/*
 * sensors.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Dhari
 */


#include "Sensors.h"

uint16_t ReadingADC[MAX_SENSORS];

void startSensors() {
	  HAL_ADC_Start_DMA(&hadc1,ReadingADC, 5);
}
void calibrateSensor(uint16_t *mySensor) {

	mySensor[1] = MAX_SENSOR - mySensor->left;

	/* the center sensor should map to same value. you could do ------> mySensor[2] = mySensor->mySensor[2] but pointless; */

	mySensor[3] = MAX_SENSOR + mySensor[3];

}


void removeSensorsAmbiance(uint16_t *mySensor) {

	for (int i = 1; i < 4; i++) {
		mySensor[i] = ReadingADC[i];
		HAL_GPIO_TogglePin(GPIO_Darl2_Port, Darl2_Pin);
		mySensor[i] -= ReadingADC[i];
	}

}

