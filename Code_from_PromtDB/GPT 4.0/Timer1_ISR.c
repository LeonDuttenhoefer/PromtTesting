#include <stdint.h>
#include <stdbool.h>

#define TIMER1_IRQ_PRIORITY 3
#define SHARED_BUFFER_SIZE 64

volatile uint8_t sharedBuffer[SHARED_BUFFER_SIZE];
extern void onTimerElapsed(void);
extern void logISRStart(void);
extern void logISREnd(void);
extern void testHook_Timer1ISR(void);

void Timer1_ISR(void) __attribute__((interrupt("IRQ")));
void Timer1_ISR(void) {
    logISRStart();

    bool error = false;

    if ((TIMER1_STATUS_REG & TIMER1_EDGE_FLAG) == 0) {
        error = true;
    }

    if (!error) {
        for (uint8_t i = 0; i < SHARED_BUFFER_SIZE; ++i) {
            sharedBuffer[i] = 0;
        }

        onTimerElapsed();
        testHook_Timer1ISR();
    }

    TIMER1_CLEAR_FLAG();

    logISREnd();
}

/* ISR API:
 * Function: Timer1_ISR
 * Description: Handles Timer1 edge-triggered interrupt.
 * - Clears interrupt flag
 * - Verifies edge trigger status
 * - Resets shared buffer
 * - Calls user callback onTimerElapsed
 * - Executes test and profiling hooks
 * Constraints:
 * - Must complete in under 10µs
 * - Uses no dynamic memory
 * - Priority level 3 with preemption enabled
 */