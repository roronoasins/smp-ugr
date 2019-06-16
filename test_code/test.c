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


#define SRF02_FW 0xE2
#define SRF02_RW 0xE4
#define SRF02_LW 0xE0

int16 duracion=0;
int frente, der, izq;
int pwm=128;
int wx=0;
int var=0;
int choque=0;
int salir_e=0;
enum state {idle, primera_carga, explorar, maniobra, salir, sobre_linea, acercarse, empujar, empujar_der, empujar_izq}actual = idle;


#INT_TIMER0
void int_tmr0() {
   
   if(wx <= pwm)
   {
      switch(actual){
         case idle: 
            M1_P();
            M2_P(); 
            break;

         case primera_carga:
            M1_H();
            M2_H();
            break;
        case sobre_linea:
            
            break;
            
        case maniobra:
            if(duracion < 80)
            {
               M1_A();
               M2_A();
            }else 
            {
               if(duracion < 200)
               {
                  M1_A();
                  M2_H();
               }else{
                  duracion = 0;
                  actual = primera_carga;
               }
            }
            break;
            
         case salir:
            if(duracion < 50)
            {
               M1_H();
               M2_H();
            }else{actual = explorar;}
            break;
            
        case explorar:
            M1_H();
            M2_H();
            break;
            
        case acercarse:
            M1_H();
            M2_H();  
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
   actual=primera_carga;
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(!P2) 
   {
     // if(IN6)  led_on();
      if (!IN2)
      {
         duracion = 0;
         actual = salir;
         //salir_e = 1;
      } 
      if(!IN3 || !IN4)
      { 
         //var++;
         duracion = 0;
         actual = maniobra;
      }
      
      /*if(IN5 || IN1) {
         //delay_ms(100);
         // Si los bumpers detectan se refleja en choque
         choque = 1;
         if(IN1 && !IN5) actual = empujar_der;
         else if(IN5 && !IN1) actual = empujar_izq;
               else actual = empujar;
      }*/
      
      /*if( actual == explorar || actual == maniobra)
      {
         frente = srf_measure_cm(SRF02_FW);
        // der = srf_measure_cm(SRF02_RW);
         //izq = srf_measure_cm(SRF02_LW);
         if(frente > 15 && frente < 30) actual = acercarse;
      }*/
     /* delay_us(1000);
      frente = srf_measure_cm(SRF02_LW);
      if(frente > 20 && frente < 30) led_on();
      else{led_off();}
      // Si los bumpers no detectan, se resetea choque
      //if(!IN5 && !IN1) choque = 0;*/
   }

}
