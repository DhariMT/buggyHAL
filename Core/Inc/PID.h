#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "main.h"

#define INTEGRATOR_MAX 2000000

typedef struct {

	/* Controller gains */
	double Kp;
	double Ki;
	double Kd;

//	/* Output limits */
//	int16_t limMin;
//	int16_t limMax;

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

} PID_Type1;

typedef struct {

	/* Controller gains */
	double Kp;
	double Ki;
	double Kd;

	/* Controller parameters */
	uint8_t N;

	/*    */
	double a0;
	double a1;
	double a2;
	/*    */
	double b0;
	double b1;
	double b2;
	/*    */
	double ku1;

	/* Sample time (in seconds) */
	double T;

	/* Controller "memory" */



	/* Controller output */
	int16_t out;

} PID_Type2;


void  PIDSpeed_Init(PID_Type1 *pid);
void  PIDSpeed_SetGain(PID_Type1 *pid, double Kp, double Ki, double Kd);
void  PIDSpeed_SetLimits(PID_Type1 *pid, int16_t outputMin, int16_t outputMax);
int16_t  PIDSpeed_Update(PID_Type1 *pid, int16_t setpoint, int16_t input);

#endif
