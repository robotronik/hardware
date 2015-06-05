/*----------------------------------------------------------------*
 * Timer pour la synchronisation de asser()                       *
 *----------------------------------------------------------------*/

int doitAttendre=1;

void reset_synchro() {
    doitAttendre=1;
}

void attente_synchro() {
    /* Si il ne faut pas attendre cela veut dire que la fréquence de synchro
     * est trop rapide par rapport au temps nécessaire à la boucle principale.
     * On le signale donc en allumant la led de débug.
     */
    //TODO Envoyer l'erreur rencontrée par UART
    //TODO allumer_del() ne doit PAS être appelé en match
    if (!doitAttendre) {
        allumer_del();
    }

    // boucle d'attente
    while(doitAttendre){;}
    // On "redémarre" la synchro pour la prochaine boucle
    reset_synchro();
}

void init_synchro() {
    /********************************************
     * Initialisation de la période de l'asser
     */
    T1CONbits.TSIDL = 1;
    T1CONbits.TGATE  = 0 ;
    T1CONbits.TCKPS = 0b11; // Prescaller 256

    TMR1 = 0;   //Reset du compteur

    PR1 = 100;  //250; //Réglage de la fréquence de l'horloge. (Fctimer = (40Mhz/256))

    T1CONbits.TCS = 0;

    IPC0bits.T1IP = 0x01;   // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0;      // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1;      // Enable interupt

    T1CONbits.TON = 1;      // Début du timer
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt() {
    doitAttendre = 0;
    IFS0bits.T1IF = 0;
    TMR1 = 0;
}

