#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include "rodos.h"

namespace UARTModule {

enum class UARTParity {
    NONE,
    EVEN,
    ODD
};

struct UARTConfig {
    int baudRate;
    int dataBits;
    int stopBits;
    UARTParity parity;
    int fifoSize;
};

class UARTHandler {
public:
    UARTHandler(const UARTConfig& config);
    void initialize();
    void send(const char* data, size_t length);
    size_t receive(char* buffer, size_t maxLength);
    bool hasError() const;
    void clearError();
    void simulateHardware(bool enabled);
private:
    UARTConfig config;
    HAL_UART* uart;
    char rxBuffer[128];
    char txBuffer[128];
    bool errorState;
    bool mockMode;

    void handleTx();
    void handleRx();
};

}

#endif