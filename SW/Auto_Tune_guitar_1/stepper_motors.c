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

void DoSteps(uint8_t motorNum, uint16_t stepsNum)
{
    StepperMotorList[motorNum]->LastState.RemainingSteps = stepsNum;
}

void DoStep(uint8_t motorNum)
{
    StepMotor *mot = (StepMotor*)(StepperMotorList[motorNum]);

    if (mot->LastState.RemainingSteps != 0) 
    {
        StepMotorCoil *xcoil;
        if (mot->LastState.ChangeDirection == 1) {
            mot->LastState.LastCoil ^= 1;
            mot->LastState.ChangeDirection = 0;
        }

        if (mot->LastState.LastCoil == 1) {
            xcoil = (StepMotorCoil*) (mot->CoilA);
        } else {
            xcoil = (StepMotorCoil*) (mot->CoilB);
        }
        *(xcoil->Port) ^= (0b11 << xcoil->FirstPin);
        mot->LastState.RemainingSteps--;
    }
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
