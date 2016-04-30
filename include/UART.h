#ifndef HARDWARE_UART_H
#define HARDWARE_UART_H

// En fait, il faudrait un header indépendant de la techno (UART,…)

//int UART_getc(unsigned char *c);
void UART_send_message(char *msg, unsigned int nb_char);


#endif
