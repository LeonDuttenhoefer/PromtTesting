#include "SPIHandler.h"
#include <cstring>

using namespace SPIModule;

static SPIConfig defaultConfig = {1000000U, 0U, SPIBitOrder::MSB_FIRST, 8U, true};

SPIHandler::SPIHandler(const SPIConfig& cfg)
    : config(cfg), errorState(false), mockMode(false) {}

void SPIHandler::simulateHardware(bool enable) {
    mockMode = enable;
}

void SPIHandler::initialize() {
    if (!mockMode) {
        // Hardware-specific SPI initialization
    }
}

bool SPIHandler::transmit(const uint8_t* data, uint16_t length) {
    if (!data || length == 0U) {
        errorState = true;
        return false;
    }

    if (mockMode) {
        return true;
    }

    // Hardware DMA SPI transmission
    return true;
}

bool SPIHandler::receive(uint8_t* buffer, uint16_t length) {
    if (!buffer || length == 0U) {
        errorState = true;
        return false;
    }

    if (mockMode) {
        std::memset(buffer, 0xAA, length);
        return true;
    }

    // Hardware DMA SPI reception
    return true;
}

bool SPIHandler::hasError() const {
    return errorState;
}

void SPIHandler::clearError() {
    errorState = false;
}

void SPIHandler::handleTx() {
    uint8_t txData[8] = {1,2,3,4,5,6,7,8};
    transmit(txData, sizeof(txData));
}

void SPIHandler::handleRx() {
    uint8_t rxData[8];
    receive(rxData, sizeof(rxData));
}

class SPITxThread {
    SPIHandler& handler;
public:
    SPITxThread(SPIHandler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleTx();
        }
    }
};

class SPIRxThread {
    SPIHandler& handler;
public:
    SPIRxThread(SPIHandler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleRx();
        }
    }
};

static SPIHandler spiHandler(defaultConfig);
static SPITxThread txThread(spiHandler);
static SPIRxThread rxThread(spiHandler);

extern "C" void initSPIModule() {
    spiHandler.initialize();
}