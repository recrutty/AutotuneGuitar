#ifndef FFT_H
#define	FFT_H
#include <dsp.h>
#define ADC_MIDDLE (2043)
#define ADC_MULTIPLIER_IDEAL_BV (7)
#define ADC_MULTIPLIER_IDEAL (1 << (ADC_MULTIPLIER_IDEAL_BV))
#define LOG2_BLOCK_LENGTH     (11)                                  
#define FFT_BLOCK_LENGTH   ((1) << (LOG2_BLOCK_LENGTH))
#define SAMPLING_RATE        (10000)  

void InitFFT();
void CalculateFFT(int inputValues[FFT_BLOCK_LENGTH], fractional outputValues[FFT_BLOCK_LENGTH/2]);
#endif	/* FFT_H */

