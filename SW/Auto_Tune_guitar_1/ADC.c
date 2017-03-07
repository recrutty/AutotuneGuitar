#include <stdint.h>

#include "xc.h"
#include "Strings_freq.h"
#include "ADC.h"
#include "Leds.h"

#define FIELD_SIZE 1000
uint16_t A[FIELD_SIZE];
int ADCdebugDataCounter = 0;


#define COMP_HIGH_LIMIT (2050)
#define COMP_LOW_LIMIT (2035)
#define MOV_AVR_BR_DIV (2)
#define MOVING_AVERAGE_FIELD_SIZE (1<<(MOV_AVR_BR_DIV))
uint16_t MovingAverage[MOVING_AVERAGE_FIELD_SIZE] = {0};
uint64_t MovingAverageSummary = 0;
uint8_t MovingAverageCounter = 0;
uint8_t compMem=0;
uint16_t AdcSamplesCounter = 0;

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
    AD1CON2bits.SMPI = 0b00000;
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
uint32_t TonesAdcPeriods[7];
void countFrequencyTable(uint16_t ConcertPitchA)
{    
    long double A1_ADC_Per = (double)((ADC_SAMPLE_RATE * MOVING_AVERAGE_FIELD_SIZE)/((double)(ConcertPitchA)));
    TonesAdcPeriods[6] = (int)(A1_ADC_Per * SEMITONE_3_MULTIPLIER + 0.5);
    TonesAdcPeriods[5] = (int)(A1_ADC_Per * SEMITONE_8_MULTIPLIER + 0.5);
    TonesAdcPeriods[4] = (int)(A1_ADC_Per * SEMITONE_2_MULTIPLIER * 2 + 0.5);
    TonesAdcPeriods[3] = (int)(A1_ADC_Per * SEMITONE_7_MULTIPLIER * 2 + 0.5);
    TonesAdcPeriods[2] = (int)(A1_ADC_Per * 4 + 0.5);
    TonesAdcPeriods[1] = (int)(A1_ADC_Per * SEMITONE_5_MULTIPLIER * 4 + 0.5);
    TonesAdcPeriods[0] = (int)(A1_ADC_Per * SEMITONE_10_MULTIPLIER * 4 + 0.5);
}

void __attribute__ ((interrupt, auto_psv)) _AD1Interrupt(void)
{   
    *(STEP_POW_PORT) |= 1 << STEP_POW_BIT;    
    
    AdcSamplesCounter++;
    switch(compMem) 
    {
    case 0 :        
        if(ADC1BUF0 > COMP_HIGH_LIMIT)
        {
            compMem = 1;            
            
            MovingAverageSummary += AdcSamplesCounter;
            MovingAverageSummary -= MovingAverage[MovingAverageCounter];            
            
            A[ADCdebugDataCounter] = AdcSamplesCounter;
            ADCdebugDataCounter++;
            AdcSamplesCounter = 0;
            
            MovingAverageCounter++;
            MovingAverageCounter &= ~(1 << MOV_AVR_BR_DIV); //reset to 0 if in max value
        }
        break;
        
    case 1 :        
        if(ADC1BUF0 < COMP_LOW_LIMIT)
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
    A[ADCdebugDataCounter] = ADC1BUF0;
    ADCdebugDataCounter++;
    if (ADCdebugDataCounter == FIELD_SIZE)
    {
        ADCdebugDataCounter = 0;
    }
    */
    
    
    IFS0bits.AD1IF = 0;        //Clear the interrupt flag
    *(STEP_POW_PORT) &= ~(1 << STEP_POW_BIT);
}