#ifndef IR_H
#define IR_H

#define RX_PIN 0
#define LED_PIN 25

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void rx_init(uint8_t pin);
bool rx_receive(uint8_t pin);
void led_init(uint8_t pin);
void led_on(uint8_t pin);
void led_off(uint8_t pin);
extern volatile bool ir_detected;
void gpio_callback(uint gpio, uint32_t events);

#endif