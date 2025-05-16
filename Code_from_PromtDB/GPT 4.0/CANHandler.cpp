#include "CANHandler.h"
#include <cstring>

using namespace CANModule;

static CANConfig defaultConfig = {
    500000U,
    2000000U,
    0x000U,
    0x7FFU,
    3U,
    64U,
    true,
    true,
    true
};

CANHandler::CANHandler(const CANConfig& cfg)
    : config(cfg), errorState(false), mockMode(false) {}

void CANHandler::simulateHardware(bool enable) {
    mockMode = enable;
}

void CANHandler::initialize() {
    if (!mockMode) {
        // Hardware-specific CAN initialization
    }
}

bool CANHandler::transmit(const uint8_t* data, uint8_t length, uint32_t id) {
    if (!data || length == 0U || length > 8U) {
        errorState = true;
        return false;
    }

    if (mockMode) {
        return true;
    }

    // Hardware CAN transmission logic
    return true;
}

bool CANHandler::receive(uint8_t* buffer, uint8_t* length, uint32_t* id) {
    if (!buffer || !length || !id) {
        errorState = true;
        return false;
    }

    if (mockMode) {
        *length = 8U;
        std::memset(buffer, 0xAB, *length);
        *id = 0x100;
        return true;
    }

    // Hardware CAN reception logic
    return true;
}

bool CANHandler::hasError() const {
    return errorState;
}

void CANHandler::clearError() {
    errorState = false;
}

void CANHandler::handleTx() {
    uint8_t diagFrame[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0, 0, 0, 0};
    transmit(diagFrame, sizeof(diagFrame), 0x7FF);
}

void CANHandler::handleRx() {
    uint8_t rxData[8];
    uint8_t len = 0;
    uint32_t id = 0;
    receive(rxData, &len, &id);
}

class CANTxThread {
    CANHandler& handler;
public:
    CANTxThread(CANHandler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleTx();
        }
    }
};

class CANRxThread {
    CANHandler& handler;
public:
    CANRxThread(CANHandler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleRx();
        }
    }
};

static CANHandler canHandler(defaultConfig);
static CANTxThread txThread(canHandler);
static CANRxThread rxThread(canHandler);

extern "C" void initCANModule() {
    canHandler.initialize();
}