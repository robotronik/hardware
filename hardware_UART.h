// UART
int UART_init(e_UART_Channel);   // Avec des wrappers pour Asser et XBee ?
int UART_putc(e_UART_Channel, unsigned char); // ou bien : (mieux non ?)
int UART_puts(e_UART_Channel, unsigned char*);
// et pour la réception :
int UART_getc(e_UART_Channel, unsigned char);
