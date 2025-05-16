#include "zephyr_module.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define ZEPHYR_MODULE_STACK_SIZE 512
#define ZEPHYR_MODULE_PRIORITY 5

K_THREAD_STACK_DEFINE(zephyr_module_stack, ZEPHYR_MODULE_STACK_SIZE);
static struct k_thread zephyr_module_thread;

static void zephyr_module_thread_func(void *arg1, void *arg2, void *arg3) {
    while (1) {
        printk("Zephyr module is running\n");
        k_sleep(K_SECONDS(1));
    }
}

void zephyr_module_start(void) {
    k_thread_create(&zephyr_module_thread, zephyr_module_stack,
                    K_THREAD_STACK_SIZEOF(zephyr_module_stack),
                    zephyr_module_thread_func,
                    NULL, NULL, NULL,
                    ZEPHYR_MODULE_PRIORITY, 0, K_NO_WAIT);
}
