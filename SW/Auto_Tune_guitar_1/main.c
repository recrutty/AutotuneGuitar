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
    while (k<2000)
    {
        k++;
    }
}
int main(void) 
{
    InitApp();
    
    MotorsWake();
    StepMotor *xmotor;
    int iled = 0;
    while (1) 
    {
        /*
        int i;
        for (i = 0; i < eStepperMotorNum; i++) 
        {

            xmotor = StepperMotorList[i];
            *(xmotor->CoilA->Port) ^= (0b10 << (xmotor->CoilA->FirstPin)); 
    
        }
        myNewDelay();
        TurnLedOn(iled);
        for (i = 0; i < eStepperMotorNum; i++) 
        {
            xmotor = StepperMotorList[i];
            *(xmotor->CoilB->Port) ^= (0b10 << (xmotor->CoilB->FirstPin)); 
        
        }
        myNewDelay();
        TurnLedOff(iled);
        iled++;
        if (iled==eLedNum) 
        {
            iled=0;
        }

        PORTB = 0b0000000000001000;
        myNewDelay();
        PORTB = 0b0000000000001010;
        myNewDelay();
        PORTB = 0b0000000000000010;
        myNewDelay();
        PORTB = 0b0000000000011010; 
        myNewDelay();       
        PORTB = 0b0000000000011100;
        myNewDelay();
        PORTB = 0b0000000000011110;
        myNewDelay();
        PORTB = 0b0000000000000110;
        myNewDelay();
        PORTB = 0b0000000000001110;
        myNewDelay();
         */   
        PORTB = 0b0001000000000100;
        myNewDelay();
        PORTB = 0b0001000000010100;
        myNewDelay();
        PORTB = 0b0001000000010000;
        myNewDelay();
        PORTB = 0b0001000000010010; 
        myNewDelay();           
        PORTB = 0b0001000000000010;
        myNewDelay();
        PORTB = 0b0001000000001010;
        myNewDelay();
        PORTB = 0b0001000000001000;
        myNewDelay();
        PORTB = 0b0001000000001100; 
        myNewDelay();    
    }
    return 0;
}
