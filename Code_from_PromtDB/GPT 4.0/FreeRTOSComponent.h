#ifndef FREERTOS_COMPONENT_H
#define FREERTOS_COMPONENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void FreeRTOSComponent_Init(void);
void FreeRTOSComponent_ISR_Handler(void);

#ifdef __cplusplus
}
#endif

#endif