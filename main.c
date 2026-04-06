#include <lpc21xx.h>
#include "main_operation.h"

void OTP_GENERATE_ISR(void) __irq
{
	
}

int main()
{	
	
	 /* ---- EINT1 CONFIGURATION ---- */
		PINSEL0 |= 0x20000000;
		VICIntSelect = 0;
															// Allocate IRQ SLOT-0
		VICVectCntl0 = (0x20)|15;
		VICVectAddr0 = (unsigned long)OTP_GENERATE_ISR;
		
		EXTMODE  = 0x00;
		EXTPOLAR = 0x00;
	
		VICIntEnable = (1<<15);
	 /* ----------------------------- */
		
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
