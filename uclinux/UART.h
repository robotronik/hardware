#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

int arret();
int UART_getc(unsigned char *c);
void UART_send_message(char *msg, unsigned int nb_char);
void * fake_RX();
void init_UART();
void append_to_UART(unsigned char c);

#ifdef __cplusplus
}
#endif

#endif
