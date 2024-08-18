#include<16f887.h>
#fuses hs
#use delay (clock =20M)
#use rs232(baud = 9600, xmit = pin_c6, rcv = pin_c7)

unsigned int8 nhan, dem = 0;
const unsigned int8 ma7doan[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


void main()
{
   set_tris_a(0x01);
   set_tris_b(0);
   set_tris_c(0x80);
   set_tris_d(0);
   enable_interrupts(int_rda);
   enable_interrupts(global);
 
   while(true)
   {
      if(!input(pin_a0))      // nut nhan dem san pham
      {
         delay_ms(20);
         if(!input(pin_a0))
         {
              dem++;
              if(dem>99)   dem = 1;
              putc(dem);
              while(!input(pin_a0));
         }
      }
     
      output_d(ma7doan[dem/10]);
      output_b(ma7doan[dem%10]);
      
   }
   
}

#int_rda
void ngatnhan()
{
   nhan = getc();
   if(nhan ==0)   dem = 0;
} 



