#include "UARTHandler.h"

using namespace UARTModule;

static UARTConfig defaultConfig = {9600, 8, 1, UARTParity::NONE, 128};

UARTHandler::UARTHandler(const UARTConfig& cfg)
    : config(cfg), uart(nullptr), errorState(false), mockMode(false) {}

void UARTHandler::simulateHardware(bool enabled) {
    mockMode = enabled;
}

void UARTHandler::initialize() {
    if (!mockMode) {
        uart = new HAL_UART(USART_IDX1);
        uart->init(config.baudRate);
    }
}

void UARTHandler::send(const char* data, size_t length) {
    if (!data || length == 0 || length > sizeof(txBuffer)) {
        errorState = true;
        return;
    }

    if (mockMode) {
        return;
    }

    size_t sent = uart->write(data, length);
    if (sent != length) {
        errorState = true;
    }
}

size_t UARTHandler::receive(char* buffer, size_t maxLength) {
    if (!buffer || maxLength == 0 || maxLength > sizeof(rxBuffer)) {
        errorState = true;
        return 0;
    }

    if (mockMode) {
        return 0;
    }

    size_t received = uart->read(buffer, maxLength);
    return received;
}

bool UARTHandler::hasError() const {
    return errorState;
}

void UARTHandler::clearError() {
    errorState = false;
}

void UARTHandler::handleTx() {
    const char* msg = "RODOS UART Tx\n";
    send(msg, strlen(msg));
}

void UARTHandler::handleRx() {
    char buffer[128];
    size_t len = receive(buffer, sizeof(buffer) - 1);
    if (len > 0) {
        buffer[len] = '\0';
    }
}

class UARTTxThread : public StaticThread<> {
    UARTHandler& handler;
public:
    UARTTxThread(UARTHandler& h) : handler(h) {}
    void run() {
        TIME_LOOP(1000 * MILLISECONDS, 1000 * MILLISECONDS) {
            handler.handleTx();
        }
    }
};

class UARTRxThread : public StaticThread<> {
    UARTHandler& handler;
public:
    UARTRxThread(UARTHandler& h) : handler(h) {}
    void run() {
        while (true) {
            handler.handleRx();
            suspendCallerUntil(NOW() + 200 * MILLISECONDS);
        }
    }
};

static UARTHandler uartHandler(defaultConfig);
static UARTTxThread txThread(uartHandler);
static UARTRxThread rxThread(uartHandler);

extern "C" void initUARTModule() {
    uartHandler.initialize();
}