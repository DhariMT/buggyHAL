#include "StateMachine.h"
#include "main.h"
#include "tim.h"
#include "Motors.h"
#include "PID.h"
#include "Encoder.h"

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

double Kp, Ki, Kd;

int16_t LEFT, RIGHT, IntegralMax, IntegralMin, outputMin, outputMax;

PIDController PID_Speed;





states StateMachine(states Current_State)
{
    states Next_State = Current_State;

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
    		//Next_State = CONSTANT_SPEED;
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

	resetEncoder();
	resetFilter();

	PIDController_SetLimits(0, 0, 0, 0, 0);


	Kp = 0;
	Ki = 0;
	Kd = 0;


	LEFT = 0;
	RIGHT = 0;


	MOTORS_Reset();
	MOTORS_Disable();

	HAL_Delay(1);

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
HAL_Delay(1);
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
	MOTORS_Disable();

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

	if (Kp != PID_Speed.Kp || Ki != PID_Speed.Ki || Kd != PID_Speed.Kd) {

		HAL_TIM_Base_Stop_IT(&htim3);

		PIDController_Init(&PID_Speed, SAMPLE_TIME);
		PIDController_SetGain(&PID_Speed, Kp, Ki, Kd);
 }
	HAL_TIM_Base_Start_IT(&htim3);

}





void State_InState_CONSTANT_SPEED(void) {

//	 uint16_t currentTime;
//	 uint16_t timeChange;
//
//	 currentTime = HAL_GetTick();
//	 timeChange = currentTime - PID_Speed.lastTime;
//	 if ( timeChange >= 100 ) {
//		PID_Speed.Kp = Kp;
//		PID_Speed.Ki = Ki;
//		PID_Speed.Kd = Kd;
//	    //int32_t PID_Out;
//	    PIDController_Update(&PID_Speed, 500, myFilterLeft.filteredVelocity);
////	 MOTOR_LEFT_SetPWM(PID_Out);
//
//	 }

	//MOTOR_LEFT_SetPWM(LEFT);
	//HAL_Delay(1);


}


void State_Exit_RESET(void)
{
	//HAL_Delay(1);
}

void State_Exit_IDLE(void)
{
	MOTORS_Reset();
	//HAL_Delay(1);
	//MOTORS_Enable();
}

void State_Exit_TUNE(void)
{
	HAL_GPIO_WritePin(GPIOA, LD2_Pin, 0);
}

void State_Exit_CONSTANT_SPEED(void)
{
	//HAL_TIM_Base_Stop_IT(&htim3);
//	HAL_GPIO_WritePin(GPIOA, LD2_Pin, 0);
	HAL_Delay(1);
}



//////////////////////// Peripheral Interrupts/Callbacks

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == Button_Pin) {
		button_pushed = true;

	}
//	else if (states != RESET_StateMachine) {
//
//	}
}

int16_t outputVel;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{


	  updateEncoder(SAMPLE_TIME);
	  computeFilter(&myFilterLeft, leftWheel.velocity);
	  outputVel = PIDController_Update(&PID_Speed, LEFT, myFilterLeft.filteredVelocity);
	  MOTOR_LEFT_SetPWM(outputVel);
}
