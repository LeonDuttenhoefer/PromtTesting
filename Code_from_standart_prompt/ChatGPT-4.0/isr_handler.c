#include "isr_handler.h"

// Global flag set by ISR
volatile bool isr_flag = false;

// Example ISR for external interrupt line 0
void EXTI0_IRQHandler(void) {
    // Clear interrupt pending bit (platform-specific, e.g., EXTI->PR = ...)
    // Example pseudocode:
    // EXTI->PR = (1 << 0); // clear pending bit for line 0

    isr_flag = true;
}
