#include "tarjeta.h"

int h=1, a=0;
int pwm=32;
int wx=0;

#use delay (clock=48MHz)

#INT_TIMER0
void int_tmr0() {
   
   if(wx <= pwm)
      M1_H();
   else
      M1_P();

      
   wx++;
}

void main() {

   setup_timer_0(RTCC_INTERNAL| RTCC_DIV_2 |RTCC_8_BIT);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(1) {
    /*  if(IN1) {
         delay_ms(100);
         if(IN1){
            pwm += 20;
            while(IN1){}
         }
      }*/
      
      if (IN1){
         pwm+=35;
         delay_ms(100);
      }
      
   }

}
