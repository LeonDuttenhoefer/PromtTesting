#include "RS485Handler.h"
#include <cstring>

using namespace RS485Module;

static RS485Config defaultConfig = {
    9600U,
    Parity::NONE,
    1U,
    8U,
    true,
    true,
    FlowControl::NONE,
    256U,
    0x01U
};

RS485Handler::RS485Handler(const RS485Config& cfg)
    : config(cfg), errorState(false), mockMode(false) {}

void RS485Handler::simulateHardware(bool enable) {
    mockMode = enable;
}

void RS485Handler::initialize() {
    if (!mockMode) {
        // Initialize UART, GPIO_DE, and termination resistor
    }
}

void RS485Handler::setDirection(bool transmit) {
    if (!mockMode) {
        if (transmit) {
            // Set GPIO_DE high
        } else {
            // Set GPIO_DE low
        }
    }
}

bool RS485Handler::detectCollision() {
    if (mockMode) {
        return false;
    }
    return false;
}

void RS485Handler::send(const char* data, uint16_t length) {
    if (!data || length == 0U || length > sizeof(txBuffer)) {
        errorState = true;
        return;
    }

    if (mockMode) {
        return;
    }

    setDirection(true);

    if (detectCollision()) {
        errorState = true;
        setDirection(false);
        return;
    }

    // Transmit data over UART

    setDirection(false);
}

uint16_t RS485Handler::receive(char* buffer, uint16_t maxLength) {
    if (!buffer || maxLength == 0U || maxLength > sizeof(rxBuffer)) {
        errorState = true;
        return 0;
    }

    if (mockMode) {
        std::memset(buffer, 0x55, maxLength);
        return maxLength;
    }

    // Receive data over UART

    return 0;
}

bool RS485Handler::hasError() const {
    return errorState;
}

void RS485Handler::clearError() {
    errorState = false;
}

void RS485Handler::handleTx() {
    const char* msg = "RS485 Tx Frame\n";
    send(msg, std::strlen(msg));
}

void RS485Handler::handleRx() {
    char buffer[256];
    receive(buffer, sizeof(buffer));
}

class RS485TxThread {
    RS485Handler& handler;
public:
    RS485TxThread(RS485Handler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleTx();
        }
    }
};

class RS485RxThread {
    RS485Handler& handler;
public:
    RS485RxThread(RS485Handler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleRx();
        }
    }
};

static RS485Handler rs485Handler(defaultConfig);
static RS485TxThread txThread(rs485Handler);
static RS485RxThread rxThread(rs485Handler);

extern "C" void initRS485Module() {
    rs485Handler.initialize();
}