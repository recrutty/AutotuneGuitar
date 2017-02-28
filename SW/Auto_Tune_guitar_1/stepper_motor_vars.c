
#include "GPIO_binding.h"
#include <stdint.h>
#include "xc.h"
#include "stepper_motors.h"

// <editor-fold defaultstate="collapsed" desc="Coils and Leds Definitions">
const StepMotorCoil CoilA_Motor1 = {STEP1_A_PORT, STEP1_A_DIR, STEP1_A_ANSEL, STEP1_A_BIT};
const StepMotorCoil CoilB_Motor1 = {STEP1_B_PORT, STEP1_B_DIR, STEP1_B_ANSEL, STEP1_B_BIT};
const StepMotorCoil CoilA_Motor2 = {STEP2_A_PORT, STEP2_A_DIR, STEP2_A_ANSEL, STEP2_A_BIT};
const StepMotorCoil CoilB_Motor2 = {STEP2_B_PORT, STEP2_B_DIR, STEP2_B_ANSEL, STEP2_B_BIT};
const StepMotorCoil CoilA_Motor3 = {STEP3_A_PORT, STEP3_A_DIR, STEP3_A_ANSEL, STEP3_A_BIT};
const StepMotorCoil CoilB_Motor3 = {STEP3_B_PORT, STEP3_B_DIR, STEP3_B_ANSEL, STEP3_B_BIT};
const StepMotorCoil CoilA_Motor4 = {STEP4_A_PORT, STEP4_A_DIR, STEP4_A_ANSEL, STEP4_A_BIT};
const StepMotorCoil CoilB_Motor4 = {STEP4_B_PORT, STEP4_B_DIR, STEP4_B_ANSEL, STEP4_B_BIT};
const StepMotorCoil CoilA_Motor5 = {STEP5_A_PORT, STEP5_A_DIR, STEP5_A_ANSEL, STEP5_A_BIT};
const StepMotorCoil CoilB_Motor5 = {STEP5_B_PORT, STEP5_B_DIR, STEP5_B_ANSEL, STEP5_B_BIT};
const StepMotorCoil CoilA_Motor6 = {STEP6_A_PORT, STEP6_A_DIR, STEP6_A_ANSEL, STEP6_A_BIT};
const StepMotorCoil CoilB_Motor6 = {STEP6_B_PORT, STEP6_B_DIR, STEP6_B_ANSEL, STEP6_B_BIT};
const StepMotorCoil CoilA_Motor7 = {STEP7_A_PORT, STEP7_A_DIR, STEP7_A_ANSEL, STEP7_A_BIT};
const StepMotorCoil CoilB_Motor7 = {STEP7_B_PORT, STEP7_B_DIR, STEP7_B_ANSEL, STEP7_B_BIT};// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Motors array declaration">
#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_)   \
    StepMotor _name_ =                  \
    {                                   \
        .CoilA = &_cA_,                 \
        .CoilB = &_cB_                  \
    };

#include "StepperMotor_list.h"

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_)   &_name_,

StepMotor *StepperMotorList[] ={
#include "StepperMotor_list.h"
}; // </editor-fold>

