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
#define LED(_name_, _po_, _tr_, _an_, _pin_)   e##_name_,

typedef enum
{
    #include "Led_list.h"
    eLedNum
} __attribute__((packed)) LedIndex;

void InitLeds();
void TurnLedOn(LedIndex ledNum);
void TurnLedOff(LedIndex ledNum);
void OneLedOn(LedIndex ledNum);
void OneLedOff(LedIndex ledNum);
void InverseLeds();
void AllLedsOn();
void AllLedsOff();
#endif	/* LEDS_H */
