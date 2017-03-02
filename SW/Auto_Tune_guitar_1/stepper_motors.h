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
    No = 0,
    Yes = 1
} __attribute__((packed)) DifferentDirection;

typedef enum
{
    Forward = 0,
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
    const DifferentDirection DifferentDirection;
} StepMotor;

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_, _dd_)   e##_name_,


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
void MotorOff(StepMotorIndex motorNum);
#endif	/* STEPPER_MOTORS_H */

