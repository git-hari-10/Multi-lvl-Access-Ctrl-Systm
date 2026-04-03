#include <lpc21xx.h>
#include "lcd.h"
#include "i2c_operation.h"

u8 p[10];        // PASSWORD STORAGE

void INIT_FUNC(void);
void TOPIC(void);
void STORE_PASS(u8*);
void GET_PASS(void);

int main()
{
	INIT_FUNC();   	
	STORE_PASS("2134");
	TOPIC();
	GET_PASS();
	lcd_cmd(0x81);lcd_str(p);
}


/* ---- INITIALIZATIONS ----  */

void INIT_FUNC()
{
	lcd_init();
	I2C_init();
}

/* -------------------------- */


/* ---- I2C_EEPROM STORE & GET PASSWORD ---- */

void STORE_PASS(u8 *pass)
{
	Page_Write(0x50,0x00,pass,4);
	delay_ms(10);
}

void GET_PASS()
{
	Seq_Read(0x50,0x00,p,4);
	delay_ms(100);
}

/* ----------------------------------- */


/* ---- PROJECT_TITLE ---- */

void TOPIC()
{
	lcd_cmd(0x80);lcd_str("     MULTI-LEVEL    ");
	lcd_cmd(0xC0);lcd_str("   SECURITY  BASED  ");
	lcd_cmd(0x94);lcd_str("    ACCESS CONTROL  ");
	lcd_cmd(0xD4);lcd_str("        SYSTEM      ");
	
	delay_s(3);lcd_cmd(0x01);
}

/* ----------------------- */

