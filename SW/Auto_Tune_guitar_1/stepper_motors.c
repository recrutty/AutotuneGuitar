#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"

extern StepMotor *StepperMotorList[];

void MotorsSleep()
{
    *STEP_WK_PORT &= ~(1 << STEP_WK_BIT);
}
void MotorsWake()
{    
    *STEP_WK_PORT |= (1 << STEP_WK_BIT);
}

void DoSteps(StepMotorIndex motorNum, StepMotorDirection dir, uint16_t stepsNum)
{
    StepperMotorList[motorNum]->LastState.RemainingSteps = stepsNum;
    StepperMotorList[motorNum]->LastState.Direction = dir;
}

void DoStep(StepMotorIndex motorNum, StepMotorDirection dir)
{
    int8_t *xstate = (int8_t*)&(StepperMotorList[motorNum]->LastState.RotationState);
    *xstate += dir;
    
    StepMotorCoil *xcoilA = (StepMotorCoil*)(StepperMotorList[motorNum]->CoilA);
    StepMotorCoil *xcoilB = (StepMotorCoil*)(StepperMotorList[motorNum]->CoilB);
    
    switch(*xstate) 
    {
    case -1 :
        *(xcoilB->Port) |= (0b10 << xcoilB->FirstPin);
        *xstate = 7;
        break;
	
    case 0 :        
        *(xcoilA->Port) &= ~(0b11 << xcoilA->FirstPin);
        break;
	
    case 1 :
        *(xcoilA->Port) |= (0b01 << xcoilA->FirstPin);
        break;
	
    case 2 :
        *(xcoilB->Port) &= ~(0b11 << xcoilB->FirstPin);
        break;
	
    case 3 :
        *(xcoilB->Port) |= (0b01 << xcoilB->FirstPin);
        break;	
	
    case 4 :
        *(xcoilA->Port) &= ~(0b11 << xcoilA->FirstPin);
        break;	
	
    case 5 :
        *(xcoilA->Port) |= (0b10 << xcoilA->FirstPin);
        break;	
	
    case 6 :
        *(xcoilB->Port) &= ~(0b11 << xcoilB->FirstPin);
        break;	
	
    case 7 :
        *(xcoilB->Port) |= (0b10 << xcoilB->FirstPin);
        break;
	
    case 8 :
        *(xcoilA->Port) &= ~(0b11 << xcoilA->FirstPin);
        *xstate = 0;
        break;
  
    default :
        *xstate = 0;
        break;
    }
    StepperMotorList[motorNum]->LastState.RemainingSteps--;
}
void InitMotors()
{
    int i;
    for (i = 0; i < eStepperMotorNum; i++) 
    {
        StepMotorCoil *xcoil = (StepMotorCoil*)(StepperMotorList[i]->CoilA);
        *(xcoil->Tris) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Ansel) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Port) ^= (1 << xcoil->FirstPin);
        
        xcoil = (StepMotorCoil*)(StepperMotorList[i]->CoilB);
        *(xcoil->Tris) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Ansel) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Port) ^= (1 << xcoil->FirstPin);
    }
    
    *STEP_WK_DIR &= ~(1 << STEP_WK_BIT);
    *STEP_WK_ANSEL &= ~(1 << STEP_WK_BIT);
}
