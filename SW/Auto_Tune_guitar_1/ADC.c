#include <stdint.h>

#include "xc.h"
#include "Strings_freq.h"
#include "ADC.h"
#include "Leds.h"


#define FIELD_SIZE 500
uint32_t A[FIELD_SIZE];
int ADCdebugDataCounter = 0;


#define COMP_HIGH_LIMIT (2050)
#define COMP_LOW_LIMIT (2035)
#define MOV_AVR_BR_DIV (4)
#define SUC_MES_BR_DIV (4)
#define MOVING_AVERAGE_FIELD_SIZE (1<<(MOV_AVR_BR_DIV))
#define SUCCESFULL_MEASUREMENT_FIELD_SIZE (1<<(SUC_MES_BR_DIV))
#define SAMPLES_TO_INTERRUPT (16)

uint16_t MovingAverage[MOVING_AVERAGE_FIELD_SIZE] = {0};
uint32_t SuccesfullMeasurement[SUCCESFULL_MEASUREMENT_FIELD_SIZE];// = {2047};
uint32_t MovingAverageSummary = 0;
uint8_t SucMesCounter = 0;
uint8_t MovingAverageCounter = 0;
uint8_t compMem=0;
uint16_t AdcSamplesCounter = 0;
uint32_t Result = 0;
uint8_t ResultFlag = 0;
uint8_t MeasureDemand = 0;

void InitAdc()
{
    initAdcPiezo();
    initAdcBattery();
    countFrequencyTable(440);
}
void initAdcBattery()
{
    ANSELBbits.ANSB6 = 1;
    
    AD2CON1bits.ADON = 1;
    AD2CON1bits.ADSIDL = 0;
    AD2CON1bits.FORM = 0;
    AD2CON1bits.SSRC = 0;
    AD2CON1bits.SSRCG = 0;
    AD2CON1bits.SIMSAM = 0;
    AD2CON1bits.ASAM = 0;
    
    AD2CON2bits.VCFG = 0;
    AD2CON2bits.CSCNA = 0;
    AD2CON2bits.CHPS = 0;
    AD2CON2bits.BUFM = 0;
    AD2CON2bits.ALTS = 0;
    
    AD2CON3bits.ADRC = 0;
    AD2CON3bits.ADCS = 0;
            
    AD2CON4bits.ADDMAEN = 0;
    AD2CHS0bits.CH0SA = 6;
    AD2CHS0bits.CH0SB = 6;
    AD2CHS0bits.CH0NA = 0;
    AD2CHS0bits.CH0NB = 0;
}

void initAdcPiezo()
{
    ANSELBbits.ANSB0 = 1;
    TRISBbits.TRISB0 = 1;
    
    AD1CON1bits.ADON = 1;
    AD1CON1bits.ADSIDL = 0;
    AD1CON1bits.AD12B = 1;
    AD1CON1bits.FORM = 0;
    AD1CON1bits.SSRCG = 0;
    AD1CON1bits.SSRC = 0b111;
    AD1CON1bits.ASAM = 1;
    
    AD1CON2bits.VCFG = 0;
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = SAMPLES_TO_INTERRUPT - 1;
    AD1CON2bits.BUFM = 0;
    AD1CON2bits.ALTS = 0;
    
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 0;
    AD1CON3bits.ADCS = 10;
    
    AD1CON4bits.ADDMAEN = 0;
    
    AD1CHS0bits.CH0SA = 0;
    AD1CHS0bits.CH0SB = 0;
    AD1CHS0bits.CH0NA = 0;
    AD1CHS0bits.CH0NB = 0;
    
    AD1CSSH = 0;
    AD1CSSL = 0;
    
    IEC0bits.AD1IE=1;
}
uint16_t TonesAdcPeriods[7];
void countFrequencyTable(uint16_t ConcertPitchA)
{    
    long double A1_ADC_Per = (double)((ADC_SAMPLE_RATE * MOVING_AVERAGE_FIELD_SIZE)/((double)(ConcertPitchA)));
    TonesAdcPeriods[6] = (uint16_t)(A1_ADC_Per * SEMITONE_5_MULTIPLIER + 0.5);
    TonesAdcPeriods[5] = (uint16_t)(A1_ADC_Per * SEMITONE_10_MULTIPLIER + 0.5);
    TonesAdcPeriods[4] = (uint16_t)(A1_ADC_Per * SEMITONE_2_MULTIPLIER * 2 + 0.5);
    TonesAdcPeriods[3] = (uint16_t)(A1_ADC_Per * SEMITONE_7_MULTIPLIER * 2 + 0.5);
    TonesAdcPeriods[2] = (uint16_t)(A1_ADC_Per * 4 + 0.5);
    TonesAdcPeriods[1] = (uint16_t)(A1_ADC_Per * SEMITONE_5_MULTIPLIER * 4 + 0.5);
    TonesAdcPeriods[0] = (uint16_t)(A1_ADC_Per * SEMITONE_10_MULTIPLIER * 4 + 0.5);
}
#define BUF0 ((ADC1BUF0))
volatile const uint16_t *ADC_buffer[] = {
&ADC1BUF0,
&ADC1BUF1,
&ADC1BUF2,
&ADC1BUF3,
&ADC1BUF4,
&ADC1BUF5,
&ADC1BUF6,
&ADC1BUF7,
&ADC1BUF8,
&ADC1BUF9,
&ADC1BUFA,
&ADC1BUFB,
&ADC1BUFC,
&ADC1BUFD,
&ADC1BUFE,
&ADC1BUFF
};

