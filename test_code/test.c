#include "tarjeta.h"

#use delay (clock=48MHz)
#include "srf02.h"

/*
 * M1 -> motor derecho
 * M2 -> motor izquierdo
 * IN1 -> bumper derecho
 * IN2 -> CNY70 trasero izquierdo
 * IN3 -> CNY70 delantero derecho
 * IN4 -> CNY70 delantero izquierdo
 * IN5 -> bumper izquierdo
 * IN6 -> configurable
 * SRF02_FW -> SRF02 frontal
 * SRF02_LW -> SRF02 izquierdo
 * SRF02_RW -> SRF02 derecho
 *
 */

// Infrarj detrasï¿½? derï¿½?


#define SRF02_RW 0xE2
//#define SRF02_FW 0xE4
#define SRF02_LW 0xE0

int16 duracion=0;
int frente=0, der=0, izq=0;
int pwm=150;int pwm2=128;
int wx=0;int wx2=0;
int var=0;
int choque=0;
int salir_e=0;
int no_salir=0;
int cont=0;
enum state {idle, explorar, maniobra, salir, acercarse, acercarse_izq, acercarse_der, empujar, empujar_der, empujar_izq}actual = idle;


#INT_TIMER0
void int_tmr0() {

   if(wx <= pwm)
   {
      switch(actual){
         case idle:
            M1_P();
            M2_P();
            break;

        case maniobra:
            if(duracion < 100)
            {
               M1_A();
               M2_A();
            }else
            {
               if(duracion < 160) // last 200
               {
                  M1_A();
                  M2_H();
               }else{
                  duracion = 0;
                  actual = explorar;
               }
            }
            break;

         case salir:
            if(duracion < 100)
            {
               M1_A();
               //M2_A();
            }else{wx2=0;duracion=0;actual=explorar;pwm=200;salir_e=0;}
            break;

        case explorar:
            M1_H();
            M2_H();
            break;

        case acercarse:
            M1_H();
            M2_H();
            break;

        case acercarse_izq:
            if(duracion < 100)
            {
               M1_H();
               M2_A();
            }else{actual = acercarse;pwm=200;}
            break;

        case acercarse_der:
            if(duracion < 100)
            {
               M1_A();
               M2_H();
            }else{actual = acercarse;pwm=200;}
            break;

        case empujar:
            M1_H();
            M2_H();
            break;

        case empujar_der:
            M1_P();
            M2_H();
            break;

        case empujar_izq:
            M1_H();
            M2_P();
            break;

        default:break;
      }
   }
   else
   {
      M1_P();
      M2_P();
   }

   if(actual == salir)
   {
     if(wx2 <= pwm2)
     {
         if(duracion < 200)
         {
            M2_A();
         }else{duracion=0;actual = explorar;salir_e=0;}

     }else
     {
       M2_P();
     }
     wx2++;
 }

   wx++;
   if (wx == 255) {duracion++;}
   //if(duracion > 10000) led_on();
}

void main()
{
   //delay_ms(3000);
   set_tris_a(0x00);
   set_tris_b(0x13);
   set_tris_c(0x00);
   set_tris_d(0x1F);
   set_tris_e(0x00);
   setup_timer_0(RTCC_INTERNAL| RTCC_DIV_2 |RTCC_8_BIT);
   actual=explorar;
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(!P2)
   {
     // si empuja fuera del tatami a rival, para poder volver pasando sobre la linea negra con sensores delanteros
     //if(actual == salir)  while((!IN3 || !IN4));
     // si al maniobrar pisa linea negra con sensores traseros
     /*while ((!IN2) && actual == maniobra)
     {
        duracion = 0;
        actual = explorar;
     }*/

      /*if ((!IN2) && (actual == explorar || actual == empujar || actual == empujar_der || actual == empujar_izq))
      {
         duracion = 0;
         actual = salir;
         salir_e = 1;

         //no_salir++;
         //led_on();
      }//else led_off();*/
      
      if(!IN2 && (actual == actual == empujar || actual == empujar_der || actual == empujar_izq))
      {
        duracion = 0;
        // pwm2 -> motor izquierdo
        // pwm -> motor derecho
        actual = salir;
        pwm = 20;
        pwm2 = 200;
      }

      if((!IN3 || !IN4) && (actual == empujar || actual == empujar_der || actual == empujar_izq))
      {
         //var++;
         //pwm=100;
         salir_e = 1;
         //while(!IN3 || !IN4);
         duracion = 0;
         actual = maniobra;
         //pwm=255;
      }


      if((!IN3 || !IN4) && (actual == explorar || actual == maniobra || actual == acercarse))
      {
         //var++;
         duracion = 0;
         actual = maniobra;
      }

      if((IN5 || IN1) && !salir_e) {
         //delay_ms(100);
         // Si los bumpers detectan se refleja en choque
         choque = 1;
         if(IN1 && !IN5) {duracion=0;actual = empujar_der;}
         else if(IN5 && !IN1) {duracion=0;actual = empujar_izq;}
               else {duracion=0;actual = empujar;}
         pwm = 230;
      }

      if( (actual == explorar || actual == maniobra || actual == idle) )
      {
         //frente = srf_measure_cm(SRF02_FW);
         der = srf_measure_cm(SRF02_RW);
         izq = srf_measure_cm(SRF02_LW);
         if(izq > 15 && izq < 30)
         {
            duracion = 0;
            actual = acercarse_izq;
            pwm = 230;
         }else if(der > 15 && der < 30)
                {
                 duracion = 0;
                 actual = acercarse_der;
                 pwm = 230;
                }
      }
    
      if(!IN5 && !IN1 && choque) {choque = 0;duracion = 0;pwm = 128;actual=explorar;}
      if(!IN5 && !IN1 && salir_e) {salir_e = 0;}
   }

}
