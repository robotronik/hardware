
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

    __builtin_write_OSCCONH((OSCCONH | 1) & 0xF9);  // Choix de l'horloge FRC avec PLL
    __builtin_write_OSCCONL (OSCCONL | 1);          // Changement d'horloge

    //while (!OSCCONbits.LOCK); // Attend le bloquage de la PLL (debug)

    while (OSCCONbits.OSWEN){;} // Attend le changement
}

void init_io() {
    _TRISB3 = 1;

    _TRISB4 = 0;    // Motor_enable
       _RB4 = 1;

    pause_ms(1);
    _TRISB5 = 0;    // DEL en mode output
       _RB5 = 1;    // On éteint la DEL par defaut

    _TRISB12 = 0;   // MOTEUR IN1 right
       _RB12 = 0;   // PWM en IO général si non-utilisé (au moins 2 broches sur 4)
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
