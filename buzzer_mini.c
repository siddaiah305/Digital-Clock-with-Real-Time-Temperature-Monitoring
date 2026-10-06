#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"
void check_and_print_alarm(void)
{
    if(ILR & 0x02)
    {
        lcd_cmd(0x01);
        lcd_cmd(0x80);
        lcd_string1("ALARM !!!");
			  found=1;
			 if(found==1)
			 {
				 IOSET0=1<<BUZZ;
				 delay_ms(1000);
				 IOCLR0=1<<BUZZ;
				 delay_ms(1000);
			 }
			 found=0;
			 while(((IOPIN0>>s1)&1)==1);
			 while(((IOPIN0>>s1)&1)==0)
			 {
			 }

        
        ILR = 0x02;   // clear flag
    }
}

