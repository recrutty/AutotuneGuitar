#include "stepper_motors.h"
#include "Leds.h"
#include "Buttons.h"
#include "user.h"
#include "ADC.h"
#include "fft.h"

void InitApp()
{
    //InitPllOsc();
    InitAdc();
    InitMotors();
    InitBtns();
    InitLeds();    
    InitFFT();
}
void InitPllOsc() 
{
    PLLFBD=42; // M=48
    CLKDIVbits.PLLPOST=0; // N2=2
    CLKDIVbits.PLLPRE=0; // N1=2
           
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC!= 0b011);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK!= 1);
}