#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"

char b[20],d[20];
void lcd_init(void)
{
	IODIR0|=(0xff<<lcd) |(1<<rw)|(1<<rs)|(1<<e);
	delay_ms(15);
	lcd_cmd(0x30);
	delay_ms(4);
	delay_us(100);
	lcd_cmd(0x30);
	delay_us(100);
	lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
}

void lcd_write(char data)
{
	IOCLR0=0xff<<lcd;
	IOSET0=data<<lcd;
	IOSET0=1<<e;
	delay_us(1);
	IOCLR0=1<<e;
	delay_ms(2);
}

void lcd_cmd(char data)
{
	IOCLR0=1<<rs;
	IOCLR0=1<<rw;
	lcd_write(data);
}

void lcd_data(char data)
{
	IOCLR0=1<<rw;
	IOSET0=1<<rs;
	lcd_write(data);
}


void lcd_string1(char *s)
{
	int i,k=0;
	for(i=0;s[i]!='\0';i++)
	{
		d[k]=s[i];
		k++;
	}
	d[k]='\0';
	for(i=0;d[i]!='\0';i++)
	{
		lcd_data(d[i]);
	}
}


void lcd_string(int val)
{
    char buf[10];
    int i = 0;

    if (val == 0) {
        lcd_data('0');
        return;
    }

    // Convert to string locally
    while (val > 0) {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    }

    // Print reversed
    while (i > 0) {
        lcd_data(buf[--i]);
    }

}

