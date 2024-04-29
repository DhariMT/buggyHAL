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
 * List of all flags is as follows :
 *
 * ble_message
 * speed_sampled
 * button_pushed
 *
 *
 *
 *
 */

voidFunc UponEnter[S_NUM] =   {State_Enter_RESET, State_Enter_IDLE,  State_Enter_LINE_FOLLOW,  State_Enter_TUNEPID_LEFT, State_Enter_TUNEPID_RIGHT, State_Enter_TUNEPID_POSITION};
voidFunc ActionWhileInState[S_NUM] = {State_InState_RESET, State_InState_IDLE, State_InState_LINE_FOLLOW , State_InState_TUNEPID_LEFT, State_InState_TUNEPID_RIGHT, State_InState_TUNEPID_POSITION};
voidFunc  UponExit[S_NUM] =           {State_Exit_RESET,  State_Exit_IDLE, State_Exit_LINE_FOLLOW,  State_Exit_TUNEPID_LEFT, State_Exit_TUNEPID_RIGHT, State_Exit_TUNEPID_POSITION};


/*          BLE Events enum            */
typedef enum {
	STOP,
	TUNEPID_LEFT,
	TUNEPID_RIGHT,
	TUNEPID_POSITION,
	PRINT_TUNING_PARAMETERS,
	PRINT_SPEED,
	PRINT_POSITION
} ble;
/*                Events            */
uint8_t button_pushed, speed_sampled, reset_complete;
ble ble_message;

/*                GLOBAL VARIABLES            */
PID_Type1 PIDleft_Speed;
PID_Type1 PIDright_Speed;
PID_Type2 LineFollower;




states StateMachine(states Current_State)
{
	states Next_State = Current_State;

    /*
     * Main variables, declared as static
     */

    switch ( Current_State )
    {

    	/* State RESET_StateMachine START */
    case RESET_StateMachine:
    	if (reset_complete) {
    	Next_State = IDLE;
    	}
    	break;
    	/* State IDLE START */
    case IDLE:
    	if (button_pushed) {
    	Next_State = LINE_FOLLOW;
    	}
        break;
    case LINE_FOLLOW:
    	if (button_pushed) {
    		Next_State = TUNEPID_SPEED;
    	}
        /* State TUNEPID_SPEED START */
    case TUNEPID_SPEED:
    	if (button_pushed) {
    		Next_State = TUNEPID_POSITION;
    	}
    	break;
    	/* State TUNEPID_POSITION START*/
    case TUNEPID_POSITION:
    	if (button_pushed) {
    		Next_State = IDLE;
    	}
    	break;
    	/* END OF ALL POSSIBLE STATES */
           // The program should never arrive here
       default:
           break;
    }


    /*
     *
     *
     * BEGIN STATE LOOKUP TABLE
     *
     *
     */


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



/*
 *
 *
 *
 *
 *
 * State Enter Functions
 *
 *
 *
 *
 */

void State_Enter_RESET() {

	HAL_TIM_Base_Stop_IT(&htim3);
	resetEncoder();
	resetFilter();

	PIDSpeed_Init(&PIDleft_Speed);
	PIDSpeed_Init(&PIDright_Speed);

	MOTORS_Reset();
	HAL_TIM_Base_Start_IT(&htim3);

	reset_complete = true;
}

void State_Enter_IDLE(void)
{
	button_pushed = false;
	MOTORS_Disable();
	HAL_UART_Transmit_IT(&huart6, "IDLE STATE", 10);
}

void State_Enter_LINE_FOLLOWER(void)
{
	button_pushed = false;
	HAL_UART_Transmit_IT(&huart6, "LINE FOLLOWING STATE", 20);
}

uint8_t readingParas1[11];
// Begin Function Enter_TUNEPID_SPEED
void State_Enter_TUNEPID_SPEED(void)
{

button_pushed = false;
HAL_UART_Transmit_IT(&huart6, "SPEED TUNING STATE", 18);
HAL_UART_Receive_IT(&huart6, readingParas1, 11);

//
//HAL_TIM_Base_Stop_IT(&htim3);
//
//PIDSpeed_Init(&PIDleft_Speed);
//PIDSpeed_SetGain(&PIDleft_Speed, KP, KI, KD);
//
//
//PIDSpeed_Init(&PIDright_Speed);
//PIDSpeed_SetGain(&PIDright_Speed, KP, KI, KD);
//
//HAL_TIM_Base_Start_IT(&htim3);
}
// Function Enter_TUNEPID_SPEED ended

uint8_t readingParas2[4];
void State_Enter_TUNEPID_POSITION(void)
{
	button_pushed = false;
	HAL_UART_Transmit_IT(&huart6, "POSITION TUNING STATE", 21);
	HAL_UART_Receive_IT(&huart6, readingParas1, 4);
}

/*
 *
 *
 *
 *
 *
 * InState Functions
 *
 *
 *
 *
 */

void State_InState_RESET(void)
{

}

void State_InState_IDLE(void)
{

}

void State_InState_LINE_FOLLOWER(void)
{

}

void State_InState_TUNEPID_SPEED(void)
{

}


void State_InState_TUNEPID_POSOITION(void)
{

}






/*
 *
 *
 *
 *
 *
 * State Exit Functions
 *
 *
 *
 *
 */

void State_Exit_RESET(void)
{
	reset_complete = true;
}

void State_Exit_IDLE(void)
{
	MOTORS_Enable();
}

void State_Exit_LINE_FOLLOWER(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
}

void State_Exit_TUNEPID_SPEED(void)
{


}

void State_Exit_TUNEPID_POSOITION(void)
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
	  outputLeft = PIDSpeed_Update(&PIDleft_Speed, SET_SPEED, myFilterLeft.filteredVelocity);
	  MOTOR_LEFT_SetPWM(outputLeft);

	  computeFilter(&myFilterRight, rightWheel.velocity);
	  outputRight = PIDSpeed_Update(&PIDright_Speed, SET_SPEED, myFilterRight.filteredVelocity);
	  MOTOR_RIGHT_SetPWM(outputRight);




}
