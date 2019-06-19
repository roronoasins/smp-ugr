#include "tarjeta.h"

#use delay (clock=48MHz)

void main() {

while(1){
   if(!IN2)
      led_off();
   else{
      led_on();
   }
   
   
}

}
