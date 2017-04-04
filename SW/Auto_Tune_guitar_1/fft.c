#include <xc.h>
#include <stdint.h>
#include <dsp.h>
#include "fft.h"

fractcomplex sigCmpx[FFT_BLOCK_LENGTH]
__attribute__ ((eds, space(ymemory), aligned (FFT_BLOCK_LENGTH * 2 *2)));	
 
fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));

void InitFFT()
{
    TwidFactorInit(LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);             
}
void CalculateFFT(int inputValues[], fractional outputValues[FFT_BLOCK_LENGTH/2])
{
    int i;
    for ( i = 0; i < FFT_BLOCK_LENGTH; i++ )
    {				
        //sigCmpx[i].real = (inputValues[i] - ADC_MIDDLE);		
        sigCmpx[i].imag = 0;
        if (sigCmpx[i].real < (ADC_MIN_FOR_MULTIPLY)) 
        {
            sigCmpx[i].real = INT16_MIN;
        }
        else if (sigCmpx[i].real > (ADC_MAX_FOR_MULTIPLY)) 
        {
            sigCmpx[i].real = INT16_MAX;
        }
        else
        {
            sigCmpx[i].real *= ADC_MULTIPLIER_IDEAL;
        }
    }
    
    FFTComplexIP(LOG2_BLOCK_LENGTH, &sigCmpx[0], &twiddleFactors[0], COEFFS_IN_DATA);
    BitReverseComplex (LOG2_BLOCK_LENGTH, &sigCmpx[0]);
    SquareMagnitudeCplx(FFT_BLOCK_LENGTH/2, &sigCmpx[0], outputValues);
    
}
int CalculateFreq(fractional outputFFT[FFT_BLOCK_LENGTH/2])
{
    int i;
    for (i = 1; i < FFT_BLOCK_LENGTH/2; i++) 
    {
        if (outputFFT[i]>10) 
        {
            return i;
        }


    }

    return 0;
}