#include<stdio.h> 
#include<LPC21xx.h> 
#include<string.h> 
#include"defines_mini.h" 
#include"global_mini.h" 
#include"declarations_mini.h" 
 
char keylut[4][4]={
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
}; 

int readnum(int *op,int *key2)
{
    char num[10];
    int i = 0;
    int j;

    *op = 0;

    lcd_cmd(0xc0);

    while(1)
    {
        *key2 = keyscan();

        if(*key2 >= '0' && *key2 <= '9')
        {
            if(i < 9)
            {
                num[i] = *key2;
                i++;

                lcd_data(*key2);

                *op = (*op * 10) + (*key2 - '0');
            }
        }

        else if(*key2 == 'B')
        {
            if(i > 0)
            {
                i--;

                *op = 0;

                for(j = 0; j < i; j++)
                {
                    *op = (*op * 10) + (num[j] - '0');
                }

                lcd_cmd(0xc0 + i);
                lcd_data(' ');
                lcd_cmd(0xc0 + i);
            }
        }

        else if(*key2 != 0)
        {
            break;
        }
    }

    return *op;
}

void kpm_init(void) 
{ 
    IODIR1 &=~(0xf<<row0); 
    IODIR1 |=0xf<<row0; 
} 

char keyscan(void)
{
    char key;

    /* Wait until a key is pressed */
    while(colscan());

    /* Debounce key press */
    delay_ms(20);

    /* Check whether key is still pressed */
    if(colscan() == 0)
    {
        r = rowcheck();
        c = colcheck();

        key = keylut[r][c];

        /* Wait until key is completely released */
        while(colscan() == 0);

        /* Debounce key release */
        delay_ms(20);

        return key;
    }

    return 0;
}

char colscan(void) 
{ 
    char t; 

    t=((IOPIN1>>col0)&0xf); 

    if(t==15) 
        return 1; 
    else 
        return 0; 
} 
 
char rowcheck(void) 
{ 
    for(r=0;r<4;r++) 
    { 
        IOSET1=0xf<<row0; 
        IOCLR1=1<<(row0+r); 

        if(!colscan()) 
            break; 
    } 

    IOCLR1=0xf<<row0; 

    return r; 
} 
 
char colcheck(void) 
{ 
    for(c=0;c<4;c++) 
    { 
        if(((IOPIN1>>(col0+c))&1)==0) 
            break; 
    } 

    return c; 
}