#include "FreeRTOSComponent.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#define STACK_SIZE 256
#define QUEUE_LENGTH 10

static StaticTask_t mainTaskTCB;
static StackType_t mainTaskStack[STACK_SIZE];

static TaskHandle_t mainTaskHandle = NULL;

static StaticQueue_t queueBuffer;
static uint8_t queueStorageArea[QUEUE_LENGTH * sizeof(uint32_t)];
static QueueHandle_t messageQueue = NULL;

static StaticSemaphore_t mutexBuffer;
static SemaphoreHandle_t resourceMutex = NULL;

static StaticTimer_t timerBuffer;
static TimerHandle_t softwareTimer = NULL;

static void MainTask(void* parameters);
static void TimerCallback(TimerHandle_t xTimer);

void FreeRTOSComponent_Init(void) {
    messageQueue = xQueueCreateStatic(QUEUE_LENGTH, sizeof(uint32_t), queueStorageArea, &queueBuffer);
    resourceMutex = xSemaphoreCreateMutexStatic(&mutexBuffer);
    softwareTimer = xTimerCreateStatic("SoftTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, TimerCallback, &timerBuffer);

    mainTaskHandle = xTaskCreateStatic(MainTask, "MainTask", STACK_SIZE, NULL, 2, mainTaskStack, &mainTaskTCB);

    xTimerStart(softwareTimer, 0);
}

static void MainTask(void* parameters) {
    uint32_t receivedValue;

    for (;;) {
        if (xQueueReceive(messageQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            if (xSemaphoreTake(resourceMutex, portMAX_DELAY) == pdPASS) {
                xSemaphoreGive(resourceMutex);
            }
        }
    }
}

static void TimerCallback(TimerHandle_t xTimer) {
    uint32_t timerMessage = 123;
    xQueueSendFromISR(messageQueue, &timerMessage, NULL);
}

void FreeRTOSComponent_ISR_Handler(void) {
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(mainTaskHandle, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}