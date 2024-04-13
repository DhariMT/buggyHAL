/*
 * Encoder.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Dhari
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "tim.h"
#include "main.h"

typedef struct {
	int32_t position;
	int16_t velocity;
	int32_t last_position;
} encoder_instance;

extern encoder_instance rightWheel, leftWheel;

void resetEncoder(encoder_instance* wheel_encoder);
void updateEncoder(encoder_instance* wheel_encoder, TIM_HandleTypeDef* htim, const uint16_t sampleRate);


#endif /* INC_ENCODER_H_ */
