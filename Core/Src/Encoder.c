/*
 * Encoder.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Dhari
 */

#include "Encoder.h"

encoder_instance rightWheel, leftWheel;

void resetEncoder(encoder_instance* wheel_encoder) {
	wheel_encoder->position = 0;
	wheel_encoder->velocity = 0;
	wheel_encoder->last_position = 0;
}

void updateEncoder(encoder_instance* wheel_encoder, TIM_HandleTypeDef* htim, const uint16_t sampleRate) { // samplRate in ms
	wheel_encoder->position = __HAL_TIM_GET_COUNTER(htim);
	wheel_encoder->velocity = (wheel_encoder->position - wheel_encoder->last_position)*1000/sampleRate;
	wheel_encoder->last_position = wheel_encoder->position;
}
