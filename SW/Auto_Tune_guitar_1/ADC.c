#include <stdint.h>

#include "xc.h"
#include "ADC.h"
#include "Leds.h"

#define FIELD_SIZE 1000
uint16_t A[FIELD_SIZE];
int ADCdebugDataCounter = 0;

void InitAdc()
{
    initAdcPiezo();
    initAdcBattery();
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
#define COMP_HIGH_LIMIT 2050
#define COMP_LOW_LIMIT 2035
uint8_t compMem=0;
uint16_t AdcSamplesCounter = 0;
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
            A[ADCdebugDataCounter] = AdcSamplesCounter;
            ADCdebugDataCounter++;
            AdcSamplesCounter = 0;
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