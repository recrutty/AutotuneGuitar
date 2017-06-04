#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Leds.h"

#undef LED
#define LED(_name_, _po_, _tr_, _an_, _pin_)          \
    Led _name_ =                        \
    {                                   \
        .Port = _po_,                   \
        .Tris = _tr_,                   \
        .Ansel = _an_,                  \
        .LedPin = _pin_                 \
    };

#include "Led_list.h"

#undef LED
#define LED(_name_, _po_, _tr_, _an_, _pin_)   &_name_,

Led *LedList[] ={
#include "Led_list.h"
};
