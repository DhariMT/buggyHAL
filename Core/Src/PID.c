#include "PID.h"

#ifndef MAX_PWM
#define MAX_PWM 3000
#endif


void PIDController_Init(PIDController *pid) {

	/* Clear controller variables */

	pid->differentiator  = 0.0f;
	pid->integratorError = 0.0f;

	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;

	pid->limMax = MAX_PWM;
	pid->limMin = -MAX_PWM;
	pid->limMinInt = -MAX_PWM;
	pid->limMaxInt = MAX_PWM;

	pid->lastTime = HAL_GetTick();
	pid->prevInput = 0;
	pid->prevError = 0;


	pid->T = 0.01f;
	pid->out = 0.0;
}

void  PIDController_SetGain(PIDController *pid, double Kp, double Ki, double Kd) {

	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;

}


void  PIDController_SetLimits(PIDController *pid, int16_t outputMax, int16_t outputMin, int16_t IntegralMax , int16_t IntegralMin){

	pid->limMin = outputMin;
	pid->limMax = outputMax;

	pid->limMaxInt = IntegralMax;
	pid->limMinInt= IntegralMin;
}

int16_t PIDController_Update(PIDController *pid, int16_t setpoint, int16_t input) {

	/*
	* Error signal
	*/
	int16_t error = setpoint - input;


	/*
	* Proportional
	*/
    double proportional = pid->Kp * error;


	/*
	* Integral
	*/
    pid->integratorError += (error);

	/* Anti-wind-up via integrator clamping */
    if (pid->integratorError > INTEGRATOR_MAX) {

    	pid->integratorError = INTEGRATOR_MAX;

    } else if (pid->integratorError < -INTEGRATOR_MAX) {

    	pid->integratorError = -INTEGRATOR_MAX;

    }

    double integrator =  pid->Ki * pid->T * pid->integratorError;




	/*
	* Derivative (band-limited differentiator)
	*/

    pid->differentiator = (  pid->Kd * (error - pid->prevError)	) / (pid->T);


    pid->out = (int16_t)(proportional + integrator + pid->differentiator);

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store measurement for later use */
    pid->prevInput = input;
    pid->prevError = error;
	/* Store last time for state machine use */
    pid->lastTime = HAL_GetTick();

    // return PID output
    return pid->out;
}
