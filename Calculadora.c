#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG,
#use delay(clock=16000000)
#use fast_io(A)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
#use fast_io(E)
unsigned int8 datoC, datoD, operacion;
int16 resultado;
#INT_RB
void interrupt_isr(void){
   if(input(PIN_B4)==1)
      operacion=1;
   if(input(PIN_B5)==1)
      operacion=2;
   if(input(PIN_B6)==1)
      operacion=3;
   if(input(PIN_B7)==1)
      operacion=4;
}

void main (void){
   set_tris_a(0xC0);
   set_tris_b(0xF0);
   set_tris_c(0xFF);
   set_tris_d(0xFF);
   set_tris_e(0x08);
   setup_adc(NO_ANALOGS);
   setup_oscillator(OSC_16MHZ);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   port_b_pullups(FALSE);
   output_a(0x00);
   output_b(0x00);
   output_e(0x00);
   while (TRUE){
      datoC=input_c();
      datoD=input_d();
      switch (operacion){
         case 1:{
            resultado=(int16)datoC + (int16)datoD;
            operacion=0;
         }break;
         case 2:{
            resultado=(int16)datoC - (int16)datoD;
            operacion=0;
         }break;
         case 3:{
            resultado=(int16)datoC * (int16)datoD;
            operacion=0;
         }break;
         case 4:{
            if(datoD!=0){
            resultado=(int16)datoC / (int16)datoD;
            }
            else{
            resultado=8191;
            }
            operacion=0;
         }break;
      }
      output_a(resultado);
      output_b(resultado>>6);
      output_e(resultado>>10);
   }
}
