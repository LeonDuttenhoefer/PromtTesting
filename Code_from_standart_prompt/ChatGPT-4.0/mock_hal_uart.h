#ifndef MOCK_HAL_UART_H
#define MOCK_HAL_UART_H

#include <string>
#include <vector>

class MockHAL_UART {
public:
    int initCallCount = 0;
    std::string lastWritten;
    std::string readData;
    bool simulateRead = false;

    void init(int baudrate) {
        initCallCount++;
    }

    void write(const char* msg) {
        lastWritten = msg;
    }

    int read(char* buffer, int maxLength) {
        if (!simulateRead) return 0;
        int len = std::min((int)readData.length(), maxLength);
        strncpy(buffer, readData.c_str(), len);
        return len;
    }
};

#endif // MOCK_HAL_UART_H
