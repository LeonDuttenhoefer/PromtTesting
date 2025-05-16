#ifndef CAN_HANDLER_H
#define CAN_HANDLER_H

#include <cstdint>

namespace CANModule {

struct CANConfig {
    uint32_t nominalBitrate;
    uint32_t dataBitrate;
    uint16_t filterStart;
    uint16_t filterEnd;
    uint8_t txMailboxSize;
    uint8_t rxMailboxSize;
    bool enableAutoRetransmit;
    bool enableDMA;
    bool enableBusOffRecovery;
};

class CANHandler {
public:
    CANHandler(const CANConfig& config);
    void initialize();
    bool transmit(const uint8_t* data, uint8_t length, uint32_t id);
    bool receive(uint8_t* buffer, uint8_t* length, uint32_t* id);
    bool hasError() const;
    void clearError();
    void simulateHardware(bool enable);

private:
    CANConfig config;
    bool errorState;
    bool mockMode;

    void handleTx();
    void handleRx();
    void sendDiagnostic();
};

}

#endif