#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "Buttons.h"

extern Button *BtnList[];

void InitBtns()
{
    int i;
    for (i = 0; i < eBtnNum; i++) 
    {
        *(BtnList[i]->Tris) |= (1 << (BtnList[i]->BtnPin));
        *(BtnList[i]->Ansel) &= ~(1 << (BtnList[i]->BtnPin));
        *(BtnList[i]->PullUp) |= (1 << (BtnList[i]->BtnPin));
    }
}
uint16_t BtnOpen(uint8_t btnNum)
{
    return ((*(BtnList[btnNum]->Port)) & (1 << (BtnList[btnNum]->BtnPin)));
}