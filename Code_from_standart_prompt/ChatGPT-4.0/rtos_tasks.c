#include "rtos_tasks.h"
#include "cmsis_os2.h"

// Define task attributes
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128 * 4
};

// Task handle
osThreadId_t defaultTaskHandle;

// Task implementation
void StartDefaultTask(void *argument) {
    for (;;) {
        // Example: toggle an LED or delay
        // HAL_GPIO_TogglePin(GPIOx, GPIO_PIN_y);
        osDelay(1000);
    }
}

// RTOS Initialization
void MX_RTOS_Init(void) {
    osKernelInitialize(); // Initialize RTOS kernel
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    osKernelStart(); // Start thread execution
}
