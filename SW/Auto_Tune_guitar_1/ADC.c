#include <stdint.h>
#include <p33EP256MU806.h>
#include "xc.h"
#include "Strings_freq.h"
#include "ADC.h"
#include "Leds.h"
#include "fft.h"

#define COMP_HIGH_LIMIT (2050)
#define COMP_LOW_LIMIT (2035)
#define MOV_AVR_BR_DIV (2)
#define SUC_MES_BR_DIV (4)
#define MOVING_AVERAGE_FIELD_SIZE (1<<(MOV_AVR_BR_DIV))
#define SUCCESFULL_MEASUREMENT_FIELD_SIZE (1<<(SUC_MES_BR_DIV))
#define SAMPLES_TO_INTERRUPT (16)

int DataForFftCounter = 0;
uint8_t DesiredSampleRate = 125;
uint8_t MeasurementStart = 0;
extern fractcomplex sigCmpx[FFT_BLOCK_LENGTH];

//init ADC1 and ADC2
void InitAdc()
{
    initAdcPiezo();
    initAdcBattery();
}
//init ADC2
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
// init ADC1
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
    //AD1CON3bits.ADCS = 250;
    AD1CON3bits.ADCS = 125;
    
    AD1CON4bits.ADDMAEN = 0;
    
    AD1CHS0bits.CH0SA = 0;
    AD1CHS0bits.CH0SB = 0;
    AD1CHS0bits.CH0NA = 0;
    AD1CHS0bits.CH0NB = 0;
    
    AD1CSSH = 0;
    AD1CSSL = 0;
    
    IEC0bits.AD1IE=1;
}
//pointers to 16 adc samples
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

//ADC1 finish conversion interrupt 
void __attribute__ ((interrupt, auto_psv)) _AD1Interrupt(void)
{       
    if (MeasurementStart == 1)
    {
        if (AD1CON3bits.ADCS != DesiredSampleRate) // if new sample rate
        {            
            AD1CON3bits.ADCS = DesiredSampleRate;
        }
        else
        {            
            int i;
            for (i = 0; i < SAMPLES_TO_INTERRUPT; i++) // loop through all 16 samples 
            {
                sigCmpx[DataForFftCounter].real = (*(ADC_buffer[i])) - ADC_MIDDLE; // save sample
                DataForFftCounter++;
                if (DataForFftCounter == FFT_BLOCK_LENGTH) // all 1024 samplpes saved
                {
                    DataForFftCounter = 0;
                    MeasurementStart = 2; //flag for main loop to start fft
                }
            }
        }
    }
    IFS0bits.AD1IF = 0;        //Clear the interrupt flag
}