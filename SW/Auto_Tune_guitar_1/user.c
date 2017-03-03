#include "stepper_motors.h"
#include "Leds.h"
#include "Buttons.h"
#include "user.h"

void InitApp()
{
    InitMotors();
    InitBtns();
    InitLeds();
}
