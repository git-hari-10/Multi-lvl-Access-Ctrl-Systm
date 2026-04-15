/* ---- TRANSMIT TEXT MESSAGE USING UART0 ---- */

void UART0_init(void);
void TxD(u8);
void Tx_str(u8*);
void send_sms(i32);
void send_unauthorized_sms(void);

void UART0_init()
{
	PINSEL0 |= 0x5;
	U0LCR    = 0x83;
	U0DLL    = 97;
	U0DLM    = 0;
	U0LCR    = 0x03;
}

void TxD(u8 txbyte)
{
	while(!((U0LSR>>5)&1));
	U0THR = txbyte;
}

void Tx_str(u8 *s)
{
	while(*s)
		TxD(*s++);
}

void send_sms(i32 otp)
{
	Tx_str("AT\r\n");
	delay_ms(500);

	Tx_str("AT+CPIN?\r\n");
	delay_ms(500);

	Tx_str("AT+CREG?\r\n");
	delay_ms(500);

	Tx_str("AT+CMGF=1\r\n");
	delay_ms(500);

	Tx_str("AT+CMGS=\"8489593859\"\r\n");
	delay_ms(500);   

	Tx_str("Don't Share your otp : ");
	TxD((otp / 1000) + '0');
	TxD(((otp / 100) % 10) + '0');
	TxD(((otp / 10) % 10) + '0');
	TxD((otp % 10) + '0');

	TxD(26);          // Ctrl+Z   
}

void send_unauthorized_sms()
{
	Tx_str("AT\r\n");
	delay_ms(500);

	Tx_str("AT+CPIN?\r\n");
	delay_ms(500);

	Tx_str("AT+CREG?\r\n");
	delay_ms(500);

	Tx_str("AT+CMGF=1\r\n");
	delay_ms(500);

	Tx_str("AT+CMGS=\"8489593859\"\r\n");
	delay_ms(500);   

	Tx_str("Unauthorized Access System Rebooted");

	TxD(26);          // Ctrl+Z
}


