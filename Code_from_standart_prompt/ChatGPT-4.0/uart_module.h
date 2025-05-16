#ifndef UART_MODULE_H
#define UART_MODULE_H

#include "rodos.h"

class UARTModule {
public:
    UARTModule(int uartNumber = 1, int baudrate = 115200);
    void write(const char* msg);
    int read(char* buffer, int maxLength);
private:
    HAL_UART* uart;
};

#endif // UART_MODULE_H
