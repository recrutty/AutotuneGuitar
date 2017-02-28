#ifndef BUTTONS_H
#define	BUTTONS_H
#include <stdint.h>
#include "xc.h"
#include "GPIO_binding.h"

typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    volatile uint16_t *PullUp;
    volatile uint8_t BtnPin;
} Button;

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_)   e##_name_,

typedef enum
{
    #include "Button_list.h"
    eBtnNum
} BtnIndex;

void InitBtns();
uint16_t BtnOpen(uint8_t btnNum);
#endif	/* BUTTONS_H */

