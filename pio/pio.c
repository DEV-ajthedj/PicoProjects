#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "test.pio.h"

volatile bool button1pressed = 0;
bool state1Changed = 0;
volatile bool button2pressed = 0;
bool state2Changed = 0;

enum direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
enum direction current_dir = UP;
int matrix[8][8] = {0};
int x = 0;
int y = 0;

uint32_t getButtonPIO(PIO pio, uint sm, uint offset, uint btnpin) {
    test_program_init(pio, sm, offset, btnpin, 1);
    pio_sm_set_enabled(pio, sm, true);
    return (bool)(pio_sm_get_blocking(pio, sm) > 0);
}

void updateDir() {
    switch (current_dir) {
        case UP:
            current_dir = RIGHT;
            break;
        case RIGHT:
            current_dir = DOWN;
            break;
        case DOWN:
            current_dir = LEFT;
            break;
        case LEFT:
            current_dir = UP;
            break;
    }
}

void move() {
    switch (current_dir) {
        case UP:
            matrix[y][x] = 0;
            y = (y + 1) % 8;
            matrix[y][x] = 1;
            break;
        case RIGHT:
            matrix[y][x] = 0;
            x = (x - 1 + 8) % 8;
            matrix[y][x] = 1;
            break;
        case DOWN:
            matrix[y][x] = 0;
            y = (y - 1 + 8) % 8;
            matrix[y][x] = 1;
            break;
        case LEFT:
            matrix[y][x] = 0;
            x = (x + 1) % 8;
            matrix[y][x] = 1;
            break;
    }
}

void showMatrix() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &test_program);
    printf("Loaded program at %d\n", offset);
    while (true) {
        button1pressed = getButtonPIO(pio, 0, offset, 0);
        if (button1pressed && !state1Changed) {
            move();
            showMatrix();
            state1Changed = 1;
        } else if (!button1pressed && state1Changed) {
            state1Changed = 0;
        }
        button2pressed = getButtonPIO(pio, 2, offset, 1);
        if (button2pressed && !state2Changed) {
            updateDir();
            state2Changed = 1;
        } else if (!button2pressed && state2Changed) {
            state2Changed = 0;
        }
        sleep_ms(50);
    }
}
