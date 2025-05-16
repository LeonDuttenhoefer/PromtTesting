#include "RS232Handler.h"
#include <cstring>

using namespace RS232Module;

static RS232Config defaultConfig = {
    115200U,
    Parity::NONE,
    1U,
    8U,
    FlowControl::NONE,
    256U
};

RS232Handler::RS232Handler(const RS232Config& cfg)
    : config(cfg), errorState(false), mockMode(false) {}

void RS232Handler::simulateHardware(bool enable) {
    mockMode = enable;
}

void RS232Handler::initialize() {
    if (!mockMode) {
        // Hardware-specific UART init
    }
}

void RS232Handler::send(const char* data, uint16_t length) {
    if (!data || length == 0U || length > sizeof(txBuffer)) {
        errorState = true;
        return;
    }

    if (mockMode) {
        return;
    }

    // Hardware UART transmission logic
}

uint16_t RS232Handler::receive(char* buffer, uint16_t maxLength) {
    if (!buffer || maxLength == 0U || maxLength > sizeof(rxBuffer)) {
        errorState = true;
        return 0;
    }

    if (mockMode) {
        std::memset(buffer, 0x55, maxLength);
        return maxLength;
    }

    // Hardware UART receive logic
    return 0;
}

bool RS232Handler::hasError() const {
    return errorState;
}

void RS232Handler::clearError() {
    errorState = false;
}

void RS232Handler::handleTx() {
    const char* msg = "RS232 Tx Frame
";
    send(msg, std::strlen(msg));
}

void RS232Handler::handleRx() {
    char buffer[256];
    receive(buffer, sizeof(buffer));
}

class RS232TxThread {
    RS232Handler& handler;
public:
    RS232TxThread(RS232Handler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleTx();
        }
    }
};

class RS232RxThread {
    RS232Handler& handler;
public:
    RS232RxThread(RS232Handler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleRx();
        }
    }
};

static RS232Handler rs232Handler(defaultConfig);
static RS232TxThread txThread(rs232Handler);
static RS232RxThread rxThread(rs232Handler);

extern "C" void initRS232Module() {
    rs232Handler.initialize();
}