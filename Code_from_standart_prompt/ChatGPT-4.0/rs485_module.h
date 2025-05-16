#ifndef RS485_MODULE_H
#define RS485_MODULE_H

#include <stdint.h>

void rs485_init(uint8_t port, uint32_t baudrate);
void rs485_write(uint8_t port, const char* data);
int rs485_read(uint8_t port, char* buffer, uint16_t maxLength);
void rs485_set_transmit_mode(uint8_t port);
void rs485_set_receive_mode(uint8_t port);

#endif // RS485_MODULE_H
