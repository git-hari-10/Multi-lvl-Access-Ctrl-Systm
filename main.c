#include <lpc21xx.h>
#include "main_operation.h"

int main()
{		
	INIT_FUNC();   	
  STORE_PASS("2004");
	TOPIC();

  while(1)
  {
    SYSTEM();
  }
}
