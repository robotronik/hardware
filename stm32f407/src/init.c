#include "init.h"

void init() {
    // ---------- SysTick timer -------- //
    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Capture error
        while (1){};
    }
}

void init_hardware() {
    init();
    init_GPIO_LED();
}
