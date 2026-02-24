#include "infrared.h"

int main() {
    stdio_init_all();
    rx_init(RX_PIN);
    led_init(LED_PIN);
    gpio_set_irq_enabled_with_callback(RX_PIN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, gpio_callback);
    
    uint i = 0;
    while (1) {
        if (ir_detected) {
            ir_detected = false;
            printf("IR Wave %u Detected!\n", i++);
        }
        sleep_ms(10);
    }

    return 0;
}