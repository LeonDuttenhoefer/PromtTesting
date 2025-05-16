#ifndef RS485_HANDLER_H
#define RS485_HANDLER_H

#include <cstdint>

namespace RS485Module {

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

struct RS485Config {
    uint32_t baudRate;
    Parity parity;
    uint8_t stopBits;
    uint8_t dataBits;
    bool halfDuplex;
    bool enableTermination;
    FlowControl flowControl;
    uint16_t fifoSize;
    uint32_t gpioDirectionEnable;
};

class RS485Handler {
public:
    RS485Handler(const RS485Config& config);
    void initialize();
    void send(const char* data, uint16_t length);
    uint16_t receive(char* buffer, uint16_t maxLength);
    bool hasError() const;
    void clearError();
    void simulateHardware(bool enable);

private:
    RS485Config config;
    bool errorState;
    bool mockMode;
    char rxBuffer[256];
    char txBuffer[256];

    void setDirection(bool transmit);
    bool detectCollision();
    void handleTx();
    void handleRx();
};

}

#endif