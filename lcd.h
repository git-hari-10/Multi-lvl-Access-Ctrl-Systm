/* ---- LCD INTERFACE ---- */

#include "datatypes.h"
#include "delay.h"

#define D  ((0xf)<<4)  // Configured 4 5 6 7 for data pin
#define RS (1<<10)     // 10 for Register Select
#define E  (1<<11)		 // 11 for Enable

void lcd_cmd(u8);
void lcd_write(u8);
void lcd_init(void);
void lcd_str(u8 *);

void lcd_init()
{
	IODIR0 |= D|RS|E;
	lcd_cmd(0x02);
	lcd_cmd(0x0C);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
}

void lcd_cmd(u8 command)
{
		//MSB
    IOCLR0 = D;
    IOSET0 = (command & 0xf0);
    IOCLR0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
		//LSB
    IOCLR0 = D;
    IOSET0 = ((command << 4) & 0xf0);
    IOCLR0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
}

void lcd_write(u8 data)
{
		//MSB
    IOCLR0 = D;
    IOSET0 = (data & 0xf0);
    IOSET0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
		//LSB
    IOCLR0 = D;
    IOSET0 = ((data << 4) & 0xf0);
    IOSET0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
}

void lcd_str(u8 *s)
{
	while(*s)
		lcd_write(*s++);
}
   
/* --------------------------- */


