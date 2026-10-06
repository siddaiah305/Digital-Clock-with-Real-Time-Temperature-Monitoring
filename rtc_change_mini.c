#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"

void rtc_change(void)
{
	 while(1)
				{
				while(1)
				{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("1.hr");
				lcd_cmd(0x80+5);
				lcd_string1("2.min");
				lcd_cmd(0x80+11);
				lcd_string1("3.sec");
				lcd_cmd(0xC0);
				lcd_string1("4.DD");
				lcd_cmd(0xC0+5);
				lcd_string1("5.MM");
				lcd_cmd(0xC0+11);
				lcd_string1("6.day");
				delay_ms(1000);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("7.return to menu");
				delay_ms(2000);
				 //while(((IOPIN0 >> s1) & 1) == 1);	
			//while(((IOPIN0 >> s1) & 1) == 0)
			//{
			//}
			
				 lcd_cmd(0x01);
				 lcd_cmd(0x80);
				 lcd_string1("enter choice");
				 lcd_cmd(0xC0);
				 op=readnum(&op,&key2);
				 if(op<=7)
				 {	 
				if(op==1)
				{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter hour");
				lcd_cmd(0xc0);
				hour = readnum(&op,&key2);
				}
				else if(op==2)
				{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter min");
				lcd_cmd(0xc0);
				min = readnum(&op,&key2);
				}
				else if(op==3)
				{

				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter sec");
				lcd_cmd(0xc0);
				sec = readnum(&op,&key2);
				}
				else if(op==4)
				{
                lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter date");
				lcd_cmd(0xc0);
				date = readnum(&op,&key2);
				}

				else if(op==5)
				{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter month");
				lcd_cmd(0xc0);
				month = readnum(&op,&key2);
				}
				else if(op==6)
				{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string1("Enter day");
				lcd_cmd(0xc0);
				day = readnum(&op,&key2);
				 }
				 else if(op==7)
				 {
				   return;
				}
				 

				if(hour<24 && min<60 && sec<60 && date<=31 && month<=12 && day<=6)
				{
					
											
						AMR = 0XFF;

						CCR = rtc_reset;
						initial_time(hour,min,sec);
						initial_data(date,month,year);
						initial_day(day);
						CCR = rtc_enable;

						
						ILR = (1<<1);

						
              AMR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);			

					lcd_cmd(0x01);
					lcd_string1("DETAILS Updated");
					delay_ms(1000);
					break;
				}

				else
				{
					lcd_cmd(0x01);
					lcd_string1("Invalid DETAILS");
					delay_ms(1500);
					 lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string1("ENTER AGAIN");

    delay_ms(1500);
					op=0;
				}
			}
				 else
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string1("invalid option");
    delay_ms(1500);

    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string1("ENTER AGAIN");

    delay_ms(1500);

    op=0;
}
			 }
				/* Optional display */
				lcd_cmd(0x01);
				lcd_display_time(hour,min,sec);
				lcd_display_data(date,month,year);
				lcd_display_day(day);
				//initial_data(date,month,year);
				//initial_day(day);

}
}
