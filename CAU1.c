#include<16f887.h>
#device adc = 10
#fuses hs
#use delay (clock =20M)
#define  lcd_rs   pin_e0
#define  lcd_rw   pin_e1
#define  lcd_e   pin_e2
#define  output_lcd   output_d
#include<tv_lcd.c>

unsigned int16 lm35a =0, lm35b =0;
      
void main()
{
   set_tris_a(0x0f);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0);
   lcd_setup();
   lcd_command(0x80);
   lcd_data("TEN - MSSV");
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(san0|san1|vss_vdd);
   while(true)
   {
//========= LM35_A ==========
      set_adc_channel(0);
      delay_us(20);
      
      // do trung binh 100 lan 
      lm35a = 0;
      for(int8 dem = 0; dem < 100; dem++)
      {
         lm35a = lm35a + read_adc();
         delay_ms(1);       
      }
      
      // tinh do phan giai: (vref+ - vref-)/0.01*2^10 - 1  => 0.4887
      lm35a = lm35a/100*0.4887;
      
      // neu nhiet do lm35a lon hon 40 => LED sang, nguoc lai LED tat
      if (lm35a > 40)   output_high(pin_c0);
      else              output_low(pin_c0);
      lcd_command(0xc0);
      printf(lcd_data,"KENH: A:%lu",lm35a);
      
//============== LM35_B ==========

      set_adc_channel(1);
      delay_us(20);
      // 
      lm35b = 0;
      for(dem = 0; dem < 100; dem++)
      {
         lm35b = lm35b + read_adc();
         delay_ms(1);       
      }
      lm35b = lm35b/100*0.4887;
      if (lm35b > 45)   output_high(pin_c1);
      else              output_low(pin_c1);
      lcd_command(0xc0+12);
      printf(lcd_data,"B:%lu",lm35b);
   }
   
}
