#include "dividedLong.h"

/*----------------------------------------------------------------*
 * gestion des ticks effectués sur les roues codeuses             *
 *----------------------------------------------------------------*/
short distLHigh, distRHigh;

long get_nbr_tick_D()
{
    long PosR;
    long * pPosR = &PosR;
    ((T_dividedLong *) pPosR)->part.high = distRHigh;
    ((T_dividedLong *) pPosR)->part.low = POS2CNT;
    return PosR;
}

long get_nbr_tick_G()
{
    long PosL;
    long * pPosL=&PosL;
    ((T_dividedLong *) pPosL)->part.high = distLHigh;
    ((T_dividedLong *) pPosL)->part.low = POS1CNT;
    return PosL;
}

void reset_nbr_tick_G()
{
    POS1CNT = 0;
    distLHigh = 0;
}

void reset_nbr_tick_D()
{
    POS2CNT = 0;
    distRHigh = 0;
}

void init_codeurs() {
    // Initialise les codeurs en quadrature QEI1 et QEI2

    // Désactivation QEI avant configuration
    QEI1CONbits.QEIM   = 0b000;
    QEI2CONbits.QEIM   = 0b000;

    // Connection des modules QEI1 : LEFT et QEI2 : RIGHT aux pins RPx du PIC
    RPINR14bits.QEA1R  = 11;    // QEA1 sur RP11
    RPINR14bits.QEB1R  = 10;    // QEB1 sur RP10
    RPINR16bits.QEA2R  = 6;     // QEA2 sur RP6
    RPINR16bits.QEB2R  = 7;     // QEB2 sur RP7

    // Initialisation QEI1 (roue gauche)
    QEI1CONbits.QEISIDL = 1;    // Lors de la mise en pause le compteur s'arrete
    QEI1CONbits.SWPAB   = 1;     // A et B inversés
    DFLT1CONbits.CEID   = 1;     // Pas d'interruption sur erreur
    MAX1CNT = 65535;            // Valeur maximale du compteur

    // Initialisation QEI2 (roue droite)
    QEI2CONbits.QEISIDL = 1;
    QEI2CONbits.SWPAB   = 1;
    DFLT2CONbits.CEID   = 1;
    MAX2CNT = 65535;

    // Reset compteurs
    POS1CNT = 0;
    POS2CNT = 0;

    // Activation des interruptions sur débordement des compteurs
    IEC3bits.QEI1IE = 1;
    IEC4bits.QEI2IE = 1;

    // Activation QEI1 et QEI2
    QEI1CONbits.QEIM   = 0b111; // Mode 4x, reset et interruption sur MAXxCNT
    QEI2CONbits.QEIM   = 0b111;

    reset_nbr_tick_D();
    reset_nbr_tick_G();
}

void __attribute__((interrupt, auto_psv)) _QEI1Interrupt() {
    IFS3bits.QEI1IF = 0; // On s'acquitte de l'interruption
    if ((unsigned short) POS1CNT < 32768)
        distLHigh ++;
    else 
        distLHigh --;
}

void __attribute__((interrupt, auto_psv)) _QEI2Interrupt() {
    IFS4bits.QEI2IF = 0; // On s'acquitte de l'interruption
    if ((unsigned short) POS2CNT < 32768)
        distRHigh ++;
    else
        distRHigh --;
}

