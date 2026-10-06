#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"
static int prev = 1;

enum day{sun,mon,tue,wed,thu,fri,sat};
int main()
{
	lcd_init();
kpm_init();
adc_init();
IODIR0 |=1<<BUZZ;
IODIR0 &= ~(1<<s1);
PINSEL0 &= ~(3<<(s1*2)); 
prev = (IOPIN0 >> s1) & 1;   
	CCR=rtc_reset;
	CCR=0x00;
	PREINT=preint_val;
	PREFRAC=prefrac_val;
	CCR=rtc_enable;
	initial_time(8,30,40);
	initial_data(06,10,2026);
	initial_day(tue);
	initial_alarm(11,30,0);
	initial_alarm_data(1,5,2026);
	initial_alarm_day(tue);
	ILR=0x03;
  
		while(1)
	{
		gettimeinfo(&hour,&min,&sec);
  	gettimeinfo(&hour,&min,&sec);
		lcd_display_time(hour,min,sec);
		getdatainfo(&date,&month,&year);
		lcd_display_data(date,month,year);
		getdayinfo(&day);
		lcd_display_day(day);
		read_lm35(&tdegC);
		lcd_cmd(0xC0+11);
		if(tdegC==0)
		{
			lcd_data('0');
		}
		else
		{
		lcd_string(tdegC);
		}
			lcd_data('C');
		lcd_data(' ');
		lcd_data(' ');
		delay_ms(100);
		
		
		 if(ILR &(1<<1))
    {
        check_and_print_alarm(); 
    }
		curr = (IOPIN0 >> s1) & 1;

    if(prev == 1 && curr == 0)
    {

        if(((IOPIN0 >> s1) & 1) == 0)
        {
            flag = 1;
				while(((IOPIN0 >> s1) & 1) == 0);
        }
    }
    prev = curr;


		if(flag==1)
		{
			flag=0;
		if(check_password()==1)
		{
		lcd_cmd(0x01);
		while(1)
		{
			lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string1("1.rtc");
		lcd_cmd(0x80+8);
		lcd_string1("2.pwd");
    lcd_cmd(0xc0);
    lcd_string1("3.alarm");
	lcd_cmd(0xC0+8);
	lcd_string1("4.exit");
	delay_ms(2000);
		//while(((IOPIN0 >> s1) & 1) == 1)
	//	{
	//	}
	//		while(((IOPIN0 >> s1) & 1) == 0);
			
    // lcd_string1("enter choice 1 or 2 or 3");
		lcd_cmd(0x01);
		lcd_cmd(0x80);
   lcd_string1("enter choice");			
		op=readnum(&op,&key2);
		////////////////////////////rtc change///////////////////////////////////////////////////////
					if(op==1)             
			{
        rtc_change();
				
			}
					/////////////////////////////////////////////////password change/////////////////////////////////////////////
		else if(op==2)   
    {
	password_change();
			
	  }
		//////////////////////////////////////////////alaram set/////////////////////////////////////////////////////////////
					 else if(op==3)
					{
						Alarm_change();
						
					}

					else if(op==4)
					{
					break;
					}
					else 
					{
						lcd_cmd(0x01);
						lcd_cmd(0x80);
						lcd_string1("invalid option");
					  delay_ms(1000);
						 lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string1("ENTER AGAIN");

    delay_ms(1500);
						op=0;
					}
				}
				}
			}
		}
			
			
}
