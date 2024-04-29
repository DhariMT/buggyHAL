/*
 * sensors.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Dhari
 */
#define MAX_SENSOR 4095
#define SENSORS_NUM 5
#include "Sensors.h"

uint16_t uncalibratedSensor[SENSORS_NUM];
uint16_t mySensor[SENSORS_NUM];

void startSensors() {
	  HAL_ADC_Start_DMA(&hadc1,mySensor, SENSORS_NUM);
}

void stopSensors() {
	  HAL_ADC_Stop_DMA(&hadc1);
}

uint16_t linePosition() {
	uint16_t sensorSum = 0;
	uint16_t sensorWeightedSum = 0;
	for (uint8_t sensorNumber = 0; sensorNumber < SENSORS_NUM; sensorNumber++) {
		sensorSum += mySensor[sensorNumber];
		sensorWeightedSum += (mySensor[SENSORS_NUM - sensorNumber] - mySensor[sensorNumber]);
	}
	return sensorSum/5;
}

//void removeSensorsAmbiance(uint16_t *mySensor) {
//
//	for (int i = 1; i < 4; i++) {
//		mySensor[i] = ReadingADC[i];
//		HAL_GPIO_TogglePin(Darl2_GPIO_Port, Darl2_Pin);
//		mySensor[i] -= ReadingADC[i];
//	}
//
//}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
//// empty for now
//
//}

