#include<16f887.h>
#fuses hs
#use delay (clock =10M)

#define  lcd_rs      pin_e0
#define  lcd_rw      pin_e1
#define  lcd_e       pin_e2
#define  output_lcd  output_d
#include<tv_lcd.c>

unsigned int8 level = 0;

      
void main()
{
   set_tris_a(0);
   set_tris_b(0xff);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0);
   setup_timer_2(T2_DIV_BY_16,124,1);
   setup_ccp2(ccp_pwm);
   set_pwm2_duty((int16)0);   //dung dong co
   output_low(pin_c2);
   lcd_setup();
   
   while(true)
   {
      if(!input(pin_b5))   // nhan BTN_STOP => dung dong co
      {
         set_pwm2_duty((int16)0);   //dung dong co
         output_low(pin_c2);
     
      }
      if(!input(pin_b6))
      {
         if(!input(pin_b0))   level =1;
         if(!input(pin_b1))   level =2;
         if(!input(pin_b2))   level =3;
         if(!input(pin_b3))   level =4;
         if(!input(pin_b4))   level =5;
         if(!input(pin_b5))   break;
         
      }
      else
      {
         if(!input(pin_b0))   level =6;
         if(!input(pin_b1))   level =7;
         if(!input(pin_b2))   level =8;
         if(!input(pin_b3))   level =9;
         if(!input(pin_b4))   level =10;
         if(!input(pin_b5))   break;
      }
      
      set_pwm2_duty((int16)level*50);
      delay_ms(100);
      lcd_command(0x80 + 3);
      lcd_data("DONG CO DC");
      lcd_command(0xc0 + 4);
      printf(lcd_data,"LEVEL:%2u",level);
   }
   
}
