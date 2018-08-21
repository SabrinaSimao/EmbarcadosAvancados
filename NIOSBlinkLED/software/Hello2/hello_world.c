#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
volatile int edge_capture;
volatile int flag = 1;

/* Initialize the button_pio. */

#ifdef PIO_1_BASE


static void handle_button_interrupts(void* context, alt_u32 id)

{
    /* Cast context to edge_capture's type. It is important that this be
     * declared volatile to avoid unwanted compiler optimization.
     */
    volatile int* edge_capture_ptr = (volatile int*) context;
    /* Store the value in the Button's edge capture register in *context. */
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
    /* Reset the Button's edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);

    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
}

static void init_button_pio()
{
    /* Recast the edge_capture pointer to match the alt_irq_register() function
     * prototype. */
    void* edge_capture_ptr = (void*) &edge_capture;
    /* Enable all 4 button interrupts. */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0xf);
    /* Reset the edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x0);
    /* Register the interrupt handler. */
    alt_irq_register( PIO_1_IRQ, edge_capture_ptr,
      handle_button_interrupts);
}

#endif /* BUTTON_PIO_BASE */

int main(void){
	flag = 1;
	printf("Embarcados+ \n");

#ifdef PIO_1_BASE
    init_button_pio();
#endif


  unsigned int led = 0;

  printf("Embarcados++ \n");

  while(1){

	  if (edge_capture != 0){
		  flag=!flag;
		  printf("%d", flag);
		  edge_capture = 0;
	  }


	  //printf("Value: %d\n", (IORD_32DIRECT(PIO_1_BASE, 0)) );

	  if(flag) {
		  IOWR_32DIRECT(PIO_0_BASE, 0, 0x01 << led++);
		  usleep(50000);
	  }
	  else{
		  led = 0;
	  }
  };

  return 0;
}
