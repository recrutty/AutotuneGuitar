#include <xc.h>
#include <stdint.h>
#include <dsp.h>
#include "fft.h"

fractcomplex sigCmpx[FFT_BLOCK_LENGTH]
__attribute__ ((eds, space(ymemory), aligned (FFT_BLOCK_LENGTH * 2 *2)));	
 
fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));

fractional input[FFT_BLOCK_LENGTH];
fractional output[FFT_BLOCK_LENGTH/2];

void InitFFT()
{
    TwidFactorInit(LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);             
}
void CalculateFFT(int inputValues[], fractional outputValues[FFT_BLOCK_LENGTH/2])
{
    int i;
    for ( i = 0; i < FFT_BLOCK_LENGTH; i++ )/* The FFT function requires input data */
    {					/* to be in the fractional fixed-point range [-0.5, +0.5]*/
            sigCmpx[i].real = (inputValues[i] - ADC_MIDDLE) ;		/* So, we shift all data samples by 1 bit to the right. */
            sigCmpx[i].imag = 0;                    /* Should you desire to optimize this process, perform  */
            if (sigCmpx[i].real<(-128)) 
            {
                sigCmpx[i].real = -32768;
            }
            else if (sigCmpx[i].real>(128)) 
            {
                sigCmpx[i].real = 32767;
            }
            else
            {                
                sigCmpx[i].real *= 128;
            }


    }
    FFTComplexIP(LOG2_BLOCK_LENGTH, &sigCmpx[0], &twiddleFactors[0], COEFFS_IN_DATA);
    BitReverseComplex (LOG2_BLOCK_LENGTH, &sigCmpx[0]);
    //sigCmpx[0].real = 0 ;
    /*for ( i = 0; i < FFT_BLOCK_LENGTH; i++ ) The FFT function requires input data
    {					
            sigCmpx[i].real = sigCmpx[i].real << 4 ;		
            sigCmpx[i].imag = sigCmpx[i].imag << 4;                 
    }*/
    SquareMagnitudeCplx(FFT_BLOCK_LENGTH/2, &sigCmpx[0], outputValues);
    
}