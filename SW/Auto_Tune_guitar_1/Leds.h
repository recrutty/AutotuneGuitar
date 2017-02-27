#ifndef LEDS_H
#define	LEDS_H
#include <stdint.h>
#include "xc.h"
#include "GPIO_binding.h"

typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    volatile uint8_t LedPin;
} Led;

#undef LED
#define LED (_name_, _po_, _tr_, _an_, _pin_)   e##_name_,

typedef enum
{
    #include "Led_list.h"
    eLedNum
} LedIndex;

void InitLeds();
void TurnLedOn(uint8_t ledNum);
void TurnLedOff(uint8_t ledNum);
void OneLedOn(uint8_t ledNum);
void AllLedsOff();

#endif	/* LEDS_H */
