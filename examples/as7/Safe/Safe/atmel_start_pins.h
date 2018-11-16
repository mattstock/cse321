/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define LED_G GPIO(GPIO_PORTA, 4)
#define LED_R GPIO(GPIO_PORTA, 5)
#define LED_B GPIO(GPIO_PORTA, 6)
#define LED_Y GPIO(GPIO_PORTA, 7)
#define PA08 GPIO(GPIO_PORTA, 8)
#define PA09 GPIO(GPIO_PORTA, 9)
#define PA14 GPIO(GPIO_PORTA, 14)
#define SW0 GPIO(GPIO_PORTA, 15)
#define PA19 GPIO(GPIO_PORTA, 19)
#define K_ROW0 GPIO(GPIO_PORTB, 0)
#define K_ROW1 GPIO(GPIO_PORTB, 1)
#define K_COL0 GPIO(GPIO_PORTB, 2)
#define K_COL1 GPIO(GPIO_PORTB, 3)
#define K_COL3 GPIO(GPIO_PORTB, 4)
#define K_COL2 GPIO(GPIO_PORTB, 5)
#define K_ROW2 GPIO(GPIO_PORTB, 6)
#define K_ROW3 GPIO(GPIO_PORTB, 7)
#define LED0 GPIO(GPIO_PORTB, 30)

#endif // ATMEL_START_PINS_H_INCLUDED
