#ifndef CAN_MODULE_H
#define CAN_MODULE_H

#include <stdint.h>

typedef struct {
    uint32_t id;
    uint8_t data[8];
    uint8_t length;
} can_message_t;

void can_init(uint8_t can_port, uint32_t baudrate);
int can_send(uint8_t can_port, const can_message_t* msg);
int can_receive(uint8_t can_port, can_message_t* msg);

#endif // CAN_MODULE_H
