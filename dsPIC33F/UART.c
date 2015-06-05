////////////////////////////////////////////////////////////////////////////////
// UART

#define RX_BUFFER_SIZE 40
#define TX_BUFFER_SIZE 40

static unsigned char rxBuffer[RX_BUFFER_SIZE];
unsigned short rxBufferDebut, rxBufferFin;

static unsigned char txBuffer[TX_BUFFER_SIZE];
static unsigned short txBufferDebut, txBufferFin;

int init_UART() {
    // initialisation des variables globales
    rxBufferDebut   = 0;
    rxBufferFin     = 0;
    txBufferDebut   = 0;
    txBufferFin     = 0;

    AD1PCFGLbits.PCFG5  = 1;    // Désactivation de l'entrée analogique !!!
    RPOR1bits.RP2R      = 3;    //        Tx1 -> RP2
    RPINR18bits.U1RXR   = 3;    // RP3 -> Rx1

    //U1MODEbits.LPBACK = 1;// Debug : Tx1 -> Rx1

    // Low speed : BRG = 79,23 MHz / 32 / Baudrate - 1
    U1MODEbits.BRGH = 1;    // High speed : BRG = 79,23 MHz / 8 / Baudrate - 1
    U1BRG = 85;             // BAUD Rate Setting for 115200 gives 115160 bauds

    U1STAbits.UTXISEL1 = 1; // Interrupt on empty FIFO, last byte is being sent
    U1STAbits.UTXISEL0 = 0; //                      "

    IFS0bits.U1RXIF = 0;    // On évite des interruptions à l'activation
    IEC0bits.U1RXIE = 1;    // Activation de l'interruption sur réceptions
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE = 1;    // Activation de l'interruption sur l'envoi
    // IFS4bits.U1EIF = 0;
    // IEC4bits.U1EIE = 1;     // Activation de l'interruption sur erreurs

    U1MODEbits.UARTEN = 1;  // Enable UART
    U1STAbits.UTXEN = 1;    // Enable UART TX
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Fonctions d'envoi

int UART_putc(unsigned char c) {
    /*while (U1STAbits.UTXBF);*/
    txBuffer[txBufferFin] = c;
    txBufferFin = (txBufferFin + 1) % TX_BUFFER_SIZE;

    // On déclenche l'interruption correspondant au début d'écriture sur tx
    // voir la fonction _U1TXInterrupt()
    IFS0bits.U1TXIF = 1;
    return 0;
}

int UART_puts(unsigned char* msg) {
    char *actuel = msg;
    while (*actuel)
        UART_putc(*actuel++);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Fonction de réception


int UART_getc(unsigned char *c) {
    if (rxBufferDebut == rxBufferFin) {
        // Il n'y avait pas de caractères en attente
        return false;
    } else {
        // Il y des caractères à traiter
        *c = rxBuffer[rxBufferDebut];
        rxBufferDebut = (rxBufferDebut + 1) % RX_BUFFER_SIZE;
        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Interruptions

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt() {
    // On s'acquitte de l'interruption
    IFS0bits.U1RXIF = 0;

    if(U1STAbits.FERR == 1) { // Erreurs ?
        return;
    }
    /* must clear the overrun error to keep uart receiving */
    if(U1STAbits.OERR == 1) {
        U1STAbits.OERR = 0;
        return;
    }

    // Attention, il ne faut accéder UNE SEULE fois au registre U1RXREG
    if(U1STAbits.URXDA == 1) {
        rxBuffer[rxBufferFin] = U1RXREG;
        rxBufferFin = (rxBufferFin + 1) % RX_BUFFER_SIZE;
    }
}

void __attribute__((interrupt, auto_psv)) _U1ErrInterrupt() {
    IFS4bits.U1EIF = 0; // On s'acquitte de l'interruption
    if(U1STAbits.FERR == 1) // Erreurs ?
        return ;
    // must clear the overrun error to keep uart receiving
    if(U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
}

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt() {
    IFS0bits.U1TXIF = 0; // On s'acquitte de l'interruption

    if(U1STAbits.FERR == 1) // Erreurs ?
        return;
    // must clear the overrun error to keep uart receiving
    if(U1STAbits.OERR == 1)     {
        U1STAbits.OERR = 0;
        return;
    }

    if(txBufferFin != txBufferDebut) {
        // Si le buffer du module n'est pas vide
        // on attends que le l'émission soit prête
        while (U1STAbits.UTXBF);

        U1TXREG = txBuffer[txBufferDebut];
        txBufferDebut = (txBufferDebut + 1) % TX_BUFFER_SIZE;
    }
}
