#include "PID.h"

#ifndef MAX_PWM
#define MAX_PWM 3000
#endif


void PIDController_Init(PIDController *pid, uint8_t samplingPeriod_ms) {

	/* Clear controller variables */

	pid->differentiator  = 0.0f;
	pid->prevInput = 0.0;

	pid->out = 0.0;

	pid->limMax = MAX_PWM;
	pid->limMin = -MAX_PWM;
	pid->limMinInt = -MAX_PWM;
	pid->limMaxInt = MAX_PWM;

	pid->lastTime = HAL_GetTick();
	pid->T = samplingPeriod_ms / 1000;
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

//    pid->differentiator = -(2.0f * pid->Kd * (input - pid->prevInput)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
//                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
//                        / (2.0f * pid->tau + pid->T);


    pid->out = (int16_t)(proportional + integrator + pid->differentiator);

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store measurement for later use */
    pid->prevInput = input;
	/* Store last time for state machine use */
    pid->lastTime = HAL_GetTick();

    // return PID output
    return pid->out;
}
