/*
File with board pinout description.
If the HW connection on board must change, 
in this file you should find all pins binding. 
*/

#ifndef GPIO_BINDING_H
#define	GPIO_BINDING_H

//analog select F is not implemented on chip and is read as 0. So its not implement in Microchip GPIO libraries
//anyway, my stepMotor libraries needs this address.
#define ANSELF_PTR ((uint16_t*)(0x0E5E))
#define ANSELF (*(ANSELF_PTR))

//10V StepUp Enable pin
#define STEP_POW_DIR (&TRISD)
#define STEP_POW_ANSEL (&ANSELD)
#define STEP_POW_PORT (&PORTD)
#define STEP_POW_BIT 7

//StepMotorDrivers wake up pin
#define STEP_WK_DIR (&TRISB)
#define STEP_WK_ANSEL (&ANSELB)
#define STEP_WK_PORT (&PORTB)
#define STEP_WK_BIT 12

//stepper motor drivers 1-7 pins
#define STEP1_A_DIR (&TRISF)
#define STEP1_A_ANSEL (&ANSELF)
#define STEP1_A_PORT (&PORTF)
#define STEP1_A_BIT 4
#define STEP1_B_DIR (&TRISB)
#define STEP1_B_ANSEL (&ANSELB)
#define STEP1_B_PORT (&PORTB)
#define STEP1_B_BIT 14

#define STEP2_A_DIR (&TRISB)
#define STEP2_A_ANSEL (&ANSELB)
#define STEP2_A_PORT (&PORTB)
#define STEP2_A_BIT 8
#define STEP2_B_DIR (&TRISB)
#define STEP2_B_ANSEL (&ANSELB)
#define STEP2_B_PORT (&PORTB)
#define STEP2_B_BIT 10

#define STEP3_A_DIR (&TRISB)
#define STEP3_A_ANSEL (&ANSELB)
#define STEP3_A_PORT (&PORTB)
#define STEP3_A_BIT 3
#define STEP3_B_DIR (&TRISB)
#define STEP3_B_ANSEL (&ANSELB)
#define STEP3_B_PORT (&PORTB)
#define STEP3_B_BIT 1

#define STEP4_A_DIR (&TRISE)
#define STEP4_A_ANSEL (&ANSELE)
#define STEP4_A_PORT (&PORTE)
#define STEP4_A_BIT 6
#define STEP4_B_DIR (&TRISG)
#define STEP4_B_ANSEL (&ANSELG)
#define STEP4_B_PORT (&PORTG)
#define STEP4_B_BIT 6

#define STEP5_A_DIR (&TRISE)
#define STEP5_A_ANSEL (&ANSELE)
#define STEP5_A_PORT (&PORTE)
#define STEP5_A_BIT 2
#define STEP5_B_DIR (&TRISE)
#define STEP5_B_ANSEL (&ANSELE)
#define STEP5_B_PORT (&PORTE)
#define STEP5_B_BIT 4

#define STEP6_A_DIR (&TRISF)
#define STEP6_A_ANSEL (&ANSELF)
#define STEP6_A_PORT (&PORTF)
#define STEP6_A_BIT 0
#define STEP6_B_DIR (&TRISE)
#define STEP6_B_ANSEL (&ANSELE)
#define STEP6_B_PORT (&PORTE)
#define STEP6_B_BIT 2

#define STEP7_A_DIR (&TRISD)
#define STEP7_A_ANSEL (&ANSELD)
#define STEP7_A_PORT (&PORTD)
#define STEP7_A_BIT 1
#define STEP7_B_DIR (&TRISD)
#define STEP7_B_ANSEL (&ANSELD)
#define STEP7_B_PORT (&PORTD)
#define STEP7_B_BIT 3

//Led pins
#define LED1_DIR (&TRISC)
#define LED1_ANSEL (&ANSELC)
#define LED1_PORT (&PORTC)
#define LED1_BIT 14
#define LED2_DIR (&TRISC)
#define LED2_ANSEL (&ANSELC)
#define LED2_PORT (&PORTC)
#define LED2_BIT 13
#define LED3_DIR (&TRISD)
#define LED3_ANSEL (&ANSELD)
#define LED3_PORT (&PORTD)
#define LED3_BIT 0
#define LED4_DIR (&TRISD)
#define LED4_ANSEL (&ANSELD)
#define LED4_PORT (&PORTD)
#define LED4_BIT 11
#define LED5_DIR (&TRISD)
#define LED5_ANSEL (&ANSELD)
#define LED5_PORT (&PORTD)
#define LED5_BIT 10
#define LED6_DIR (&TRISD)
#define LED6_ANSEL (&ANSELD)
#define LED6_PORT (&PORTD)
#define LED6_BIT 9
#define LED7_DIR (&TRISD)
#define LED7_ANSEL (&ANSELD)
#define LED7_PORT (&PORTD)
#define LED7_BIT 8

//Buttons pins
#define BTN1_DIR (&TRISB)
#define BTN1_ANSEL (&ANSELB)
#define BTN1_PULLUP (&CNPUB)
#define BTN1_PORT (&PORTB)
#define BTN1_PIN 15
#define BTN2_DIR (&TRISD)
#define BTN2_ANSEL (&ANSELD)
#define BTN2_PULLUP (&CNPUD)
#define BTN2_PORT (&PORTD)
#define BTN2_PIN 5
#define BTN3_DIR (&TRISD)
#define BTN3_ANSEL (&ANSELD)
#define BTN3_PULLUP (&CNPUD)
#define BTN3_PORT (&PORTD)
#define BTN3_PIN 6

#endif	/* GPIO_BINDING_H */

