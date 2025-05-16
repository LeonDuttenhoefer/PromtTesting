#include "uart_module.h"

UARTModule::UARTModule(int uartNumber, int baudrate) {
    uart = new HAL_UART(uartNumber);
    uart->init(baudrate);
}

void UARTModule::write(const char* msg) {
    uart->write(msg);
}

int UARTModule::read(char* buffer, int maxLength) {
    return uart->read(buffer, maxLength);
}
