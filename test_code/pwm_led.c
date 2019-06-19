#include "tarjeta.h"

int pwm = 10;
int wx = 0;

void main() {

while(1){
   if(P2) {
   while(P2){}
      pwm += 20;
   }
   if(wx <= pwm)
      led_on();
   else
      led_off();
   wx++;
}

}
