
#include <p33FJ128MC802.h>
#include "moteurs.h"

/*******************************************************************************
 * Init du registre et des variables
 */

_FOSCSEL(FNOSC_FRCPLL & IESO_ON)
_FOSC(FCKSM_CSECMD & IOL1WAY_ON & OSCIOFNC_ON & POSCMD_NONE)
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS32768)

void init_osc() {
    // Init de la PLL : 7,37 -> 79,23 MHz !!!
    CLKDIVbits.PLLPRE = 0;      // (FRC) /2
    PLLFBD = 41;                // (FRC/2) *43
    CLKDIVbits.PLLPOST = 0;     // (FRC/2*43) /2

    __builtin_write_OSCCONH((OSCCONH | 1 )& 0xF9);  // Choix de l'horloge FRC avec PLL
    __builtin_write_OSCCONL(OSCCONL | 1);       // Changement d'horloge
    //while (!OSCCONbits.LOCK); // Attend le bloquage de la PLL (debug)

    while (OSCCONbits.OSWEN){;} // Attend le changement
}

void init_io() {
    // "All port pins are defined as inputs after a Reset"

    // Reglage du PORTA
    //_TRISA0 = 1;  // MOTOR_LEFT_CURRENT
    //_TRISA1 = 1;
    //_TRISA2 = 1;  // MOTOR_SF

    // Reglage du PORTB
    //U1MODEbits.UARTEN = 0b0; // UART déconnecté
    //_TRISB2 = 0;
    _TRISB3 = 1;

    _TRISB4 = 0;    // Motor_enable
    _RB4 = 1;
    pause_ms(1);
    _TRISB5 = 0;    // DEL en mode output
    _RB5 = 1;       // On eteint la DEL par defaut
    //_TRISB6 = 1;  // Coder right B
    //_TRISB7 = 1;  // Coder right A
    //_TRISB10 = 1; // Coder left B
    //_TRISB11 = 1; // Coder left A

    _TRISB12 = 0;   // MOTEUR IN1 right
    _RB12 = 0;      // PWM en IO général si non-utilisé (au moins 2 broches sur 4)
    _TRISB13 = 0;   // MOTEUR IN2 right
    _RB13 = 0;
    _TRISB14 = 0;   // MOTEUR IN1 left
    _RB14 = 0;
    _TRISB15 = 0;   // MOTEUR IN2 left
    _RB15 = 0;
}


void init_hardware() {
    init_osc    ();
    init_io     ();

    init_synchro();
    init_UART   ();

    init_moteurs();
    init_codeurs();
}



void init_timer2() {
    /********************************************
     * Initialisation du timer de blocage 16bit
     * Euh………… Utile ?
     */

    T2CONbits.TON = 0;      //On stop le timer

    T2CONbits.TSIDL = 1;
    T2CONbits.TGATE  = 0 ;
    T2CONbits.TCKPS = 0b11; //Prescaller 64

    TMR2 = 0;

    PR2 = 12438; //Timer de 10ms

    T2CONbits.TCS = 0;      // Horloge interne

    T2CONbits.T32 = 0;      // Timer 16bits

    IPC1bits.T2IP = 0x01;   // Set Timer1 Interrupt Priority Level
    IFS0bits.T2IF = 0;      // Clear Timer1 Interrupt Flag
    IEC0bits.T2IE = 1;      // Enable interupt
}
