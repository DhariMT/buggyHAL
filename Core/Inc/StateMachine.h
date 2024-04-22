/*
 * StateMachine.h
 *
 *  Created on: Apr 19, 2024
 *      Author: Dhari
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_

#include "main.h"
#define S_NUM 4




typedef enum {RESET_StateMachine = 0 , IDLE = 1, TUNE = 2, CONSTANT_SPEED = 3 } states;

states StateMachine(states Current_State);

typedef void (* const voidFunc)(void);



void State_Enter_RESET(void); void State_Enter_IDLE(void); void State_Enter_CONSTANT_SPEED(void); void State_Enter_TUNE(void);

void State_InState_RESET(void); void State_InState_IDLE(void); void State_InState_CONSTANT_SPEED(void); void State_InState_TUNE(void);

void State_Exit_RESET(void); void State_Exit_IDLE(void); void State_Exit_CONSTANT_SPEED(void); void State_Exit_TUNE(void);



#endif /* INC_STATEMACHINE_H_ */
