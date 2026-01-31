#include "pir.h"

int main() {
    stdio_init_all();
    pir_init(PIR_PIN);

    gpio_set_irq_enabled_with_callback(PIR_PIN, GPIO_IRQ_EDGE_RISE, true, &pir_callback);

    while (1) {
        if (pir_value) {
            printf("Motion detected!\n");
            pir_value = 0;
        }
        sleep_ms(100);
    }
}
