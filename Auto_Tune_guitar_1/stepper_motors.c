#include "stepper_motors.h"

#include <stdint.h>
#include "xc.h"
typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    uint8_t FirstPin;
} StepMotorCoil;

typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    uint8_t LedPin;
} StepMotorLed;

typedef struct
{
    const StepMotorCoil* CoilA;
    const StepMotorCoil* CoilB;
    const StepMotorLed* Led;
} StepMotor;

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
const StepMotorCoil CoilB_Motor7 = {STEP7_B_PORT, STEP7_B_DIR, STEP7_B_ANSEL, STEP7_B_BIT};

const StepMotorLed Led_Motor1 = {STEP1_LED_PORT, STEP1_LED_DIR, STEP1_LED_ANSEL, STEP1_LED_BIT};
const StepMotorLed Led_Motor2 = {STEP2_LED_PORT, STEP2_LED_DIR, STEP2_LED_ANSEL, STEP2_LED_BIT};
const StepMotorLed Led_Motor3 = {STEP3_LED_PORT, STEP3_LED_DIR, STEP3_LED_ANSEL, STEP3_LED_BIT};
const StepMotorLed Led_Motor4 = {STEP4_LED_PORT, STEP4_LED_DIR, STEP4_LED_ANSEL, STEP4_LED_BIT};
const StepMotorLed Led_Motor5 = {STEP5_LED_PORT, STEP5_LED_DIR, STEP5_LED_ANSEL, STEP5_LED_BIT};
const StepMotorLed Led_Motor6 = {STEP6_LED_PORT, STEP6_LED_DIR, STEP6_LED_ANSEL, STEP6_LED_BIT};
const StepMotorLed Led_Motor7 = {STEP7_LED_PORT, STEP7_LED_DIR, STEP7_LED_ANSEL, STEP7_LED_BIT};


#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_, _led_)   e##_name_,

typedef enum
{
    #include "StepperMotor_list.h"
    eStepperMotorNum
} StepMotorIndex;

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_, _led_)   \
    StepMotor _name_ =                  \
    {                                   \
        .CoilA = &_cA_,                 \
        .CoilB = &_cB_,                 \
        .Led = &_led_                   \
    };

#include "StepperMotor_list.h"

#undef STEPPER_MOTOR
#define STEPPER_MOTOR(_name_, _cA_, _cB_, _led_)   &_name_,

StepMotor* StepperMotorList[] = 
{
    #include "StepperMotor_list.h"
};

void InitMotors()
{
    int i;
    for (i = 0; i < eStepperMotorNum; i++) 
    {
        *(StepperMotorList[i]->CoilA->Port) |= (3 << StepperMotorList[i]->CoilA->FirstPin);
        *(StepperMotorList[i]->CoilA->Tris) |= (3 << StepperMotorList[i]->CoilA->FirstPin);
        *(StepperMotorList[i]->CoilA->Ansel) |= (3 << StepperMotorList[i]->CoilA->FirstPin);
        
        *(StepperMotorList[i]->CoilB->Port) |= (3 << StepperMotorList[i]->CoilB->FirstPin);
        *(StepperMotorList[i]->CoilB->Tris) |= (3 << StepperMotorList[i]->CoilB->FirstPin);
        *(StepperMotorList[i]->CoilB->Ansel) |= (3 << StepperMotorList[i]->CoilB->FirstPin);

        *(StepperMotorList[i]->Led->Port) |= (1 << StepperMotorList[i]->Led->LedPin);
        *(StepperMotorList[i]->Led->Tris) |= (1 << StepperMotorList[i]->Led->LedPin);
        *(StepperMotorList[i]->Led->Ansel) |= (1 << StepperMotorList[i]->Led->LedPin);
    }

}