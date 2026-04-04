#include <lpc21xx.h>
#include <string.h>
#include "lcd.h"
#include "i2c_operation.h"
#include "keypad.h"

i32 attempts = 0;
u8 p[10];			// PASSWORD STORAGE
u8 e[10];     // ENTERED PASSWORD

void INIT_FUNC(void);
void TOPIC(void);
void STORE_PASS(u8*);
void GET_PASS(void);
void ENTER_PASS(void);
void COMPARE_PASS(void);
void OTP(void);

int main()
{
	INIT_FUNC();   	
  STORE_PASS("2134");
	TOPIC();

  while(1)
  {
    ENTER_PASS();
    GET_PASS();
    COMPARE_PASS();
  }
}

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
	for(i=0,addr=0x9C;i<4;i++)
	{
		e[i] = keypress();
		lcd_cmd(addr++);lcd_write(e[i]);
	}
	e[i] = '\0';
}

/* ---- PROJECT_TITLE ---- */

void TOPIC()
{
	i32 i;
	lcd_cmd(0x80); lcd_str("MULTI LEVEL SECURITY");
	lcd_cmd(0xC0); lcd_str("   ACCESS CONTROL   ");
	lcd_cmd(0x94); lcd_str("       SYSTEM       ");
	lcd_cmd(0xD4);
				for(i=0;i<20;i++)
				{
					lcd_write('~');
					delay_ms(200);
				}
}

/* ----- COMPARE PASSWORD ----- */

void COMPARE_PASS()
{
	i32 i;
	if(!strcmp((char *)p,(char *)e))
			{
				attempts = 0;
				lcd_cmd(0x01);
				lcd_cmd(0xC0);lcd_str(" [ ACCESS GRANTED ] ");
				lcd_cmd(0x94);
				for(i=0;i<20;i++)
				{
					lcd_write('-');
					delay_ms(100);
				}
				OTP();
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

void OTP()
{
	lcd_cmd(0x01);
  lcd_cmd(0x80);lcd_str("====================");
  lcd_cmd(0xC0);lcd_str("   SYSTEM STATUS    ");
  lcd_cmd(0x94);lcd_str("      UNLOCKED      ");
  lcd_cmd(0xD4);lcd_str("====================");
	
	/*
	lcd_cmd(0x01);
  lcd_cmd(0x80);lcd_str(" ****************** ");
  lcd_cmd(0xC0);lcd_str("   SYSTEM STATUS    ");
  lcd_cmd(0x94);lcd_str("      UNLOCKED      ");
  lcd_cmd(0xD4);lcd_str(" ****************** ");
	while(1);
	*/
}

