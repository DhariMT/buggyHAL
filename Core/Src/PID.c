#include "PID.h"

#ifndef MAX_PWM
#define MAX_PWM 3000
#endif


#define INTEGRATOR_MAX 2000000
#define ADC_MAX 4095
#define POSITION_SAMPLE_TIME 0.1
#define SPEED_SAMPLE_TIME 0.01

void PIDSpeed_Init(PID_Type1 *pid) {

	/* Clear controller variables */

	pid->differentiator  = 0.0f;
	pid->integratorError = 0.0f;

	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;


	pid->lastTime = HAL_GetTick();
	pid->prevInput = 0;
	pid->prevError = 0;


	pid->T = SPEED_SAMPLE_TIME;
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
//	pid->limMaxInt = IntegralMax;
//	pid->limMinInt= IntegralMin;
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

    double integrator =  pid->Ki * pid->T * pid->integratorError;




    pid->differentiator = (  pid->Kd * (error - pid->prevError)	) / (pid->T);


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
    pid->lastTime = HAL_GetTick();


    return pid->out;
}
/*
void PIDLineSensor_Init(PID_Type2 *pid, double _Kp, double _Ki, double _Kd, uint8_t _N) {
	pid->Kp = _Kp;

	pid-> Ki = _Ki;    //          integral gain

	pid->Kd = _Kd;   //          derivative          gain

	pid->N = _N;             //          filter coefficients

	pid->T = POSITION_SAMPLE_TIME;       // This     must match      actual sampling time PID

	//                    controller is running

	//                    -- the following coefficients must be recomputed if

	//                    --- any parameter above is changed by user

	double a0 = (1+ (pid->N*pid->Ts));
	double a1 = -(2 + pid->N*pid->Ts);
	double a2 = 1;

	double b0 = pid->Kp*(1+pid->N*pid->T) +pid->pid->Ki*pid->Ts*(1+pid->N*pid->T) + pid->Kd*pid->N;
	double b1 = -(pid->Kp*(2+pid->N*pid->T) +pid-> pid-> Ki*pid->T + 2*Kd*pid->N);
	double b2 = pid->Kp + pid->Kd*pid->N;

	ku1 = a1/a0; ku2 = a2/a0; ke0 = b0/a0; ke1 = b1/a0; ke2 = b2/a0;
}

int16_t PIDLineSensor_Compute(PID_Type1 *pid, int16_t setpoint, int16_t input) {


	e2=e1; e1=e0; u2=u1;
	u1=u0; // update variables

	positionOutput = read();           // read    plant output

	e0 = positionInput - positionOutput;           // compute new error

	positionOutput = -ku1*u1 – ku2*u2 + ke0*e0 + ke1*e1 + ke2*e2; // eq (12)

	if (positionOutput > UMAX) positionOutput  = UMAX;  // limit to DAC or PWM range

	if (U0     <            UMIN) u0           = UMIN;

	return positionOutput;
}


double e2, e1, e0, u2, u1, u0;                    // variables used in PID_Type1 computation

double positionInput;         // command

double positionOutput;        // plant output

//                    -- these parameters should be user-adjustable double Kp = 10; // proportional gain



void pid(void) { // implement this as timer interrupt service routine {

e2=e1; e1=e0; u2=u1;       u1=u0; // update variables

positionOutput = read();           // read    plant output

e0 = positionInput – positionOutput;           // compute new error

u0 = -ku1*u1 – ku2*u2 + ke0*e0 + ke1*e1 + ke2*e2; // eq (12)

if (u0     >            UMAX) u0          = UMAX;  // limit to DAC or PWM range

if (U0     <            UMIN) u0           = UMIN;

return u0;

}
*/
