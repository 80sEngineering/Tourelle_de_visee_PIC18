#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdlib.h>   


#endif

#include "motor.h"
#include "pins.h"
#include "clock.h"
 
void rotation_moteur_horaire(int degres){
    double incrementation =  degres * 1.4222;
    
    for (int i =0; i<incrementation; i++){
        
        STEP1 = 1;
        STEP2 = 0;
        STEP3 = 0;
        STEP4 = 1;
        __delay_ms(1);



         STEP1 = 0;
        STEP2 = 0;
        STEP3 = 0;
        STEP4 = 1;
        __delay_ms(1);



        STEP1 = 0;
        STEP2 = 0;
        STEP3 = 1;
        STEP4 = 1;
        __delay_ms(1);



        STEP1 = 0;
        STEP2 = 0;
        STEP3 = 1;
        STEP4 = 0;
        __delay_ms(1);



        STEP1 = 0;
        STEP2 = 1;
        STEP3 = 1;
        STEP4 = 0;
        __delay_ms(1);



        STEP1 = 0;
        STEP2 = 1;
        STEP3 = 0;
        STEP4 = 0;
        __delay_ms(1);



        STEP1 = 1;
        STEP2 = 1;
        STEP3 = 0;
        STEP4 = 0;
        __delay_ms(1);



        STEP1 = 1;
        STEP2 = 0;
        STEP3 = 0;
        STEP4 = 0;
        __delay_ms(1);
         }
}




void rotation_moteur_antihoraire(int degres){
        double incrementation =  degres * 1.4222;
        for (int i =0; i<incrementation; i++){

            STEP1 = 1;
            STEP2 = 0;
            STEP3 = 0;
            STEP4 = 0;
            __delay_ms(1);

            STEP1 = 1;
            STEP2 = 1;
            STEP3 = 0;
            STEP4 = 0;
           __delay_ms(1);



            STEP1 = 0;
            STEP2 = 1;
            STEP3 = 0;
            STEP4 = 0;
            __delay_ms(1);

            STEP1 = 0;
            STEP2 = 1;
            STEP3 = 1;
            STEP4 = 0;
            __delay_ms(1);

            STEP1 = 0;
            STEP2 = 0;
            STEP3 = 1;
            STEP4 = 0;
            __delay_ms(1);

            STEP1 = 0;
            STEP2 = 0;
            STEP3 = 1;
            STEP4 = 1;
            __delay_ms(1);

            STEP1 = 0;
            STEP2 = 0;
            STEP3 = 0;
            STEP4 = 1;
            __delay_ms(1);

            STEP1 = 1;
            STEP2 = 0;
            STEP3 = 0;
            STEP4 = 1;
            __delay_ms(1);
       }
}
