/*
 * Encoder.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Dhari
 */

#include "Encoder.h"


encoder_instance rightWheel, leftWheel;
filter_instance myFilterLeft, myFilterRight;


void resetFilter() {

	myFilterLeft.iterator = 0;
	myFilterLeft.sum = 0;

	myFilterRight.iterator = 0;
	myFilterRight.sum = 0;

	for (int i = 0; i < FILTER_SIZE; i++){

		myFilterLeft.FILTER_ARRAY[i] = 0;

		myFilterRight.FILTER_ARRAY[i] = 0;

	}

}

void computeFilter(filter_instance* _myFilter, int16_t inputVelocity) {
	_myFilter->sum += inputVelocity - (_myFilter->FILTER_ARRAY[_myFilter->iterator]);
	_myFilter->FILTER_ARRAY[_myFilter->iterator] = inputVelocity;
	_myFilter->iterator++;

	if (_myFilter->iterator == FILTER_SIZE) {
		_myFilter->iterator = 0;
	}

	_myFilter->filteredVelocity = _myFilter->sum / FILTER_SIZE;

}

void resetEncoder() {

	leftWheel.position = 0;
	leftWheel.velocity = 0;
	leftWheel.last_position = 0;

	rightWheel.position = 0;
	rightWheel.velocity = 0;
	rightWheel.last_position = 0;

}

void updateEncoder(const uint8_t sampleRate) { // samplRate in ms

	leftWheel.position = __HAL_TIM_GET_COUNTER(&htim2);
	leftWheel.velocity = (leftWheel.position - leftWheel.last_position) * (1000 / sampleRate);
	leftWheel.last_position = leftWheel.position;

	rightWheel.position = __HAL_TIM_GET_COUNTER(&htim5);
	rightWheel.velocity = (rightWheel.position - rightWheel.last_position) * (1000 / sampleRate);
	rightWheel.last_position = rightWheel.position;
}


