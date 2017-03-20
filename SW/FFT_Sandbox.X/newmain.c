#define FFT_BLOCK_LENGTH 512
#define LOG2_BLOCK_LENGTH 9  

#include <stdio.h>
#include "dsp.h"
#include <stdlib.h>


fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));/**/

int main() 
{  
    fractcomplex* karel = TwidFactorInit(LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);

    return 0;
}

