#include "tarjeta.h"

#use delay (clock=48MHz)

int contador = 0;
int encendido = 0;

#INT_TIMER0
void int_tmr0() {
   set_timer0(18661);
   if(encendido) {
      led_off();
      encendido -= 1;
   }else{
         led_on();
         encendido += 1;
   }
}

void main() {
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   set_timer0(18661);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
while(1){
   
}


}
