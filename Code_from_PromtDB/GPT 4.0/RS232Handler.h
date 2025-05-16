#ifndef RS232_HANDLER_H
#define RS232_HANDLER_H

#include <cstdint>

namespace RS232Module {

enum class Parity {
    NONE,
    EVEN,
    ODD
};

enum class FlowControl {
    NONE,
    RTS_CTS,
    XON_XOFF
};

struct RS232Config {
    uint32_t baudRate;
    Parity parity;
    uint8_t stopBits;
    uint8_t dataBits;
    FlowControl flowControl;
    uint16_t fifoSize;
};

class RS232Handler {
public:
    RS232Handler(const RS232Config& config);
    void initialize();
    void send(const char* data, uint16_t length);
    uint16_t receive(char* buffer, uint16_t maxLength);
    bool hasError() const;
    void clearError();
    void simulateHardware(bool enable);

private:
    RS232Config config;
    bool errorState;
    bool mockMode;
    char rxBuffer[256];
    char txBuffer[256];

    void handleTx();
    void handleRx();
};

}

#endif