#include<stdio.h>
#include<LPC21xx.h>
#include<string.h>
#include"defines_mini.h"
#include"global_mini.h"
#include"declarations_mini.h"

void adc_init(void)
{
	PINSEL1 &= ~(0xff<<((27-16)*2));
	PINSEL1 |=(1<<((27-16)*2)) | (1<<((28-16)*2)) | (1<<((29-16)*2)) | (1<<((30-16)*2));
	ADCR |=(1<<pdn) | (clk_div<<clk_div_bits);
}

void adc_read(int chno,int *dval,float *evr)
{
	ADCR &=0xffffff00;
 ADCR |=(1<<adc_start_con) |(1<<chno);
	while(((ADDR>>done)&1)==0);
	ADCR &=~(1<<adc_start_con);
	*dval=((ADDR>>digital_bits)&1023);
	*evr=(*dval * (3.3/1024));
}

void read_lm35(int *tdegC)
{
	adc_read(1,&dval,&evr);
	*tdegC=(evr*100);
	
}


