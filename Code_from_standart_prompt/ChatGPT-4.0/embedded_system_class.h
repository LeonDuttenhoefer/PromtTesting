#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <stdint.h>

class GpioPin {
public:
    GpioPin(uint32_t pin, bool isOutput);
    void write(bool value);
    bool read();

private:
    uint32_t pinNumber;
    bool outputMode;
};

#endif // GPIO_PIN_H
