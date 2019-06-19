#include "tarjeta.h"

int pwm=2;
int pwm2=32;
int wx = 0;
//Se puede mejorar aumentando el prescaler y asi sobrecargar menos el micro ejecutando menos veces la int_timer0
//Si debe ser muy precisa elegir el que menos difiera del tdesb deseado
#use delay (clock=48MHz)
int encendido = 0;

#INT_TIMER0
void int_tmr0() {
   set_timer0(0);
    if(P2) {
       while(P2){}
      pwm *= 4;
   }
   if(wx <= pwm)
      led_on();
   else
      led_off();
   if(wx <= pwm2)
      output_high(PIN_C0);
   else
      output_low(PIN_C0);
   wx++;
}

void main() {
   setup_timer_0(RTCC_INTERNAL  | RTCC_8_BIT);
   set_timer0(0);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
while(1) {}


}
