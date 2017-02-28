
#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Buttons.h"

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_)   \
    Button _name_ =                                     \
    {                                                   \
        .Port = _po_,                                   \
        .Tris = _tr_,                                   \
        .Ansel = _an_,                                  \
        .PullUp = _up_,                                 \
        .BtnPin = _pin_                                 \
    };

#include "Button_list.h"

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_) &_name_,

Button *BtnList[] ={
#include "Button_list.h"
};
