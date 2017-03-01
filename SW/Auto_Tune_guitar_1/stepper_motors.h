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

typedef enum
{
    Forward = -1,
    Back = 1
} __attribute__((packed)) StepMotorDirection;

typedef struct{
    uint16_t RemainingSteps;
    int8_t RotationState;
    StepMotorDirection Direction;
} StepMotorState;

typedef struct
{
    const StepMotorCoil *CoilA;
    const StepMotorCoil *CoilB;
    volatile StepMotorState LastState;
} StepMotor;

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_)   e##_name_,


typedef enum
{
    #include "StepperMotor_list.h"
    eStepperMotorNum
} StepMotorIndex;

void InitMotors();
void MotorsSleep();
void MotorsWake();
void DoStep(StepMotorIndex motorNum, StepMotorDirection dir);
void DoSteps(StepMotorIndex motorNum, StepMotorDirection dir, uint16_t stepsNum);

#endif	/* STEPPER_MOTORS_H */

