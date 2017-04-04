#include "config_bits.h"
#include <p33EP256MU806.h>
#include "dsp.h"
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"
#include "user.h"
#include "Leds.h"
#include "Buttons.h"
#include "ADC.h"
#include "fft.h"

extern StepMotor *StepperMotorList[];
extern Led *LedList[];
extern Button *BtnList[];
extern uint32_t Result; 
extern uint8_t ResultFlag;
extern uint16_t TonesAdcPeriods[];
extern uint8_t MeasureDemand;
extern uint8_t MeasurementStart;
extern int DataForFFT[FFT_BLOCK_LENGTH];
fractional OutputValues[FFT_BLOCK_LENGTH/2] = {0};
uint8_t MotorSelected = 0;
StepMotorIndex mot = 0;
LedIndex led = 0;   
    
void myNewDelay()
{   
    uint16_t k = 0;
    while (k<5000)
    {
        k++;
    }
}
int main(void) 
{     
    InitApp();    
    MotorsWake();    
    /*
    fractional kuk = 50;
    fractional bum = 5;
    fractional kar = 0;
    int karel = __builtin_divmodsd(kuk, bum, &kar);*/
    MeasurementStart = 0;
    
    
    
    while (1)
    {
        if (MeasurementStart == 2)
        {
            CalculateFFT(DataForFFT, OutputValues);
            MeasurementStart = 0;
        }
        if (BtnClick(eBtn1))
        {
           MeasurementStart = 1;
        }    
               
    }
    return 0;
}
