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
uint16_t BtnClick(uint8_t btnNum)
{
    Button *btn = (BtnList[btnNum]);
    if (BtnOpen(btn))
    {
        
    } 
    return 0;
}