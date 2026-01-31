#ifndef PIR_H
#define PIR_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define PIR_PIN 26

extern volatile uint16_t pir_value;
void pir_init(uint8_t pin);
bool pir_read(uint8_t pin);
void pir_callback(uint gpio, uint32_t events);

#endif