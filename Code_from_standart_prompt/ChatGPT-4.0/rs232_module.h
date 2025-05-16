#ifndef RS232_MODULE_H
#define RS232_MODULE_H

#include <stdint.h>

void rs232_init(uint8_t port, uint32_t baudrate);
void rs232_write(uint8_t port, const char* data);
int rs232_read(uint8_t port, char* buffer, uint16_t maxLength);

#endif // RS232_MODULE_H
