 /* motors.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Dhari
 */

#include "main.h"
#include "tim.h"

#include "Motors.h"


#define MAX_PWM 3000
#define UNIPOLAR 0
#define BIPOLAR 1
#define FORWARD 1
#define BACKWARD 0


void MOTORS_Reset(void) {

	HAL_GPIO_WritePin(directionRight_GPIO_Port, directionRight_Pin, FORWARD);
	HAL_GPIO_WritePin(directionLeft_GPIO_Port, directionLeft_Pin, FORWARD);

	HAL_GPIO_WritePin(unipolarLeft_GPIO_Port, unipolarLeft_Pin, UNIPOLAR);
	HAL_GPIO_WritePin(unipolarRight_GPIO_Port, unipolarLeft_Pin, UNIPOLAR);

	MOTOR_LEFT_SetPWM(0);
	MOTOR_RIGHT_SetPWM(0);
}

void MOTOR_LEFT_SetPWM(const int16_t PWM) {


	if (PWM > MAX_PWM) {
		return;
	}

	if (PWM < -MAX_PWM) {
		return;
	}

	int16_t _PWM;

	if (PWM >= 0) {
		HAL_GPIO_WritePin(directionLeft_GPIO_Port, directionLeft_Pin, FORWARD); // Sets direction forward assuming unipolar
		_PWM = (MAX_PWM - PWM);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _PWM);
	}
	else {
		HAL_GPIO_WritePin(directionLeft_GPIO_Port, directionLeft_Pin, BACKWARD);  // Sets direction forward assuming unipolar
		_PWM = (MAX_PWM + PWM);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, _PWM);
	}

}

void MOTOR_RIGHT_SetPWM(const int16_t PWM) {


	if (PWM > MAX_PWM) {
		return;
	}

	if (PWM < -MAX_PWM) {
		return;
	}

	int16_t _PWM;

	if (_PWM >= 0) {
		HAL_GPIO_WritePin(directionRight_GPIO_Port, directionRight_Pin, FORWARD);// Sets direction forward assuming unipolar
		_PWM = (MAX_PWM - PWM);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _PWM);
	}

	else {
		HAL_GPIO_WritePin(directionRight_GPIO_Port, directionRight_Pin, BACKWARD);// Sets direction forward assuming unipolar
		_PWM = (MAX_PWM + PWM);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, _PWM);
	}



}





void MOTORS_Enable(void) {
	 HAL_GPIO_WritePin(MotorsEnable_GPIO_Port, MotorsEnable_Pin, 1);
}

void MOTORS_Disable(void) {
	 HAL_GPIO_WritePin(MotorsEnable_GPIO_Port, MotorsEnable_Pin, 0);
}
