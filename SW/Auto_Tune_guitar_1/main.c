#include "config_bits.h"
#include <p33EP256MU806.h>
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"
#include "user.h"
#include "Leds.h"
#include "Buttons.h"
#include "ADC.h"

extern StepMotor *StepperMotorList[];
extern Led *LedList[];
extern Button *BtnList[];
extern uint32_t Result; 
extern uint8_t ResultFlag;
extern uint16_t TonesAdcPeriods[];
extern uint8_t MeasureDemand;
    
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
    
    
    //ResultFlag =0;
    while (1)
    {
        if(MotorSelected)
        {
            if (ResultFlag) 
            {
                int32_t diffA = Result-TonesAdcPeriods[mot];
                if (diffA<0)
                {
                    diffA = TonesAdcPeriods[mot]-Result;
                }

                int32_t diffB = (Result*2)-TonesAdcPeriods[mot];
                if (diffB<0)
                {
                    diffB = TonesAdcPeriods[mot]-(Result*2);
                }
                if (diffA>diffB)
                {                
                    Result*=2;
                }

                if(Result==(TonesAdcPeriods[mot])) 
                {                    
                    ResultFlag=0;
                    MeasureDemand = 0;
                    InverseLeds();
                    MotorSelected = 0;   
                }
                else if(Result<TonesAdcPeriods[mot])
                {                
                    MotorsWake();
                    int i;
                    for (i = 0; i < 100; i++) 
                    {
                        DoStep(mot, Back);        
                        myNewDelay();
                    }
                    MotorsSleep();
                    ResultFlag=0;
                }
                else if(Result>TonesAdcPeriods[mot])
                {                            
                    MotorsWake();
                    int i;
                    for (i = 0; i < 100; i++) 
                    {
                        DoStep(mot, Forward);        
                        myNewDelay();
                    }
                    MotorsSleep();
                    ResultFlag=0;
                }
            }
            else if(BtnClick(eBtn2))
            {
                InverseLeds();
                MotorSelected = 0;    
                MeasureDemand = 0;                         
                ResultFlag=0;
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
                MeasureDemand = 1;
                ResultFlag = 0;
            } 
        }        
    }
    return 0;
}
