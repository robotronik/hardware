
#include "moteurs.h"
#include "dividedLong.h"

/*----------------------------------------------------------------*
 * génération des PWMs de commande des moteurs                    *
 *----------------------------------------------------------------*/
void set_PWM_moteur_D(int PWM) {
    short negatif = (PWM < 0);

    short speedR  = (short) (MAX_SPEED * abs(PWM)) / 1000; 


    if (speedR == 0) {
        PWM1CON1bits.PEN2H = 0;
        PWM1CON1bits.PEN2L = 0;
        return;
    }

    PWM1CON1bits.PEN2H = !negatif;
    PWM1CON1bits.PEN2L =  negatif;

    if (speedR >= MAX_SPEED)
        P1DC2 = MAX_SPEED;
    else
        P1DC2 = speedR;
}

void set_PWM_moteur_G(int PWM) {
    short negatif = (PWM < 0);

    short speedL  = (short) (MAX_SPEED * abs(PWM)) / 1000; 


    if (speedL == 0) {
        PWM1CON1bits.PEN1H = 0;
        PWM1CON1bits.PEN1L = 0;
        return;
    }

    PWM1CON1bits.PEN1H = !negatif;
    PWM1CON1bits.PEN1L =  negatif;

    if (speedL >= MAX_SPEED)
        P1DC1 = MAX_SPEED;
    else
        P1DC1 = speedL;
}

void moteurs_stop() {
    // On met les 4 sorties en logique
    PWM1CON1bits.PEN1H = 0;
    PWM1CON1bits.PEN2H = 0;
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
}

void init_moteurs() {
    P1TPER = MAX_SPEED/2;       // Période du timer
    P1DC1 = 0;                  // Duty-cycle PWM1H1 = 0%
    P1DC2 = 0;                  // Duty-cycle PWM1H2 = 0%

    PWM1CON1bits.PMOD1 = 1;
    PWM1CON1bits.PMOD2 = 1;

    P1TCONbits.PTEN = 1;        // Active le Timer des PWMs
    P1TCONbits.PTOPS = 5-1;     // Reset automatique aux modif de P1TCON
    //P1TCONbits.PTSIDL = 1;    // Arrêt en pause

    moteurs_stop();
}