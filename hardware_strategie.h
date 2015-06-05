/* En gros, un fichier générique d'"interfaçage hardware". L'idée est que ce soit
 * le seul fichier qu'on ait besoin d'inclure dans stratégie, etc.
 */

// Il faudra inclure les headers nécessaires pour les types.

#include "hardware_common.h"
#include "hardware_UART.h"

// Tous les inits "généraux"
int init_GPIO();
int init_GPIO_LED();
int init_RTC();     // Donner un nom plus explicite (c'est bien pour les timers ?)
int init_PWM_In();


// Accès aux pins
int pin_init(e_Pin_Port, e_Pin_Pin, mode, sens); // je connais pas les types et pour le moment c'est irrelevant
int pin_get_state(e_Pin_Port, e_Pin_Pin);
// Interruptions sur pins ?
int pin_IT_init(e_Pin_Port, e_Pin_Pin);
int pin_IT_callback(e_Pin_Port, e_Pin_Pin);


// Leds (Débug essentiellement)
int led_set     (e_LED led, e_PIN_STATE state);
int led_toggle  (e_LED led);
int leds_spin   ();
int leds_set_all(e_PIN_STATE state);



// Timers
int timer_init  (int lequel); // Plus un argument du type "i-ième timer" si on en a besoin de plusieurs
int timer_start (int lequel, int temps_ms);
//int set_timer   (int lequel, int temps_ms);
//int start_timer (int lequel); // Ptêt pas nécessaire
// le i-ième timer peut être géré par un e_TIMER non ?


// Capteurs US
int US_Sensor_init_all();
int US_Sensor_init      (US_Sensor);
int US_Sensor_enable    (US_Sensor);
int US_Sensor_disable   (US_Sensor);

int adversaire_detecte_callback(US_Sensor, int distance); // Pas sûr du param distance (tout-ou-rien)


// Servos
int servo_init(Servo_t*, GPIO_TypeDef*, uint16_t, Servo*);
    // Probab' difficile de faire mieux :(
    // Ici on donne l'adresse du Servo qu'on va utiliser pour les autres méthodes
// int init_servo(e_Servo); // Le problème c'est que c'est spécifique au petit ou gros
int servo_set_pos(Servo, int angle);
int servo_get_pos(Servo);



// Moteurs
int moteur_init(e_Moteur);
int moteur_set_PWM(e_Moteur, int vitesse); // Définir l'unité de vitesse. Le signe définit le sens.
int moteur_stop(e_Moteur);



