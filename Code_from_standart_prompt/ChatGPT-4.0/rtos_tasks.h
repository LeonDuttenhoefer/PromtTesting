#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#include "cmsis_os2.h"

void StartDefaultTask(void *argument);

void MX_RTOS_Init(void);

#endif // RTOS_TASKS_H
