#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include "main.h"

#define INTEGRATOR_MAX 2000000

/* 		Speed controller		*/
typedef struct {

	/* Controller gains */
	double Kp;
	double Ki;
	double Kd;

	/* Controller "memory" */
	double integratorError;
	double differentiator;
	int16_t prevInput;
	int16_t prevError;


	/* Controller output */
	int16_t out;

} PID_Type1;

/* 		declaring speed controllers methods		*/
void  PIDSpeed_Init(PID_Type1 *pid);
void  PIDSpeed_SetGain(PID_Type1 *pid, double Kp, double Ki, double Kd);
void  PIDSpeed_SetLimits(PID_Type1 *pid, int16_t outputMin, int16_t outputMax);
int16_t  PIDSpeed_Update(PID_Type1 *pid, int16_t setpoint, int16_t input);



/* 		Line Position simple Proportional controller		*/
typedef struct {

	double Kp;
	int16_t out;

}PID_Type2;

/* 		declaring position controllers methods		*/
void PIDPosition_Init(PID_Type2 *pid, double _Kp);
int16_t PIDPosition_Update(PID_Type2 *pid, int16_t setpoint, int16_t input);


#endif
