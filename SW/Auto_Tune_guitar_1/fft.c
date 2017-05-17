#include <xc.h>
#include <stdint.h>
#include <dsp.h>
#include "fft.h"
#include "Strings_freq.h"
#include "GPIO_binding.h"


//double ADC_SampleRate = 1593.76;
double ADC_SampleRate = 3174.4;
double FFT_MaxFreq;

GuitarString strings[7];
double A_low_freq;

double TonesFreq[7];
fractcomplex sigCmpx[FFT_BLOCK_LENGTH]
__attribute__ ((eds, space(ymemory), aligned (FFT_BLOCK_LENGTH * 2 *2)));	
 
fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));

void InitFFT()
{
    TwidFactorInit(LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);
    
    CountFrequencyTable(FREQ_a1);
}
void CountFrequencyTable(uint32_t ConcertPitchA)
{
    strings[0].ADC_SampleRateHz = 1593.76 / 2;
    strings[1].ADC_SampleRateHz = 1593.76 / 2;
    strings[2].ADC_SampleRateHz = 1593.76 / 2;
    strings[3].ADC_SampleRateHz = 1593.76 / 2;
    strings[4].ADC_SampleRateHz = 3174.4 / 2;
    strings[5].ADC_SampleRateHz = 3174.4 / 2;
    strings[6].ADC_SampleRateHz = 3174.4 / 2;

    strings[0].ADC_SampleRate = 250;
    strings[1].ADC_SampleRate = 250;
    strings[2].ADC_SampleRate = 250;
    strings[3].ADC_SampleRate = 250;
    strings[4].ADC_SampleRate = 125;
    strings[5].ADC_SampleRate = 125;
    strings[6].ADC_SampleRate = 125;
    
    strings[0].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[0].ADC_SampleRateHz * 8))) * SEMITONE_2_MULTIPLIER);
    strings[1].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[1].ADC_SampleRateHz * 8))) * SEMITONE_7_MULTIPLIER);
    strings[2].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[2].ADC_SampleRateHz * 8))) * 2 + 0.5);
    strings[3].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[3].ADC_SampleRateHz * 8))) * SEMITONE_5_MULTIPLIER * 2);
    strings[4].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[4].ADC_SampleRateHz * 8))) * SEMITONE_10_MULTIPLIER * 2);
    strings[5].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[5].ADC_SampleRateHz * 8))) * SEMITONE_2_MULTIPLIER * 4);
    strings[6].Freq = ((((double) (ConcertPitchA * FFT_LAST_ELEMENT)) / ((double) (strings[6].ADC_SampleRateHz * 8))) * SEMITONE_7_MULTIPLIER * 4);
    
    strings[0].StepsCoef = 400;
    strings[1].StepsCoef = 400;
    strings[2].StepsCoef = 400;
    strings[3].StepsCoef = 400;
    strings[4].StepsCoef = 450;
    strings[5].StepsCoef = 650;
    strings[6].StepsCoef = 800;
}

int CalculateFFT(int inputValues[], fractional outputValues[FFT_BLOCK_LENGTH/2])
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
    BitReverseComplex(LOG2_BLOCK_LENGTH, &sigCmpx[0]);
    SquareMagnitudeCplx(FFT_BLOCK_LENGTH / 2, &sigCmpx[0], outputValues);
    
    int16_t	peakFrequencyBin = 0;
    fractional val = VectorMax(FFT_BLOCK_LENGTH/2, outputValues, &peakFrequencyBin);
    if (outputValues[peakFrequencyBin]>=200)
    {        
        return peakFrequencyBin;
    }
    else
    {
        return 0;
    }

}
#define MAX_FREQ_HARM (10)
double CalculateFreq(fractional outputFFT[FFT_BLOCK_LENGTH/2], double desiredFreq)
{
    FreqPeak peaks[MAX_FREQ_HARM]={{ 0 }};
    int peaksCounter = 0;
    int found=0;
    int i;
    for (i = 50; i < FFT_FINAL_LENGTH; i++) 
    {        
        if (outputFFT[i]>=10) 
        {
            if (outputFFT[i+1]>=outputFFT[i])
            {
                continue;
            }
            if (found)
            {
                continue;
            }
            if((i-10) < peaks[peaksCounter].Freq)
            {
                continue;
            }
            double diff;
            double minimum = FFT_MaxFreq;
            uint8_t minIndex = 0;
            int j;
            for (j = 1; j < MAX_FREQ_HARM; j++)
            {
                diff = (desiredFreq * j) - i;
                if (diff < 0)
                {
                    diff = i - (desiredFreq * j);
                }
                
                if (diff < minimum)
                {
                    minimum = diff;
                    minIndex = j;
                }
            }
            
            peaks[peaksCounter].Freq = i;
            peaks[peaksCounter].HarmNum = minIndex;
            peaksCounter++;
            if (peaksCounter==MAX_FREQ_HARM)
            {
                int kuk = 0;
                kuk++;
                return 0;
            }
            found = 1;
        }
        else
        {
            found = 0;
        }
    }
    double diff;
    double minimum = FFT_MaxFreq;
    uint8_t minIndex = 0;
    int goodPeaksLimit = 3*(((int)desiredFreq)/4);
    for (i = 0; i < MAX_FREQ_HARM; i++)
    {
        if (peaks[i + 1].Freq == 0)
        {
            break;
        }
        diff = peaks[i + 1].Freq - peaks[i].Freq;
        if (diff < goodPeaksLimit)
        {
            continue;
        }

        if (diff < minimum)
        {
            minimum = diff;
        }
    }
    int goodPeaks = 0;
    int lastGoodPeak = 0;
    int lastGoodHarm = 0;
    int harm = 0;
    
    for (i = 0; i < MAX_FREQ_HARM; i++)
    {
        if (peaks[i].Freq == 0)
        {
            break;
        }
        harm = CalcHarmNum(minimum, peaks[i].Freq);

        if((((minimum * harm) - peaks[i].Freq) < 10) && (((peaks[i].Freq) - (minimum * harm)) > -10))
        {
            goodPeaks++;
            lastGoodPeak = i;
            lastGoodHarm = harm;
        }
    }
    if (lastGoodHarm == 0)
    {
        return 0;
    }
    if (goodPeaks<3)
    {        
        return 0;
    }

    double result = peaks[lastGoodPeak].Freq/((double)lastGoodHarm);
    return result / CalcHarmNum(desiredFreq, result);
}


int CalcHarmNum(double desiredFreq, double freq)
{
    double diff;
    double minimum = FFT_MaxFreq;
    uint8_t minIndex = 0;
    int i;
    for (i = 1; i < MAX_FREQ_HARM; i++)
    {
        diff = (desiredFreq * i) - (double)freq;
        if (diff < 0)
        {
            diff = (double)freq - (desiredFreq * i);
        }

        if (diff < minimum)
        {
            minimum = diff;
            minIndex = i;
        }
    }

    return minIndex;
}