#include "freertos_component.h"
#include <stdio.h>

// Example task implementation
void vTaskExample(void *pvParameters) {
    while (1) {
        // Replace with application-specific code
        printf("Example FreeRTOS task running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Function to create and start the task
void vStartFreeRTOSComponent(void) {
    xTaskCreate(vTaskExample, "ExampleTask", configMINIMAL_STACK_SIZE + 100, NULL, tskIDLE_PRIORITY + 1, NULL);
}
