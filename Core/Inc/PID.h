#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "main.h"

#define INTEGRATOR_MAX 1000000

typedef struct {

	/* Controller gains */
	double Kp;
	double Ki;
	double Kd;


	/* Output limits */
	int16_t limMin;
	int16_t limMax;

	/* Integrator limits */
	int16_t limMinInt;
	int16_t limMaxInt;

	/* Sample time (in seconds) */
	double T;

	/* Controller "memory" */
	double integratorError;
	double differentiator;
	int16_t prevInput;
	int16_t prevError;

	uint8_t lastTime;

	/* Controller output */
	int16_t out;

} PIDController;

void  PIDController_Init(PIDController *pid);
void  PIDController_SetGain(PIDController *pid, double Kp, double Ki, double Kd);
void  PIDController_SetLimits(PIDController *pid, int16_t outputMin, int16_t outputMax, int16_t IntegralMin, int16_t IntegralMax);
int16_t  PIDController_Update(PIDController *pid, int16_t setpoint, int16_t input);

#endif
