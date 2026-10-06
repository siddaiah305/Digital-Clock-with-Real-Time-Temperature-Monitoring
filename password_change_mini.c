#include<stdio.h> 
#include<LPC21xx.h> 
#include<string.h> 
#include"defines_mini.h" 
#include"global_mini.h" 
#include"declarations_mini.h" 
 
int check_password(void) 
{ 
    static int wrong_count = 0; 
    int i; 
    char key; 
    char entered[20]; 
 
    while(1)    
    { 
        if(wrong_count >= 3) 
        { 
            lcd_cmd(0x01); 
            lcd_cmd(0x80); 
            lcd_string1("System Locked"); 
            delay_ms(1000); 
 
            lcd_cmd(0xC0); 
            lcd_string1("Wait..."); 
 
            delay_ms(1500);    
 
            wrong_count = 0;  
        } 
 
        i = 0; 
 
        lcd_cmd(0x01); 
        lcd_cmd(0x80); 
        lcd_string1("Enter Password"); 
 
        lcd_cmd(0xC0); 
 
        while(1) 
        { 
            key = keyscan(); 
 
            /* NUMBER KEY */ 
            if(key >= '0' && key <= '9') 
            { 
                if(i < 19) 
                { 
                    entered[i] = key; 
                    lcd_data('*'); 
                    i++; 
                } 
 
                while(colscan() == 0);  
            } 
 
            /* BACKSPACE KEY */ 
            else if(key == 'B') 
            { 
                if(i > 0) 
                { 
                    i--; 
                    entered[i] = '\0'; 
 
                    /* Move cursor to previous position */ 
                    lcd_cmd(0xC0 + i); 
 
                    /* Erase * */ 
                    lcd_data(' '); 
 
                    /* Move cursor back */ 
                    lcd_cmd(0xC0 + i); 
                } 
 
                while(colscan() == 0); 
            } 
 
            /* ENTER / OTHER KEY */ 
            else 
            { 
                while(colscan() == 0); 
                break; 
            } 
        } 
 
        entered[i] = '\0'; 
 
        if(strcmp(entered, password) == 0) 
        { 
            lcd_cmd(0x01); 
            lcd_string1("Access Granted"); 
            delay_ms(1000); 
 
            wrong_count = 0; 
            return 1;    
        } 
        else 
        { 
            wrong_count++; 
 
            lcd_cmd(0x01); 
            lcd_string1("Access Denied"); 
 
            lcd_cmd(0xC0); 
            lcd_string1("Try Again"); 
 
            delay_ms(1500); 
        } 
    } 
} 
 
 
void password_change(void) 
{ 
    char old[20], newpwd[20], conf[20]; 
    int i; 
    char key; 
 
    while(1) 
    { 
        lcd_cmd(0x01); 
        lcd_cmd(0x80); 
        lcd_string1("Enter Old Pwd"); 
 
        lcd_cmd(0xC0); 
 
        /* Clear buffer */ 
        for(i=0;i<20;i++) 
            old[i]=0; 
 
        i=0; 
 
        while(1) 
        { 
            key = keyscan(); 
 
            /* NUMBER KEY */ 
            if(key>='0' && key<='9') 
            { 
                if(i < 19) 
                { 
                    old[i]=key; 
                    lcd_data('*'); 
                    i++; 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* BACKSPACE KEY */ 
            else if(key=='B') 
            { 
                if(i>0) 
                { 
                    i--; 
                    old[i]='\0'; 
 
                    lcd_cmd(0xC0+i); 
                    lcd_data(' '); 
                    lcd_cmd(0xC0+i); 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* ENTER / OTHER KEY */ 
            else 
            { 
                while(colscan()==0); 
                break; 
            } 
        } 
 
        old[i]='\0'; 
 
        if(strcmp(old,password)==0) 
            break; 
 
        else 
        { 
            lcd_cmd(0x01); 
            lcd_string1("Wrong Password"); 
 
            lcd_cmd(0xC0); 
            lcd_string1("Try Again"); 
 
            delay_ms(1500); 
        } 
    } 
 
 
    while(1) 
    { 
        lcd_cmd(0x01); 
        lcd_cmd(0x80); 
        lcd_string1("New Password"); 
 
        lcd_cmd(0xC0); 
 
        /* Clear buffer */ 
        for(i=0;i<20;i++) 
            newpwd[i]=0; 
 
        i=0; 
 
        while(1) 
        { 
            key = keyscan(); 
 
            /* NUMBER KEY */ 
            if(key>='0' && key<='9') 
            { 
                if(i < 19) 
                { 
                    newpwd[i]=key; 
                    lcd_data('*'); 
                    i++; 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* BACKSPACE KEY */ 
            else if(key=='B') 
            { 
                if(i>0) 
                { 
                    i--; 
                    newpwd[i]='\0'; 
 
                    lcd_cmd(0xC0+i); 
                    lcd_data(' '); 
                    lcd_cmd(0xC0+i); 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* ENTER / OTHER KEY */ 
            else 
            { 
                while(colscan()==0); 
                break; 
            } 
        } 
 
        newpwd[i]='\0'; 
 
 
        lcd_cmd(0x01); 
        lcd_cmd(0x80); 
        lcd_string1("Confirm Pwd"); 
 
        lcd_cmd(0xC0); 
 
        /* Clear buffer */ 
        for(i=0;i<20;i++) 
            conf[i]=0; 
 
        i=0; 
 
        while(1) 
        { 
            key = keyscan(); 
 
            /* NUMBER KEY */ 
            if(key>='0' && key<='9') 
            { 
                if(i < 19) 
                { 
                    conf[i]=key; 
                    lcd_data('*'); 
                    i++; 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* BACKSPACE KEY */ 
            else if(key=='B') 
            { 
                if(i>0) 
                { 
                    i--; 
                    conf[i]='\0'; 
 
                    lcd_cmd(0xC0+i); 
                    lcd_data(' '); 
                    lcd_cmd(0xC0+i); 
                } 
 
                while(colscan()==0); 
                delay_ms(20); 
            } 
 
            /* ENTER / OTHER KEY */ 
            else 
            { 
                while(colscan()==0); 
                break; 
            } 
        } 
 
        conf[i]='\0'; 
 
 
        /* Compare new password and confirmation */ 
        if(strcmp(newpwd,conf)==0) 
        { 
            strcpy(password,newpwd); 
 
            lcd_cmd(0x01); 
            lcd_string1("Pwd Changed"); 
            delay_ms(1500); 
 
            break; 
        } 
 
        else 
        { 
            lcd_cmd(0x01); 
            lcd_string1("Mismatch!"); 
 
            lcd_cmd(0xC0); 
            lcd_string1("Try Again"); 
 
            delay_ms(1500); 
        } 
    } 
}