#include "pir.h"

volatile uint16_t pir_value = 0;

void pir_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, 0);
}

bool pir_read(uint8_t pin) {
    return gpio_get(pin);
}

void pir_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_RISE) {
        pir_value = 1;
    }
}