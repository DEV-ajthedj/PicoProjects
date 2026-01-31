#include "infrared.h"

int main() {
    stdio_init_all();
    rx_init(RX_PIN);
    led_init(LED_PIN);

    gpio_set_irq_enabled_with_callback(RX_PIN, GPIO_IRQ_EDGE_FALL, true, gpio_callback);

    uint i = 0;
    while (1) {
        if (ir_detected) {
            ir_detected = false;
            printf("IR Wave %u Detected!\n", i++);
            led_on(LED_PIN);
        } else {
            led_off(LED_PIN);
        }
        sleep_ms(200);
    }
    return 0;
}