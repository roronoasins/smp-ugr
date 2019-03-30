#include "tarjeta.h"

void avanzar() {
   M1_H();
   M2_H();
}

void main() {
   while(1) {
         if(!IN1|| !IN2) {
            delay_ms(100);
            avanzar();
      }
   }

}
