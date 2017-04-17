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
extern GuitarString strings[7];
extern uint8_t DesiredSampleRate;
extern double FFT_MaxFreq;
fractional OutputValues[FFT_BLOCK_LENGTH/2] = {0};
uint8_t MotorSelected = 0;
StepMotorIndex mot = 0;
LedIndex led = 0;
    
void myNewDelay()
{   
    uint16_t k = 0;
    while (k<500)
    {
        k++;
    }
}
int main(void) 
{     
    InitApp();    
    MotorsWake();    
    MeasurementStart = 0;
    
    while (1)
    {
        if (MeasurementStart == 2)
        {
            CalculateFFT(DataForFFT, OutputValues);
            double truePeakFreq = CalculateFreq(OutputValues, strings[mot].Freq);        
            if (truePeakFreq>0)
            {                       
                double distunning = strings[mot].Freq - truePeakFreq;
                
                if (distunning > 10 || distunning < -10)
                {
                    MeasurementStart = 1;
                }
                else if ((distunning < (0.3)) && (distunning > (-0.3)))
                {
                    TurnLedOn(eLed1);
                    MeasurementStart = 0;
                }
                else if (distunning < 0)
                {                
                    MotorsWake();
                    int steps = -1* strings[mot].StepsCoef * distunning;
                    int i;
                    for (i = 0; i < steps; i++)
                    {
                        DoStep(mot, Back);
                        myNewDelay();
                    }
                    MotorsSleep();
                    MeasurementStart = 1;
                }
                else
                {
                    MotorsWake();
                    int steps =  strings[mot].StepsCoef * distunning;
                    int i;
                    for (i = 0; i < steps; i++) 
                    {
                        DoStep(mot, Forward);
                        myNewDelay();
                    }
                    MotorsSleep();
                    
                    MeasurementStart = 1;
                }
            }
            else if(!BtnOpen(BtnList[eBtn2]))
            {
                InverseLeds();
                MeasureDemand = 0;        
                MeasurementStart = 0;  
            }
            else
            {
                MeasurementStart = 1;
            }
        }
        else if(MeasurementStart==0)
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
                mot = (StepMotorIndex)led;
                MeasureDemand = 1;
                MeasurementStart = 1;
                DesiredSampleRate = strings[led].ADC_SampleRate;
                FFT_MaxFreq = strings[led].ADC_SampleRateHz;
            } 
            /*
            if (BtnClick(eBtn1))
            {
                if (MeasurementStart)
                {
                    TurnLedOn(eLed1);
                    MeasurementStart = 0;
                } 
                else
                {
                    TurnLedOff(eLed1);
                    MeasurementStart = 1;
                }
            }    */   
        }
    }
    return 0;
}
