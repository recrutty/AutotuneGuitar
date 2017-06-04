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

extern StepMotor *StepperMotorList[]; //List of step motors
extern Led *LedList[]; //List of Leds
extern Button *BtnList[];//List of Buttons
extern uint8_t MeasurementStart; //main loop can set this to start measurement
extern GuitarString strings[7]; //List of strings
extern uint8_t DesiredSampleRate; //sample rate can be set. will be changet on next adc conversion
extern double FFT_MaxFreq; //FFT maximum frequency can be set for calculations
fractional OutputValues[FFT_BLOCK_LENGTH/2] = {0}; //data from FFT is stored there
StepMotorIndex mot = 0; //number of selected motor
LedIndex led = 0; //number of selected led
void StepMotorDelay(); //delay for right step motor turning

int main(void)
{     
    InitApp();
    MotorsWake();
    MeasurementStart = 0;
    
    while (1)
    {
        if (MeasurementStart == 2) //flag if there is data from adc
        {
            CalculateFFT(OutputValues);
            double truePeakFreq = CalculateFreq(OutputValues, strings[mot].Freq);        
            
            if (truePeakFreq > 0) //if string freq was found
            {                       
                double distunning = strings[mot].Freq - truePeakFreq; //difference between ref freq and measured freq
                
                if (distunning > 10 || distunning < -10) //differende too big
                {
                    MeasurementStart = 1; //measure again
                }
                else if ((distunning < (0.3)) && (distunning > (-0.3))) //differende is small enough
                {
                    InverseLeds();
                    MeasurementStart = 0; // tunning finished
                }
                else if (distunning < 0) //meassured freq is bigger than ref freq
                {     
                    //do steps
                    MotorsWake();
                    int steps = -1* strings[mot].StepsCoef * distunning;
                    int i;
                    for (i = 0; i < steps; i++)
                    {
                        DoStep(mot, Back);
                        StepMotorDelay();
                    }
                    MotorsSleep();
                    MeasurementStart = 1;
                }
                else //meassured freq is smaller than ref freq
                {
                    //do steps
                    MotorsWake();
                    int steps =  strings[mot].StepsCoef * distunning;
                    int i;
                    for (i = 0; i < steps; i++) 
                    {
                        DoStep(mot, Forward);
                        StepMotorDelay();
                    }
                    MotorsSleep();
                    
                    MeasurementStart = 1;
                }
            }
            else if(!BtnOpen(BtnList[eBtn2])) //stop tunning demand
            {
                InverseLeds();       
                MeasurementStart = 0;  
            }
            else
            {
                MeasurementStart = 1;
            }
        }
        else if(MeasurementStart==0) //idle state
        {
            //button actions, string selection
            if (BtnClick(eBtn1) && (led > eLed1)) 
            {
                led--;
            }    
            if (BtnClick(eBtn3) && (led < eLed7)) 
            {
                led++;
            }            
            OneLedOn(led);
            if(BtnClick(eBtn2)) //user wand to tude
            {   
                InverseLeds();
                mot = (StepMotorIndex)led;
                MeasurementStart = 1;
                DesiredSampleRate = strings[led].ADC_SampleRate;
                FFT_MaxFreq = strings[led].ADC_SampleRateHz;
            }  
        }
    }
    return 0;
}

void StepMotorDelay()
{   
    uint16_t k = 0;
    while (k<500)
    {
        k++;
    }
}