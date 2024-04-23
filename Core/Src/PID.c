#include "PID.h"



void PIDController_Init(PIDController *pid, uint8_t samplingPeriod_ms) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError  = 0.0;

	pid->differentiator  = 0.0f;
	pid->prevInput = 0.0;

	pid->out = 0.0;

//	pid->limMax = 0;
//	pid->limMin = 0;
//	pid->limMinInt = 0;
//	pid->limMaxInt = 0;

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

    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }


	/*
	* Derivative (band-limited differentiator)
	*/

//    pid->differentiator = -(2.0f * pid->Kd * (input - pid->prevInput)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
//                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
//                        / (2.0f * pid->tau + pid->T);


	/*
	* Compute output and apply limits
	*/
    pid->out = (int16_t)(proportional + pid->integrator + pid->differentiator);

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store error and measurement for later use */
    pid->prevError       = error;
    pid->prevInput = input;

    pid->lastTime = HAL_GetTick();
    return pid->out;
}
