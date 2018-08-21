#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */

#define PIO_1_BASE 0x0

int main(void){

	printf("Embarcados+ \n");
	init_but_pio();


  unsigned int led = 0;

  printf("Embarcados++ \n");

  while(1){
	  if(IORD_32DIRECT(PIO_1_BASE, 0)) {
		  IOWR_32DIRECT(PIO_0_BASE, 0, 0x01 << led++);
		  usleep(50000);
	  }
	  else{
		  led = 0;
	  }
  };

  return 0;
}
