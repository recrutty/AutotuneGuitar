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
extern Button *BtnList[];
uint8_t MotorSelect = 0;
    
void myNewDelay()
{   
    uint16_t k = 0;
    while (k<300)
    {
        k++;
    }
}
int main(void) 
{ 
    InitApp();    
    MotorsWake();
    
    uint8_t MotorSelected = 0;
    StepMotorIndex mot = 0;
    LedIndex led = 0;
    while (1)
    {
        if(MotorSelected)
        {
            if(!BtnOpen(BtnList[eBtn1]))
            {                
                MotorsWake();
                DoStep(mot, Back);        
                myNewDelay();
            }
            else if(!BtnOpen(BtnList[eBtn3]))
            {
                MotorsWake();
                DoStep(mot, Forward);        
                myNewDelay();
            }
            else
            {
                MotorsSleep();
            }
                
            if(BtnClick(eBtn2))
            {
                InverseLeds();
                MotorSelected = 0;                
            } 
        }
        else
        {
            if (BtnClick(eBtn1) && (led > eLed1)) 
            {
                led--;
            }    
            if (BtnClick(eBtn3) && (led < eLed7)) 
            {
                led++;
            }   
            OneLedOn(led);
            if(BtnClick(eBtn2))
            {   
                InverseLeds();
                MotorSelected = 1;
                mot = (StepMotorIndex)led;
            } 
        }        
    }
    return 0;
}
