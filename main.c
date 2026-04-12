#include <lpc21xx.h>
#include "main_operation.h"

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
