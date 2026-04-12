#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include "i2c_operation.h"
#include "keypad.h"

#define SW 14

i32 attempts = 0;
i32 otp = 0;
u8 p[10];						// PASSWORD STORAGE
u8 e[10];     			// ENTERED PASSWORD

void INIT_FUNC(void);
void TOPIC(void);
void STORE_PASS(u8*);
void GET_PASS(void);
void ENTER_PASS(void);
void COMPARE_PASS(void);
void ENTER_OTP(u8*);
void GENERATE_OTP(void);

/* ---- INITIALIZATIONS ----  */

void INIT_FUNC()
{
	lcd_init();
	I2C_init();
}

/* ---- I2C_EEPROM STORE & GET PASSWORD ---- */

void STORE_PASS(u8 *pass)
{
	Page_Write(0x50,0x00,pass,4);
	delay_ms(10);
}

void GET_PASS()
{
	Seq_Read(0x50,0x00,p,4);
	p[4] = '\0';
	delay_ms(100);
}

/* ----- ENTER PASSWORD ----- */

void ENTER_PASS()
{
	i32 i,addr;
	lcd_cmd(0x01);
	lcd_cmd(0x80);lcd_str("====================");
	lcd_cmd(0xC0);lcd_str("   ENTER PASSWORD   ");
	lcd_cmd(0xD4);lcd_str("====================");
	for(i=0,addr=0x99;i<4;i++)
	{
		e[i] = keypress();
		lcd_cmd(addr+=2);lcd_write('*');
	}
	e[i] = '\0';
}

/* ---- PROJECT_TITLE ---- */

void TOPIC()
{
	i32 i;
	u8 st,end;
	
	lcd_cmd(0xC0); lcd_str("MULTI LEVEL SECURITY");
	lcd_cmd(0x94); lcd_str("ACCESS CONTROL SYSTM");
	for(i=0, st=0x80, end=0xD4; i<20; i++)
	{
		lcd_cmd(st++);lcd_write('~');
		lcd_cmd(end++);lcd_write('~');
		delay_ms(200);
	}
}

/* ----- COMPARE PASSWORD ----- */

void COMPARE_PASS()
{
	u8 otp[5];
	if(!strcmp((char *)p,(char *)e))
	{
		attempts = 0;
		lcd_cmd(0x01);
		lcd_cmd(0x80);lcd_str("  (^_^) ACCESS OK!  ");
		lcd_cmd(0xC0);lcd_str(" ------------------ ");
		lcd_cmd(0x94);lcd_str("   PRESS ~ BUTTON   ");
		lcd_cmd(0xD4);lcd_str("    GENERATE OTP    ");
		//delay_ms(2000);
		ENTER_OTP(otp);
	}
	else
	{
		attempts++;
		
		lcd_cmd(0x01);
		lcd_cmd(0x80);lcd_str("====================");
		lcd_cmd(0xC0);lcd_str("      IN-VALID      ");
		lcd_cmd(0x94);lcd_str("      PASSWORD      ");
		lcd_cmd(0xD4);lcd_str("====================");
		
		delay_ms(1200);lcd_cmd(0x01);
		
		lcd_cmd(0xC0);lcd_str("   ATTEMPTS LEFT:   ");
		lcd_cmd(0x9D);lcd_write('0');lcd_write('0' + (3 - attempts));  

		delay_ms(1200);

		// LOCK CONDITION
		if(attempts >= 3)
		{
				lcd_cmd(0x01);
				lcd_cmd(0x80);lcd_str(" ****************** ");
				lcd_cmd(0xC0);lcd_str("       SYSTEM       ");
				lcd_cmd(0x94);lcd_str("       LOCKED       ");
				lcd_cmd(0xD4);lcd_str(" ****************** ");

				while(1);   // permanent lock
		}
	}
}

void GENERATE_OTP()
{
	T1PR  = 15000 - 1;
	T1TCR = 0x01;

	while(((IOPIN0>>SW)&1)==1);  
	delay_ms(150);

	otp = (T1TC % 8000) + 2000;  

	while(((IOPIN0>>SW)&1)==0);   

	T1TCR = 0x03;
	T1TCR = 0x00;
}

void ENTER_OTP(u8 *p)
{
	i32 i, addr;

	GENERATE_OTP();
	// Here comes UART

	lcd_cmd(0x01);
	lcd_cmd(0x80);lcd_str(" ------------------ ");
	lcd_cmd(0xC0);lcd_str("     ENTER OTP      ");
	lcd_cmd(0xD4);lcd_str(" ------------------ ");
	lcd_cmd(0x94);

	for(i=0,addr=0x98;i<4;i++)
	{
		p[i] = keypress();
		lcd_cmd(addr+=2);
		lcd_write(p[i]);   
	}
	p[i] = '\0';

	if((p[0]-48)*1000 + (p[1]-48)*100 + (p[2]-48)*10 + (p[3]-48) == otp)
	{
		lcd_cmd(0x01);
		lcd_str("ACCESS GRANTED");
	}
	else
	{
		lcd_cmd(0x01);
		lcd_str("WRONG OTP");
	}

	while(1);
}

