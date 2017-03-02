#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Leds.h"

extern Led *LedList[];

void InitLeds()
{
    LedIndex i;
    for (i = 0; i < eLedNum; i++) 
    {
        Led *xLed = LedList[i];
        *(xLed->Tris) &= ~(1 << (xLed->LedPin));
        *(xLed->Ansel) &= ~(1 << (xLed->LedPin));
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

void OneLedOn(uint8_t ledNum)
{    
    AllLedsOff();
    TurnLedOn(ledNum);
}
void AllLedsOff()
{    
    LedIndex i;
    for (i = 0; i < eLedNum; i++) 
    {
        Led *xLed = LedList[i];
        *(xLed->Port) &= ~(1 << (xLed->LedPin));
    }   
}