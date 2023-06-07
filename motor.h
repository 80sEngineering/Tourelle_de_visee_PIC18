#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "pins.h"

void rotation_moteur_horaire(int degres);
void rotation_moteur_antihoraire(int degres);