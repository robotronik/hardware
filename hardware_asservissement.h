#ifndef HARDWARE_H
#define HARDWARE_H

// Init
void init_hardware();

// Moteurs
void set_PWM_moteur_D(int PWM);
void set_PWM_moteur_G(int PWM);
void motors_stop();

// Codeurs
long int get_nbr_tick_D();
long int get_nbr_tick_G();

// Timer. Pas vraiment hw ?
void attente_synchro();

// Led de débug
void allumer_del();
void eteindre_del();

#endif
