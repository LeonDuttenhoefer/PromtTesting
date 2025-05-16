#ifndef FREERTOS_COMPONENT_H
#define FREERTOS_COMPONENT_H

#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

void vTaskExample(void *pvParameters);
void vStartFreeRTOSComponent(void);

#ifdef __cplusplus
}
#endif

#endif // FREERTOS_COMPONENT_H
