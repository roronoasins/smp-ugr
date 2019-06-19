#include "tarjeta.h"
#use delay (clock=48MHz)

#define PCF_W 0x90
#define PCF_R 0x91

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

      
      i2c_start();
      i2c_write(PCF_W);
      i2c_write(0x00);     //Byte de control
      i2c_stop();
   
   while(1) {
      i2c_start();
      i2c_write(PCF_R);
      i2c_read();          //Leo el dato de la última conversión anterior
      m = i2c_read();    //Leo el dato de la conversión del canal 0
      m = i2c_read(0);    //Leo el dato de la conversión del canal 0
      i2c_stop();
      
      
      //if (m == 0xFF) //((m > 51) && (m <= 102))
      if (input(ES8))
         pwm = 255;
      else pwm = 0;
      
      delay_ms(500);
   }

   
}

