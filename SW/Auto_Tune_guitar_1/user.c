#include "stepper_motors.h"
#include "Leds.h"
#include "Buttons.h"
#include "user.h"
#include "ADC.h"
#include "fft.h"

void InitApp()
{
    InitAdc();
    InitMotors();
    InitBtns();
    InitLeds();    
    InitFFT();
}