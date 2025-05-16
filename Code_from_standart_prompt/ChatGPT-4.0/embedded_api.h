#ifndef GPIO_API_H
#define GPIO_API_H

#include <stdint.h>

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} gpio_direction_t;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_value_t;

void gpio_init(uint32_t pin_number, gpio_direction_t direction);
void gpio_write(uint32_t pin_number, gpio_value_t value);
gpio_value_t gpio_read(uint32_t pin_number);

#endif // GPIO_API_H
