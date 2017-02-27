
const StepMotorLed Led_Motor1 = {STEP1_LED_PORT, STEP1_LED_DIR, STEP1_LED_ANSEL, STEP1_LED_BIT};
const StepMotorLed Led_Motor2 = {STEP2_LED_PORT, STEP2_LED_DIR, STEP2_LED_ANSEL, STEP2_LED_BIT};
const StepMotorLed Led_Motor3 = {STEP3_LED_PORT, STEP3_LED_DIR, STEP3_LED_ANSEL, STEP3_LED_BIT};
const StepMotorLed Led_Motor4 = {STEP4_LED_PORT, STEP4_LED_DIR, STEP4_LED_ANSEL, STEP4_LED_BIT};
const StepMotorLed Led_Motor5 = {STEP5_LED_PORT, STEP5_LED_DIR, STEP5_LED_ANSEL, STEP5_LED_BIT};
const StepMotorLed Led_Motor6 = {STEP6_LED_PORT, STEP6_LED_DIR, STEP6_LED_ANSEL, STEP6_LED_BIT};
const StepMotorLed Led_Motor7 = {STEP7_LED_PORT, STEP7_LED_DIR, STEP7_LED_ANSEL, STEP7_LED_BIT}; 


        /*
        StepMotorLed *xled = (StepMotorLed*)(StepperMotorList[i]->Led);
        *(xled->Tris) &= ~(1 << xled->LedPin);
        *(xled->Ansel) &= ~(1 << xled->LedPin);
*/
/*
typedef struct
{
    volatile uint16_t *Port;
    volatile uint16_t *Tris;
    volatile uint16_t *Ansel;
    volatile uint8_t LedPin;
} StepMotorLed;
*/
