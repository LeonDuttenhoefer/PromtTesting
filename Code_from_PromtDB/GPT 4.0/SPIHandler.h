#ifndef SPI_HANDLER_H
#define SPI_HANDLER_H

#include <cstdint>

namespace SPIModule {

enum class SPIBitOrder {
    MSB_FIRST,
    LSB_FIRST
};

struct SPIConfig {
    uint32_t clockSpeedHz;
    uint8_t mode;
    SPIBitOrder bitOrder;
    uint8_t dataSize;
    bool useDMA;
};

class SPIHandler {
public:
    SPIHandler(const SPIConfig& config);
    void initialize();
    bool transmit(const uint8_t* data, uint16_t length);
    bool receive(uint8_t* buffer, uint16_t length);
    bool hasError() const;
    void clearError();
    void simulateHardware(bool enable);

private:
    SPIConfig config;
    bool errorState;
    bool mockMode;

    void handleTx();
    void handleRx();
};

}

#endif