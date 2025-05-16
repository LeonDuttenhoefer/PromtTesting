#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <sys/printk.h>
#include <power/power.h>

#define STACK_SIZE 1024
#define MSGQ_MAX_MSGS 10
#define MSG_SIZE sizeof(uint32_t)

K_THREAD_STACK_DEFINE(zephyr_stack_area, STACK_SIZE);
static struct k_thread zephyr_thread_data;
static struct k_msgq zephyr_msgq;
K_MSGQ_DEFINE(zephyr_msgq, MSG_SIZE, MSGQ_MAX_MSGS, 4);

static struct k_timer zephyr_timer;

static void zephyr_thread(void *p1, void *p2, void *p3) {
    uint32_t msg;
    while (1) {
        if (k_msgq_get(&zephyr_msgq, &msg, K_FOREVER) == 0) {
            printk("Received msg: %u\n", msg);
        }
    }
}

static void zephyr_timer_handler(struct k_timer *timer_id) {
    uint32_t msg = 42;
    k_msgq_put(&zephyr_msgq, &msg, K_NO_WAIT);
}

static void zephyr_pm_notify(enum pm_state state) {
    printk("Power state change: %d\n", state);
}

void zephyr_module_init(void) {
    k_timer_init(&zephyr_timer, zephyr_timer_handler, NULL);
    k_timer_start(&zephyr_timer, K_SECONDS(1), K_SECONDS(1));

    k_thread_create(&zephyr_thread_data, zephyr_stack_area,
                    K_THREAD_STACK_SIZEOF(zephyr_stack_area),
                    zephyr_thread, NULL, NULL, NULL,
                    5, 0, K_NO_WAIT);

    pm_power_state_force(0, PM_STATE_ACTIVE);
}