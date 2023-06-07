#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <string.h>

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "motor.h"

int point(){
    uint8_t data;
    char target[3];
    int int_target = 0;
    int index = 0;
    while(1)
    {
        data = UART1_Read();
        if(data == 44){ // data == ","
            int_target = atoi(target);
            if (int_target<=180){
                int angle = 180 - int_target;
                rotation_moteur_antihoraire(angle);
                __delay_ms(8000);
                rotation_moteur_horaire(angle);
            }else{
                int angle = int_target - 180;
                rotation_moteur_horaire(angle);
                __delay_ms(8000);
                rotation_moteur_antihoraire(angle);
            }


            return 1;
            }else{
            target[index] = (char)data;
            index += 1;
        }

    }
}

void main(void)
{
    SYSTEM_Initialize();
    while(1){
        point();
    }
}