void __attribute__ ((interrupt, auto_psv)) _AD1Interrupt(void)
{   
    //*(STEP_POW_PORT) |= 1 << STEP_POW_BIT;
    if (MeasureDemand)
    {
        *(STEP_POW_PORT) |= 1 << STEP_POW_BIT;
        int i;
        for (i = 0; i < SAMPLES_TO_INTERRUPT; i++)
        {
            AdcSamplesCounter++;
            switch(compMem) 
            {
            case 0 :        
                if(*(ADC_buffer[i]) > COMP_HIGH_LIMIT)
                {   
                    compMem = 1;            

                    MovingAverageSummary += AdcSamplesCounter;
                    MovingAverageSummary -= MovingAverage[MovingAverageCounter];

                    A[ADCdebugDataCounter] = (MovingAverageSummary);
                    ADCdebugDataCounter++;

                    MovingAverage[MovingAverageCounter] = AdcSamplesCounter;
                    MovingAverageCounter++;
                    MovingAverageCounter &= ~(1 << MOV_AVR_BR_DIV); //reset to 0 if in max value
                    AdcSamplesCounter = 0;

                    SuccesfullMeasurement[SucMesCounter] = MovingAverageSummary;
                    SucMesCounter++;            
                    SucMesCounter &= ~(1 << SUC_MES_BR_DIV); //reset to 0 if in max value
                    if (ResultFlag ==0)
                    {
                        uint32_t min=0xffff;
                        uint32_t max=0;
                        int j;
                        for (j = 0; j < SUCCESFULL_MEASUREMENT_FIELD_SIZE; j++) 
                        {
                            if(SuccesfullMeasurement[j]>max)
                            {
                                max=SuccesfullMeasurement[j];
                            }
                            if(SuccesfullMeasurement[j]<min)
                            {
                                min=SuccesfullMeasurement[j];
                            }
                        }
                        if ((max-min)<30) 
                        {
                            int k;
                            Result=0;
                            for (k = 0; k < SUCCESFULL_MEASUREMENT_FIELD_SIZE; k++) 
                            {
                                Result += SuccesfullMeasurement[k];
                            }
                            
                            Result >>= SUC_MES_BR_DIV;

                            A[ADCdebugDataCounter-1]=0;
                            ResultFlag = 1;
                        }
                    }
                }
                break;

            case 1 :        
                if(*(ADC_buffer[i]) < COMP_LOW_LIMIT)
                {
                    compMem = 0;
                }            
                break;
            default:        
                compMem = 0;
                break;
            }
            
            switch(ADCdebugDataCounter) 
            {
            case FIELD_SIZE :
                ADCdebugDataCounter=0;
                break;
            }

                /*
            A[ADCdebugDataCounter] = (*(ADC_buffer[i]));
            ADCdebugDataCounter++;
            if (ADCdebugDataCounter == FIELD_SIZE)
            {
                ADCdebugDataCounter = 0;
            }
             */


        }
    }
    IFS0bits.AD1IF = 0;        //Clear the interrupt flag
    *(STEP_POW_PORT) &= ~(1 << STEP_POW_BIT);
}