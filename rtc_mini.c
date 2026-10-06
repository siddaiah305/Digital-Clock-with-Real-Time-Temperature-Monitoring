#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"
char week[][4]={"sun","mon","tue","wed","thu","fri","sat"};
enum day{sun,mon,tue,wed,thu,fri,sat};
void initial_alarm_day(int day)
{
	ALDOW=day;
}
void initial_alarm_data(int date,int month,int year)
{
	
	ALDOM=date;
	ALMON=month;
	ALYEAR=year;
	
}
void initial_alarm(int hour,int min,int sec)
{
	/* Disable alarm first */
	AMR = 0xFF;   

	ALHOUR = hour;
	ALMIN  = min;
	ALSEC  = sec;

	/* Clear any pending alarm flag */
	ILR = (1<<1);

	/* Enable only HOUR, MIN, SEC comparison */
	AMR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	
}
void lcd_display_day(int day)
{
	lcd_cmd(0x80+11);
	lcd_string1(week[day]);

}
void getdayinfo(int *day)
{
	*day=DOW;
}

void lcd_display_data(int date,int month,int year)
{
	lcd_cmd(0xc0);
	lcd_data((date/10+48));
	lcd_data((date%10+48));
	lcd_data('/');
	lcd_data((month/10+48));
	lcd_data((month%10+48));
	lcd_data('/');
	lcd_data((year/1000)+48);
	lcd_data(((year/100)%10)+48);
	lcd_data(((year/10)%10)+48);
	lcd_data((year%10)+48);
}

void getdatainfo(int *date,int *month,int *year)
{
	*date=DOM;
	*month=MONTH;
	*year=YEAR;
}

	
void lcd_display_time(int hour,int min,int sec)
{
	lcd_cmd(0x80);
	lcd_data((hour/10+48));
	lcd_data((hour%10+48));
	lcd_data(':');
	lcd_data((min/10+48));
	lcd_data((min%10+48));
	lcd_data(':');
	lcd_data((sec/10+48));
  lcd_data((sec%10+48));
	lcd_data(' ');
	lcd_data(' ');
	lcd_data(' ');
}
void gettimeinfo(int *hour,int *min,int*sec)
{
	*hour=HOUR;
	*min=MIN;
	*sec=SEC;
}

void initial_time(int hour,int min,int sec)
{
	HOUR=hour;
	MIN=min;
	SEC=sec;
}
void initial_data(int date,int month,int year)
{
	DOM=date;
	MONTH=month;
	YEAR=year;
}
void initial_day(int day)
{
	DOW=day;
}


void display_alarm(int al_hour,int al_min,int al_sec)
{
	lcd_cmd(0x80);
	lcd_data(((al_hour)/10)+48);
	lcd_data(((al_hour)%10)+48);
	lcd_data(':');
	lcd_data(((al_min)/10)+48);
	lcd_data(((al_min)%10)+48);
	lcd_data(':');
	lcd_data(((al_sec)/10)+48);
	lcd_data(((al_sec)%10)+48);
	lcd_data(' ');
	lcd_data(' ');
}


