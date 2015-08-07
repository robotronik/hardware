#ifndef __US_SENSOR_H__
#define __US_SENSOR_H__

#include "stm32f4xx_hal_conf.h"
#include "utilities.h"

#define NB_VALEURS_LISSAGE 5
#define LIMIT_RANGE 900

#define ADVERSAIRE_NON_DETECTE 1694
#define ADVERSAIRE_DETECTE 1695
#define ATTENTE_FIN_DETECTION 6248

void activate_sensor1();
void activate_sensor2();
void desactivate_sensor1();
void desactivate_sensor2();
void init_sensor1();
void init_sensor2();

void init_sensors();

void adversaire_detecte_callback();

#endif
