#include "gtest/gtest.h"
#include "mock_hal_uart.h"

// Example class to test
class UARTModule {
public:
    UARTModule(MockHAL_UART* uart, int baudrate = 115200) : uart(uart) {
        uart->init(baudrate);
    }

    void write(const char* msg) {
        uart->write(msg);
    }

    int read(char* buffer, int maxLength) {
        return uart->read(buffer, maxLength);
    }

private:
    MockHAL_UART* uart;
};

TEST(UARTModuleTest, InitializationCallsInit) {
    MockHAL_UART mockUart;
    UARTModule uartMod(&mockUart, 9600);
    EXPECT_EQ(mockUart.initCallCount, 1);
}

TEST(UARTModuleTest, WriteSendsCorrectData) {
    MockHAL_UART mockUart;
    UARTModule uartMod(&mockUart);
    uartMod.write("Hello");
    EXPECT_EQ(mockUart.lastWritten, "Hello");
}

TEST(UARTModuleTest, ReadReceivesData) {
    MockHAL_UART mockUart;
    mockUart.simulateRead = true;
    mockUart.readData = "Test123";
    UARTModule uartMod(&mockUart);

    char buffer[20] = {0};
    int len = uartMod.read(buffer, sizeof(buffer));
    EXPECT_EQ(len, 7);
    EXPECT_STREQ(buffer, "Test123");
}
