#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"

extern StepMotor *StepperMotorList[];

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
void InitMotorsAndLeds()
{
    int i;
    for (i = 0; i < eStepperMotorNum; i++) 
    {
        StepMotorCoil *xcoil = (StepMotorCoil*)(StepperMotorList[i]->CoilA);
        *(xcoil->Tris) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Ansel) &= ~(0b11 << xcoil->FirstPin);
        
        xcoil = (StepMotorCoil*)(StepperMotorList[i]->CoilB);
        *(xcoil->Tris) &= ~(0b11 << xcoil->FirstPin);
        *(xcoil->Ansel) &= ~(3 << xcoil->FirstPin);
        
        StepMotorLed *xled = (StepMotorLed*)(StepperMotorList[i]->Led);
        *(xled->Tris) &= ~(1 << xled->LedPin);
        *(xled->Ansel) &= ~(1 << xled->LedPin);   
    }
}
