#include "PID.h"

#ifndef MAX_PWM
#define MAX_PWM 3000
#endif


#define INTEGRATOR_MAX 2000000
#define ADC_MAX 4095
#define POSITION_SAMPLE_TIME 0.1 // sec
#define SPEED_SAMPLE_TIME 0.01 // sec



void PIDSpeed_Init(PID_Type1 *pid) {

	/* Clear controller variables */

	pid->differentiator  = 0.0f;
	pid->integratorError = 0.0f;

	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;


//	pid->lastTime = HAL_GetTick();
	pid->prevInput = 0;
	pid->prevError = 0;


	pid->out = 0.0;
}

void  PIDSpeed_SetGain(PID_Type1 *pid, double Kp, double Ki, double Kd) {

	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;

}


//void  PIDSpeed_SetLimits(PID_Type1 *pid, int16_t outputMax, int16_t outputMin, int16_t IntegralMax , int16_t IntegralMin){
//
//	pid->limMin = outputMin;
//	pid->limMax = outputMax;
//
//}

int16_t PIDSpeed_Update(PID_Type1 *pid, int16_t setpoint, int16_t input) {


	int16_t error = setpoint - input;



    double proportional = pid->Kp * error;



    pid->integratorError += (error);

	// Limit integration part to avoid system saturation // anti-wind coupling
    if (pid->integratorError > INTEGRATOR_MAX) {

    	pid->integratorError = INTEGRATOR_MAX;

    } else if (pid->integratorError < -INTEGRATOR_MAX) {

    	pid->integratorError = -INTEGRATOR_MAX;

    }

    double integrator =  pid->Ki * SPEED_SAMPLE_TIME * pid->integratorError;




    pid->differentiator = (  pid->Kd * (error - pid->prevError)	) / SPEED_SAMPLE_TIME;


    pid->out = (int16_t)(proportional + integrator + pid->differentiator);

    if (pid->out > MAX_PWM) {

        pid->out = MAX_PWM;

    } else if (pid->out < -MAX_PWM) {

        pid->out = -MAX_PWM;

    }

	// Store measurement for integral and derivative action
    pid->prevInput = input;
    pid->prevError = error;
	// Store time stamp for state machine use
    //pid->lastTime = HAL_GetTick();


    return pid->out;
}

void PIDPosition_Init(PID_Type2 *pid, double _Kp) {

	pid->Kp = _Kp;

}
int16_t PIDPosition_Update(PID_Type2 *pid, int16_t setpoint, int16_t input) {

	int16_t error = setpoint - input;

    pid->out = pid->Kp * error;
    return pid->out;
}

