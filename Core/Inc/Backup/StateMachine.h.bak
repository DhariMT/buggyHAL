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



/*
 * Defining an enum that contains all states in the order they are placed in the LUT (Look Up table).
 */
typedef enum {RESET_StateMachine = 0,  IDLE = 1, FOLLOW_LINE = 2, TUNEPID_LEFT = 3, TUNEPID_RIGHT = 4, TUNEPID_POSITION = 5} states;
states StateMachine(states Current_State); // declare state machine function which will contain or organize the main body of this program

typedef void (* const voidFunc)(void);


/* ENTER */
void State_Enter_RESET(void); void State_Enter_IDLE(void); void State_Enter_LINE_FOLLOW(void);
void State_Enter_TUNEPID_LEFT(void); void State_Enter_TUNEPID_RIGHT(void); void State_Enter_TUNEPID_POSITION(void);

/* InState */
void State_InState_RESET(void); void State_InState_IDLE(void); void State_InState_LINE_FOLLOW(void);
void State_InState_TUNEPID_LEFT(void); void State_InState_TUNEPID_RIGHT(void); void State_InState_TUNEPID_POSITION(void);

/* Exit */
void State_Exit_RESET(void); void State_Exit_IDLE(void); void State_Exit_LINE_FOLLOWD(void); void State_Exit_TUNEPID_LEFT(void);
void State_Exit_TUNEPID_RIGHT(void); void State_Exit_TUNEPID_POSITION(void);



#endif /* INC_STATEMACHINE_H_ */
