#include "tarjeta.h"
#use delay (clock=48MHz)
#include "srf02.h"

int pwm=0;
int wx=0;

#INT_TIMER0
void int_tmr0() {
   
   if(wx <= pwm)
      led_on();
   else
      led_off();
      
   wx++;
}

void main() {

   setup_timer_0(RTCC_INTERNAL| RTCC_DIV_2 |RTCC_8_BIT);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   unsigned int16 m;
 /*  
   set_tris_a(0x00);
   set_tris_b(0x13);
   set_tris_c(0x00);
   set_tris_d(0x1F);
   set_tris_e(0x00);
 */  


   while(1) {
   
     if(P2)   
      {
         pwm+=35;
         delay_ms(100);
       }
      
   m = srf_measure_cm();
   
   if(m > 16 && m < 30) {
      pwm = 32;
   }else if(m > 30 && m < 60) {
      pwm = 100;
      }else if(m > 60 && m < 120) {
      pwm = 200;
      }else if ( m > 120)  pwm = 255;
   
   delay_ms(500);
   }

   
}

