#include "config_bits.h"
#include <p33EP256MU806.h>
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"
#include "user.h"
#include "Leds.h"
#include "Buttons.h"

extern StepMotor *StepperMotorList[];
extern Led *LedList[];
    
void myNewDelay()
{   
    uint16_t k = 0;
    while (k<1000)
    {
        k++;
    }
}
int main(void) 
{
    InitApp();    
    MotorsWake();
    
    while (1) 
    {
        int i;
        for (i = 0; i < eStepperMotorNum; i++)
        {
            DoStep(i, Back);
            *(LedList[i]->Port) ^= (1<<(LedList[i]->LedPin));
            myNewDelay();
        }
    }
    return 0;
}
