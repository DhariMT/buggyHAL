#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "main.h"
typedef struct {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	int16_t limMin;
	int16_t limMax;

	/* Integrator limits */
	int16_t limMinInt;
	int16_t limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	int16_t prevError;			/* Required for integrator */
	float differentiator;
	int16_t prevInput;		/* Required for differentiator */

	uint8_t lastTime;

	/* Controller output */
	int16_t out;

} PIDController;

void  PIDController_Init(PIDController *pid, uint8_t samplingPeriod_ms);
void  PIDController_SetGain(PIDController *pid, double Kp, double Ki, double Kd);
void  PIDController_SetLimits(PIDController *pid, int16_t outputMin, int16_t outputMax, int16_t IntegralMin, int16_t IntegralMax);
int16_t  PIDController_Update(PIDController *pid, int16_t setpoint, int16_t input);

#endif
