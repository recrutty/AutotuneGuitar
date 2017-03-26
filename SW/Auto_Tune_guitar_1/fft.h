#ifndef FFT_H
#define	FFT_H
#include <dsp.h>
#define ADC_MIDDLE (2043)
#define LOG2_BLOCK_LENGTH     (11)    /* = Number of "Butterfly" Stages in FFT processing */
#define FFT_BLOCK_LENGTH   ((1) << (LOG2_BLOCK_LENGTH)) // 512     /* = Number of frequency points in the FFT */
#define SAMPLING_RATE        (10000)    /* = Rate at which input signal was sampled */
                                        /* SAMPLING_RATE is used to calculate the frequency*/
                                        /* of the largest element in the FFT output vector*/
void InitFFT();
void CalculateFFT(int inputValues[FFT_BLOCK_LENGTH], fractional outputValues[FFT_BLOCK_LENGTH/2]);
#endif	/* FFT_H */

