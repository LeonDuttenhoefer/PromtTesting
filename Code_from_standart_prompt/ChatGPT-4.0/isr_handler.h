#ifndef ISR_HANDLER_H
#define ISR_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile bool isr_flag;

void EXTI0_IRQHandler(void); // Example for external interrupt line 0

#ifdef __cplusplus
}
#endif

#endif // ISR_HANDLER_H
