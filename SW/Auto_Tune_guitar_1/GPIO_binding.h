#ifndef GPIO_BINDING_H
#define	GPIO_BINDING_H

#define ANSELF_PTR ((uint16_t*)(0x0E5E))
#define ANSELF (*(ANSELF_PTR))

#define STEP1_A_DIR (&TRISF)
#define STEP1_A_ANSEL (&ANSELF)
#define STEP1_A_PORT (&PORTF)
#define STEP1_A_BIT 4
#define STEP1_B_DIR (&TRISB)
#define STEP1_B_ANSEL (&ANSELB)
#define STEP1_B_PORT (&PORTB)
#define STEP1_B_BIT 14
#define STEP1_LED_DIR (&TRISC)
#define STEP1_LED_ANSEL (&ANSELC)
#define STEP1_LED_PORT (&PORTC)
#define STEP1_LED_BIT 14

#define STEP2_A_DIR (&TRISB)
#define STEP2_A_ANSEL (&ANSELB)
#define STEP2_A_PORT (&PORTB)
#define STEP2_A_BIT 8
#define STEP2_B_DIR (&TRISB)
#define STEP2_B_ANSEL (&ANSELB)
#define STEP2_B_PORT (&PORTB)
#define STEP2_B_BIT 10
#define STEP2_LED_DIR (&TRISC)
#define STEP2_LED_ANSEL (&ANSELC)
#define STEP2_LED_PORT (&PORTC)
#define STEP2_LED_BIT 13

#define STEP3_A_DIR (&TRISB)
#define STEP3_A_ANSEL (&ANSELB)
#define STEP3_A_PORT (&PORTB)
#define STEP3_A_BIT 3
#define STEP3_B_DIR (&TRISB)
#define STEP3_B_ANSEL (&ANSELB)
#define STEP3_B_PORT (&PORTB)
#define STEP3_B_BIT 1
#define STEP3_LED_DIR (&TRISD)
#define STEP3_LED_ANSEL (&ANSELD)
#define STEP3_LED_PORT (&PORTD)
#define STEP3_LED_BIT 0

#define STEP4_A_DIR (&TRISE)
#define STEP4_A_ANSEL (&ANSELE)
#define STEP4_A_PORT (&PORTE)
#define STEP4_A_BIT 6
#define STEP4_B_DIR (&TRISG)
#define STEP4_B_ANSEL (&ANSELG)
#define STEP4_B_PORT (&PORTG)
#define STEP4_B_BIT 6
#define STEP4_LED_DIR (&TRISD)
#define STEP4_LED_ANSEL (&ANSELD)
#define STEP4_LED_PORT (&PORTD)
#define STEP4_LED_BIT 11

#define STEP5_A_DIR (&TRISE)
#define STEP5_A_ANSEL (&ANSELE)
#define STEP5_A_PORT (&PORTE)
#define STEP5_A_BIT 2
#define STEP5_B_DIR (&TRISE)
#define STEP5_B_ANSEL (&ANSELE)
#define STEP5_B_PORT (&PORTE)
#define STEP5_B_BIT 4
#define STEP5_LED_DIR (&TRISD)
#define STEP5_LED_ANSEL (&ANSELD)
#define STEP5_LED_PORT (&PORTD)
#define STEP5_LED_BIT 10

#define STEP6_A_DIR (&TRISF)
#define STEP6_A_ANSEL (&ANSELF)
#define STEP6_A_PORT (&PORTF)
#define STEP6_A_BIT 0
#define STEP6_B_DIR (&TRISE)
#define STEP6_B_ANSEL (&ANSELE)
#define STEP6_B_PORT (&PORTE)
#define STEP6_B_BIT 2
#define STEP6_LED_DIR (&TRISD)
#define STEP6_LED_ANSEL (&ANSELD)
#define STEP6_LED_PORT (&PORTD)
#define STEP6_LED_BIT 9

#define STEP7_A_DIR (&TRISD)
#define STEP7_A_ANSEL (&ANSELD)
#define STEP7_A_PORT (&PORTD)
#define STEP7_A_BIT 1
#define STEP7_B_DIR (&TRISD)
#define STEP7_B_ANSEL (&ANSELD)
#define STEP7_B_PORT (&PORTD)
#define STEP7_B_BIT 3
#define STEP7_LED_DIR (&TRISD)
#define STEP7_LED_ANSEL (&ANSELD)
#define STEP7_LED_PORT (&PORTD)
#define STEP7_LED_BIT 8

#define SW1_DIR (&TRISB)
#define SW1_ANSEL (&ANSELB)
#define SW1_PULLUP (&CNPUB)
#define SW1_PORT (&PORTB)
#define SW1_PIN 15
#define SW2_DIR (&TRISD)
#define SW2_ANSEL (&ANSELD)
#define SW2_PULLUP (&CNPUD)
#define SW2_PORT (&PORTD)
#define SW2_PIN 5
#define SW3_DIR (&TRISD)
#define SW3_ANSEL (&ANSELD)
#define SW3_PULLUP (&CNPUD)
#define SW3_PORT (&PORTD)
#define SW3_PIN 6

#endif	/* GPIO_BINDING_H */

