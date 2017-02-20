#ifndef STEPPER_MOTORS_H
#define	STEPPER_MOTORS_H
#include <stdint.h>
#include "xc.h"
#include "GPIO_binding.h"

typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    volatile uint8_t FirstPin;
} StepMotorCoil;

typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    volatile uint8_t LedPin;
} StepMotorLed;

typedef struct{
    uint16_t RemainingSteps;
    uint8_t UpDown:1;
    uint8_t LastCoil:1;
    uint8_t ChangeDirection:1;    
} StepMotorState;

typedef struct
{
    const StepMotorCoil *CoilA;
    const StepMotorCoil *CoilB;
    const StepMotorLed *Led;    
    volatile StepMotorState LastState;
} StepMotor;

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_, _led_)   e##_name_,

typedef enum
{
    #include "StepperMotor_list.h"
    eStepperMotorNum
} StepMotorIndex;



void InitMotorsAndLeds();
void DoStep(uint8_t motorNum);
void DoSteps(uint8_t motorNum, uint16_t stepsNum)

#endif	/* STEPPER_MOTORS_H */

