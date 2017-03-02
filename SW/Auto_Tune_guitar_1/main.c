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
    while (k<220)
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
            int j;
            for (j = 0; j < 3000; j++) 
            {          
                DoStep(i, Back);
                myNewDelay();
            }
            
            for (j = 0; j < 3000; j++) 
            {          
                DoStep(i, Forward);
                myNewDelay();
            }
            MotorOff(i);
        }        
    }
    return 0;
}
