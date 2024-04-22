/*
 * Encoder.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Dhari
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#define FILTER_SIZE 128

#include "tim.h"


typedef struct {
	int32_t position;
	int16_t velocity;
	int32_t last_position;
} encoder_instance;

typedef struct {
	int16_t FILTER_ARRAY[FILTER_SIZE];
	uint8_t iterator;
	int32_t sum;
	int16_t filteredVelocity;
} filter_instance;

extern encoder_instance rightWheel, leftWheel;
extern filter_instance myFilterLeft, myFilterRight;

void resetFilter();
void computeFilter(filter_instance* _myFilter, int16_t inputVelocity);
void resetEncoder();
void updateEncoder(const uint8_t sampleRate);



#endif /* INC_ENCODER_H_ */

