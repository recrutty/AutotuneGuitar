#include "config_bits.h"
#include <p33EP256MU806.h>
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"
#include "user.h"
extern StepMotor *StepperMotorList[];

    StepMotorLed *xled;
    
void myNewDelay()
{   
    uint16_t k = 0;
    while (k<65000)
    {
        k++;
    }
}
int main(void) 
{
    //InitApp();
    
    int i;
    for (i = 0; i < eStepperMotorNum; i++) 
    {        
        xled = (StepMotorLed*)(StepperMotorList[i]->Led);
        *(xled->Tris) &= ~(1 << xled->LedPin);
        *(xled->Ansel) &= ~(1 << xled->LedPin);
        *(xled->Port) |= (1 << xled->LedPin);
    }
    
    *(SW1_DIR) |= (1 << SW1_PIN);
    *(SW1_PULLUP) |= (1 << SW1_PIN);
    *(SW1_ANSEL) &= ~(1 << SW1_PIN);
    
    *(SW2_DIR) |= (1 << SW2_PIN);
    *(SW2_PULLUP) |= (1 << SW2_PIN);
    *(SW2_ANSEL) &= ~(1 << SW2_PIN);
    
    *(SW3_DIR) |= (1 << SW3_PIN);
    *(SW3_PULLUP) |= (1 << SW3_PIN);
    *(SW3_ANSEL) &= ~(1 << SW3_PIN);
    
    while (1) 
    {
        xled = (StepMotorLed*)(StepperMotorList[6]->Led);
        if (((*(SW1_PORT))&(1 << SW1_PIN))==0) 
        {
            
            *(xled->Port) |= (1 << xled->LedPin);
        } 
        else
        {
            
            *(xled->Port) &= ~(1 << xled->LedPin);
        }
        
        xled = (StepMotorLed*)(StepperMotorList[5]->Led);
        if (((*(SW2_PORT))&(1 << SW2_PIN))==0) 
        {
            
            *(xled->Port) |= (1 << xled->LedPin);
        } 
        else
        {
            
            *(xled->Port) &= ~(1 << xled->LedPin);
        }
        
        xled = (StepMotorLed*)(StepperMotorList[4]->Led);
        if (((*(SW3_PORT))&(1 << SW3_PIN))==0) 
        {
            
            *(xled->Port) |= (1 << xled->LedPin);
        } 
        else
        {
            
            *(xled->Port) &= ~(1 << xled->LedPin);
        }
        /*
        xled = (StepMotorLed*)(StepperMotorList[0]->Led);
        *(xled->Port) |= (1 << xled->LedPin);

        xled = (StepMotorLed*)(StepperMotorList[6]->Led);
        *(xled->Port) &= ~(1 << xled->LedPin);
            myNewDelay();
        int j;
        for (j = 0; j < 7; j++) 
        {
            xled = (StepMotorLed*)(StepperMotorList[j]->Led);
            *(xled->Port) ^= (1 << xled->LedPin);
            
            xled = (StepMotorLed*)(StepperMotorList[j-1]->Led);
            *(xled->Port) &= ~(1 << xled->LedPin);
            myNewDelay();
        }    */
        
        
    }

    return 0;
}
