
#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Buttons.h"

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_, _dP_, _dR_)   \
    Button _name_ =                                     \
    {                                                   \
        .Port = _po_,                                   \
        .Tris = _tr_,                                   \
        .Ansel = _an_,                                  \
        .PullUp = _up_,                                 \
        .BtnPin = _pin_,                                \
        .DebPressVal = _dP_,                            \
        .DebReleaseVal = _dR_                           \
    };

#include "Button_list.h"

#undef BUTTON
#define BUTTON(_name_, _po_, _tr_, _an_, _up_, _pin_, _dP_, _dR_) &_name_,

Button *BtnList[] ={
#include "Button_list.h"
};
