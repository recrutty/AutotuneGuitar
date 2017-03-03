#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Buttons.h"

extern Button *BtnList[];

void InitBtns()
{
    BtnIndex i;
    for (i = 0; i < eBtnNum; i++) 
    {
        Button *btn = (Button*)(BtnList[i]);
        *(btn->Tris) |= (1 << (btn->BtnPin));
        *(btn->Ansel) &= ~(1 << (btn->BtnPin));
        *(btn->PullUp) |= (1 << (btn->BtnPin));
    }
}
uint16_t DebPress(Button *btn)
{
    return --(btn->DebPressCounter);
}
uint16_t DebRelease(Button *btn)
{
    return --(btn->DebReleaseCounter);
}

uint16_t BtnOpen(Button *btn)
{
    return ((*(btn->Port)) & (1 << (btn->BtnPin)));
}
uint16_t BtnClick(BtnIndex btnNum)
{
    Button *btn = (BtnList[btnNum]);
    if (BtnOpen(btn))
    {
        btn->DebPressCounter = btn->DebPressVal;
        if (DebRelease(btn)<=0)
        {
            (btn->Pressed) = 0;
            btn->DebReleaseCounter = btn->DebReleaseVal;
        } 
    }
    else
    {        
        btn->DebReleaseCounter = btn->DebReleaseVal;
        if (DebPress(btn)<=0)
        {            
            if ((btn->Pressed)==0)
            {
                (btn->Pressed) = 1;
                return 1;
            }
            btn->DebPressCounter = btn->DebPressVal;
        }
    }
    return 0;
}