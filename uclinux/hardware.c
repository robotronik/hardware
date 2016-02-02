#include <stdio.h>

#include "UART.h"
#include "asservissement.h"
#include "hardware.h"

void __attribute__((weak)) dessine_point_passage_carto  (void* null) { }
void __attribute__((weak)) dessine_obstacle_rond        (void* null) { }
void __attribute__((weak)) dessine_obstacle_ligne       (void* null) { }
