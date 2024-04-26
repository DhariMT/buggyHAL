#include "StateMachine.h"
#include "main.h"
#include "tim.h"
#include "Motors.h"
#include "PID.h"
#include "Encoder.h"

#define KP 6
#define KI 4
#define KD 3

#define SET_SPEED 300

#define MAX_PWM 3000
#define SAMPLE_TIME 10 //milliseconds
/*
 * flags are of type uint8_t
 * List of all flags is:
 *
 *
 */

voidFunc UponEnter[S_NUM] =   {State_Enter_RESET, State_Enter_IDLE,  State_Enter_TUNE,  State_Enter_CONSTANT_SPEED};
voidFunc ActionWhileInState[S_NUM] = {State_InState_RESET, State_InState_IDLE, State_InState_TUNE, State_InState_CONSTANT_SPEED};
voidFunc  UponExit[S_NUM] =           {State_Exit_RESET,  State_Exit_IDLE, State_Exit_TUNE , State_Exit_CONSTANT_SPEED};

states button_pushed;

double KpLeft, KiLeft, KdLeft, KpRight, KiRight, KdRight;

int16_t LEFT, RIGHT;






states StateMachine(states Current_State)
{
	static states Next_State = Current_State;

    /*
     * Main variables, declared as
     */
    static PIDController PIDleft_Speed, PIDright_Speed;
    static uint16_t * mySensor;
    switch ( Current_State )
    {

    	/* State IDLE START */

    case RESET_StateMachine:
    	Next_State = IDLE;
    	break;
    case IDLE:
    	if (button_pushed) {
    	Next_State = TUNE;
    	}
    	/* State IDLE END */
           break;
    case TUNE:
    	if (button_pushed) {
    		Next_State = IDLE;
    	}
    	break;

    case CONSTANT_SPEED:
    	if (button_pushed) {
    		Next_State = IDLE;
    	}
    	break;
    	/* State SPIN_TIRES START */

           // The program should never arrive here
       default:
           break;
    }

    if (Next_State != Current_State)
    {
        // Function call for Upon Exit function, it can be omitted but allows extra functionality
        UponExit[Current_State]();
        // Function call for Upon Enter function, it can be omitted but allows extra functionality
        UponEnter[Next_State]();
    }
    else // ActionWhileInState is only be called when NOT doing a transition
     {
        ActionWhileInState[Current_State]();
    }
    return Next_State;
}





void State_Enter_RESET() {



}

void State_Enter_IDLE(void)
{
	button_pushed = false;
	MOTORS_Disable();
}

void State_Enter_TUNE(void)
{

button_pushed = false;

//
HAL_GPIO_WritePin(GPIOA, LD2_Pin, 1);

HAL_TIM_Base_Stop_IT(&htim3);

PIDController_Init(&PIDleft_Speed);
PIDController_SetGain(&PIDleft_Speed, KP, KI, KD);


PIDController_Init(&PIDright_Speed);
PIDController_SetGain(&PIDright_Speed, KP, KI, KD);

HAL_TIM_Base_Start_IT(&htim3);

//PIDController_Init(&PID_Speed, SAMPLE_TIME);
//PIDController_SetLimits(&PID_Speed, outputMin, outputMax, IntegralMin, IntegralMax);
//PID_Speed.Kp = Kp;
//PID_Speed.Ki = Ki;
//PID_Speed.Kd = Kd;
//
//MOTORS_Enable();
}
void State_Enter_CONSTANT_SPEED(void)

{
	button_pushed = false;
	//MOTORS_Disable();

//	button_pushed = false;
//
//
//	MOTORS_Enable();


}


void State_InState_RESET(void)
{
	//HAL_Delay(1);
}

void State_InState_IDLE(void)
{
	//HAL_Delay(1);
}

void State_InState_TUNE(void)
{

//	if (KpLeft != PIDleft_Speed.Kp || KiLeft != PIDleft_Speed.Ki || KdLeft != PIDleft_Speed.Kd) {
//
//		HAL_TIM_Base_Stop_IT(&htim3);
//
//		MOTOR_LEFT_SetPWM(0);
//		PIDController_Init(&PIDleft_Speed);
//		PIDController_SetGain(&PIDleft_Speed, KpLeft, KiLeft, KdLeft);
//
//		HAL_TIM_Base_Start_IT(&htim3);
// }
//
//	if (KpRight != PIDright_Speed.Kp || KiRight != PIDright_Speed.Ki || KdRight != PIDright_Speed.Kd) {
//
//		HAL_TIM_Base_Stop_IT(&htim3);
//
//
//		MOTOR_RIGHT_SetPWM(0);
//		PIDController_Init(&PIDright_Speed);
//
//		PIDController_SetGain(&PIDright_Speed, KpRight, KiRight, KdRight);
//		HAL_TIM_Base_Start_IT(&htim3);
// }

}





void State_InState_CONSTANT_SPEED(void) {


}


void State_Exit_RESET(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);
	resetEncoder();
	resetFilter();


	PIDController_Init(&PIDleft_Speed);
	PIDController_Init(&PIDright_Speed);


	KpLeft = 0;
	KiLeft = 0;
	KdLeft = 0;

	KpRight = 0;
	KiRight = 0;
	KdRight = 0;

	LEFT = 0;
	RIGHT = 0;


	MOTORS_Reset();
	HAL_TIM_Base_Start_IT(&htim3);
}

void State_Exit_IDLE(void)
{
	MOTORS_Enable();
}

void State_Exit_TUNE(void)
{

	HAL_GPIO_WritePin(GPIOA, LD2_Pin, 0);

}

void State_Exit_CONSTANT_SPEED(void)
{
}



//////////////////////// Peripheral Interrupts/Callbacks

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == Button_Pin) {
		button_pushed = true;

	}

}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	  // Updating encoder velocities and declare required PID outputs
	  int16_t outputLeft, outputRight;
	  updateEncoder(SAMPLE_TIME);

	  // apply a simple FIR filter before adding input to speed PID
	  computeFilter(&myFilterLeft, leftWheel.velocity);
	  outputLeft = PIDController_Update(&PIDleft_Speed, SET_SPEED, myFilterLeft.filteredVelocity);
	  MOTOR_LEFT_SetPWM(outputLeft);

	  computeFilter(&myFilterRight, rightWheel.velocity);
	  outputRight = PIDController_Update(&PIDright_Speed, SET_SPEED, myFilterRight.filteredVelocity);
	  MOTOR_RIGHT_SetPWM(outputRight);




}
