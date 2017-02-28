#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Leds.h"

extern Led *LedList[];

void InitLeds()
{
    int i;
    for (i = 0; i < eLedNum; i++) 
    {
        *((LedList[i])->Tris) &= ~(1 << ((LedList[i])->LedPin));
        *((LedList[i])->Ansel) &= ~(1 << ((LedList[i])->LedPin));
    }    
}

void TurnLedOn(uint8_t ledNum)
{
    *(LedList[ledNum]->Port) |= (1 << LedList[ledNum]->LedPin);                
}

void TurnLedOff(uint8_t ledNum)
{
    *(LedList[ledNum]->Port) &= ~(1 << LedList[ledNum]->LedPin);                
}