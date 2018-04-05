#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(A)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
int8 datoC, datoD, interruptor;
int16 resultado;
#INT_RB
void interrupt_isr(void){
   if(input(pin_b4)==0)
      interruptor=1;
   if(input(pin_b5)==0)
      interruptor=2;
   if(input(pin_b6)==0)
      interruptor=3;
   if(input(pin_b7)==0)
      interruptor=4;
}

void main (void){
   set_tris_A(0xC0);
   set_tris_B(0xF0);
   set_tris_C(0xFF);
   set_tris_D(0xFF);
   set_tris_E(0x08);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   port_b_pullups(true);
   while (true){
      datoC=input_c();
      datoD=input_d();
      switch (interruptor){
         case 1:{
            resultado=(int16)datoC + (int16)datoD;
            interruptor=0;
         }break;
         case 2:{
            if(datoD<=datoC){
            resultado=(int16)datoC - (int16)datoD;
            interruptor=0;
            }
            else{
            resultado=(int16)datoC - (int16)datoD;
            resultado=(~resultado)+1;
            interruptor=0;
            }
         }break;
         case 3:{
            resultado=(int16)datoC * (int16)datoD;
            interruptor=0;
         }break;
         case 4:{
            if(datoD!=0){
            resultado=(int16)datoC / (int16)datoD;
            interruptor=0;
            }
            else{
            resultado=8191;
            interruptor=0;
            }
         }break;
      }
      output_a(resultado);
      output_b(resultado>>6);
      output_e(resultado>>10);
   }
}
