#include "infrared.h"

volatile bool ir_detected = false;

void rx_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, false);
}

bool rx_receive(uint8_t pin) {
    return gpio_get(pin);
}

void led_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, true);
}

void led_on(uint8_t pin) {
    gpio_put(pin, true);
}

void led_off(uint8_t pin) {
    gpio_put(pin, false);
}

void gpio_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {
        if (gpio == RX_PIN) {
            ir_detected = true;
            led_on(LED_PIN);
        }
    } else if (events & GPIO_IRQ_EDGE_RISE) {
        if (gpio == RX_PIN) {
            ir_detected = false;
            led_off(LED_PIN);
        }
    }
}