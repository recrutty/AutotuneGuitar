#ifndef FFT_H
#define	FFT_H
#include <dsp.h>
#include <stdint.h>

typedef struct
{
    volatile uint16_t Freq;
    volatile uint8_t HarmNum;
} FreqPeak;

typedef struct
{
    volatile double Freq;
    volatile int StepsCoef;
    volatile uint8_t ADC_SampleRate;    
    volatile double ADC_SampleRateHz;
} GuitarString;

#define ADC_MIDDLE (2043)
#define ADC_MULTIPLIER_IDEAL_BV (7)
#define ADC_MULTIPLIER_IDEAL (1 << (ADC_MULTIPLIER_IDEAL_BV))
#define ADC_MAX_FOR_MULTIPLY ((int)((INT16_MAX)/(ADC_MULTIPLIER_IDEAL)))
#define ADC_MIN_FOR_MULTIPLY ((int)((INT16_MIN)/(ADC_MULTIPLIER_IDEAL)))

#define LOG2_BLOCK_LENGTH     (11)                                  
#define FFT_BLOCK_LENGTH   ((1) << (LOG2_BLOCK_LENGTH))            
#define FFT_LAST_ELEMENT   (((FFT_BLOCK_LENGTH) >> (1))-(1)) 
#define FFT_FINAL_LENGTH   ((FFT_BLOCK_LENGTH) >> (1))

void InitFFT();
void CountFrequencyTable(uint32_t ConcertPitchA);
int CalculateFFT(int inputValues[FFT_BLOCK_LENGTH], fractional outputValues[FFT_BLOCK_LENGTH/2]);
double CalculateFreq(fractional outputFFT[FFT_BLOCK_LENGTH/2], double desiredFreq);
int CalcHarmNum(double desiredFreq, double freq);
#endif	/* FFT_H */

