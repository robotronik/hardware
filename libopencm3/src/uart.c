#include <specific.h>

static void console_putc(int usart_can, char c) {
    uint32_t    reg;
    do {
        reg = USART_SR(usart_can);
    } while ((reg & USART_SR_TXE) == 0);
    USART_DR(usart_can) = (uint16_t) c & 0xff;
}

void console_puts(int usart_can, char * buff, uint8_t buff_len) {
    for (int i = 0; i < buff_len; ++i) {
        console_putc(usart_can, *buff);
        buff++;
    }
}
