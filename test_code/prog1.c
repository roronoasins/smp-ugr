#include "tarjeta.h"

int pwm=32;
int wx=0;
enum estado {avanzar, g_izq, g_der, piv_izq, piv_der, parar, retroceder}actual=parar;
#use delay (clock=48MHz)

#INT_TIMER0
void int_tmr0() {
   
   if(wx <= pwm)
      switch(actual){
         case avanzar: 
            M1_H();
            M2_H();
            break;
         case g_izq: //sobre sí mismo
            M1_P();
            M2_A();
            break;
         case g_der: //sobre sí mismo
            M1_H();
            M2_A();
            break;
         case piv_izq:
            M1_H();
            M2_P();
            break;     
         case piv_der:
            M1_P();
            M2_H();
            break;
         case retroceder:
            M1_A();
            M2_A();
         //default:break;
         break;
      }
   else
   {
      M1_P();
      M2_P();
   }
      
   wx++;
}

void main() {

   setup_timer_0(RTCC_INTERNAL| RTCC_DIV_2 |RTCC_8_BIT);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(1) {
   
     if(P2)   
      {
         pwm+=35;
         delay_ms(100);
       }
       
    /* comportamiento lapa */
    /*
    if(!IN1|| !IN2) {
         delay_ms(100);
         if(!IN1 && IN2) actual = piv_der;
         else if(!IN2 && IN1) actual = piv_izq;
               else actual = avanzar;
      }else actual = parar;
      */
      
      /* sigue_linea v0 */
      if(IN3 || IN4) {
         delay_ms(50);
         if(IN3 && !IN4) actual = piv_izq;
         else if(IN4 && !IN3) actual = piv_der;
               else actual = avanzar;
      }else actual = parar;
   }

}
