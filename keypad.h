// ROWS
#define r0 1<<16
#define r1 1<<17
#define r2 1<<18
#define r3 1<<19
// COLUMNS
#define c0 ((IOPIN1>>16)&1)
#define c1 ((IOPIN1>>17)&1)
#define c2 ((IOPIN1>>18)&1)
#define c3 ((IOPIN1>>19)&1)

unsigned char key[4][4] = {
	
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'C','0','=','+'}

};

unsigned char keypress(void)
{
	unsigned char r,c;
	IODIR0 |= r0|r1|r2|r3;
	while(1)
	{
		IOCLR0 = r0|r1|r2|r3;
		IOSET1 = c0|c1|c2|c3;
		
		// Waiting for keypress
		while((c0&&c1&&c2&&c3)==1); 
		
		/* ----- ROW IDENTIFICATION ----- */
		
		IOCLR0 = r0;            // ROW-0
		IOSET0 = r1|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			r = 0;
			break;
		}
		
		IOCLR0 = r1;            // ROW-1
		IOSET0 = r0|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			r = 1;
			break;
		}
		
		IOCLR0 = r2;            // ROW-2
		IOSET0 = r0|r1|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			r = 2;
			break;
		}
		
		IOCLR0 = r3;            // ROW-3
		IOSET0 = r0|r1|r2;
		if((c0&&c1&&c2&&c3)==0)
		{
			r = 3;
			break;
		}
		
		/* ----------------------------- */
	}
	
	/* ---- COLUMN IDENTIFICATION ---- */
	
	if(c0==0)
		c = 0;
	else if(c1==0)
		c = 1;
	else if(c2==0)
		c = 2;
	else
		c = 3;
	
	/* ------------------------------- */
	
	delay_ms(150); // To avoid (switch bouncing)
	
  // Wait until key release	
	while((c0&&c1&&c2&&c3)==0); 
	
	return key[r][c];
}
	

