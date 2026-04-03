/* ---- DELAY ---- */

void delay_s(i32);
void delay_ms(i32);
void delay_us(i32);

void delay_s(i32 sec)
{
	T0PR  = 15000000 - 1;
	T0TCR = 0x01;
	while(T0TC < sec);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_ms(i32 milli)
{
	T0PR  = 15000 - 1;
	T0TCR = 0x01;
	while(T0TC < milli);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_us(i32 micro)
{
	T0PR  = 15 - 1;
	T0TCR = 0x01;
	while(T0TC < micro);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

/* ---------------- */

