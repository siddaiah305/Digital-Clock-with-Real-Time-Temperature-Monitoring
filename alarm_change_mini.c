#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"
void Alarm_change(void)
{
	while(1)
	{
				lcd_cmd(0x01);
						lcd_cmd(0x80);
						lcd_string1("Enter hour");
						lcd_cmd(0xC0);
						al_hour = readnum(&op,&key1);

						lcd_cmd(0x01);
						lcd_cmd(0x80);
						lcd_string1("Enter min");
						lcd_cmd(0xC0);
						al_min = readnum(&op,&key1);

						lcd_cmd(0x01);
						lcd_cmd(0x80);
						lcd_string1("Enter sec");
						lcd_cmd(0xC0);
						al_sec = readnum(&op,&key1);

						/* ? Validation */
						if(al_hour < 24 && al_min < 60 && al_sec < 60)
						{
							initial_alarm(al_hour,al_min,al_sec);
							lcd_cmd(0x01);
						
							lcd_cmd(0x80);
							display_alarm(al_hour,al_min,al_sec);
						lcd_cmd(0xC0);
							lcd_string1("Alarm Set");
							delay_ms(1500);
							break;
						}
						else
						{
							lcd_cmd(0x01);
							lcd_string1("Invalid Time");
							delay_ms(1500);
							 lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string1("ENTER AGAIN");

    delay_ms(1500);
						}
					}
}

