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
    volatile const uint8_t BtnPin;
    volatile const uint16_t DebPressVal;
    volatile const uint16_t DebReleaseVal;
    volatile uint16_t DebPressCounter;
    volatile uint16_t DebReleaseCounter;
    volatile uint8_t Pressed;
} Button;

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_, _dP_, _dR_)   e##_name_,

typedef enum
{
    #include "Button_list.h"
    eBtnNum
} __attribute__((packed)) BtnIndex;

void InitBtns();
uint16_t BtnOpen(Button *btn);
uint16_t DebPress(Button *btn);
uint16_t DebRelease(Button *btn);
uint16_t BtnClick(BtnIndex btnNum);
#endif	/* BUTTONS_H */

