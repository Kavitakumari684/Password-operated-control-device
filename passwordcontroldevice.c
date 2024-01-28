#include<reg51.h>
#include"string.h"
#define dat P2
#define keypad  P1

sbit rs = P3^0;
sbit en = P3^1;
sbit relay= P3^2;

void delay (unsigned int time);
void lcdcmd(unsigned char ch);
void lcddata(unsigned char ch);
void lcdstr(unsigned char *str);
char getkeypad(void);

void main()
{
	
	unsigned char keyvalue=0;
	unsigned char count = 0;
	unsigned int comparepassword = 0 ;
	unsigned int attempt = 0;
	unsigned int dec = 30;
	char predefinedpassword[5] = "2222";
	char enterpassword[5] ;
	relay = 0;

	lcdcmd(0x38);
	lcdcmd(0x0E);
	
	
	while(1)
	{
		lcdcmd(0x80);
		lcdstr("ENTER PASSWORD");
		keyvalue = getkeypad();
		if(keyvalue != 0)
		{
			enterpassword[count] = keyvalue;
			lcdcmd(0xc0 + count);
	    lcdstr("*");
			count = count +1;
		}
		if(count == 4)
		{
			lcdcmd(0x01);
			count = 0;
			
			comparepassword = strcmp(predefinedpassword , enterpassword);
			
			if(comparepassword == 0)
			{
				lcdcmd(0x80);
				relay = 1;
				lcdstr("correct password");
				delay(50);
			}
			else
			{
				
				lcdcmd(0x80);
				relay = 0;
				lcdstr("wrong password");
				attempt = attempt + 1;
				delay(50);
				lcdcmd(0x01);
				if(attempt == 2)
				{
					lcdstr("lock for 30 sec.");
					
					for( dec = 30;dec>0;dec--)
					{
						delay(50);
					}
				}
				lcdcmd(0x01);
			}
		}
	}
}
void delay (unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<1200;j++)
		{
		}
	}
}

void lcdstr(unsigned char *str)
{
	unsigned int loop;
	for(loop = 0; str[loop]!='\0' ;loop++)
	{
		lcddata(str[loop]);
	}
	
}
void lcdcmd(unsigned char ch)
{
	dat = ch;
	rs = 0;
	en =1;
	delay(10);
	en =0;
}
void lcddata(unsigned char ch)
{
	dat = ch;
	rs=1;
	en =1;
	delay(10);
	en =0;
}
char getkeypad(void)
{
	unsigned char keyvalue = 0 ;
	keypad = 0xFE;     //ROW =0
	if(keypad == 0xEE)
	{
		keyvalue = '1' ;
	}
	if(keypad == 0xDE)
	{
		keyvalue = '2';
	}
	if(keypad == 0xBE)
	{
		keyvalue = '3';
	}
	
	keypad = 0xFD;     //ROW =1
	if(keypad == 0xED)
	{
		keyvalue = '4' ;
	}
	if(keypad == 0xDD)
	{
		keyvalue = '5';
	}
	if(keypad == 0xBD)
	{
		keyvalue = '6';
	}
	
	keypad = 0xFB;     //ROW =2
	if(keypad == 0xEB)
	{
		keyvalue = '7' ;
	}
	if(keypad == 0xDB)
	{
		keyvalue = '8';
	}
	if(keypad == 0xBB)
	{
		keyvalue = '9';
	}
	
	keypad = 0xF7;     //ROW =2
	if(keypad == 0xE7)
	{
		keyvalue = '*' ;
	}
	if(keypad == 0xD7)
	{
		keyvalue = '0';
	}
	if(keypad == 0xB7)
	{
		keyvalue = '#';
	}

	return keyvalue;
}
	
	
		
	
	

