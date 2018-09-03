#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> /* Leiutura e escrita no Avalon */
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_alarm.h"



volatile int edge_capture;
volatile int flag = 1;

/* Initialize the button_pio. */

static void handle_button_interrupts(void* context, alt_u32 id)

{
	printf("Entrou button\n");

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



static void handle_timer_interrupt(void*p, alt_u32 param)
{
   printf("Entrou timerrr\n");
   //clear
   IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
   printf("Entrou\n");

}


static void tc_init(int freq){

	 // alt_sysclk_init (freq);

	  /* set to free running mode */

	  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_0_BASE,
	            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
	            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
	            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

		 IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0x03E8);
		 IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0);

	  alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, handle_timer_interrupt,
			  TIMER_0_BASE, NULL);

}

int main(void){
	flag = 1;
	printf("Embarcados+ \n");

	 // Timer initialization
	 /*alt_irq_register(TIMER_0_IRQ, 0, handle_timer_interrupt);

	 // activate the time
	 IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
	                 ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
	               | ALTERA_AVALON_TIMER_CONTROL_START_MSK
	               | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

	 IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0x03E8);
	 IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0);

	//IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
	//                                                 | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
	//IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);    // Clear IRQ status just in case..
	//IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, ALTERA_AVALON_TIMER_PERIODL_MSK);
	//IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, ALTERA_AVALON_TIMER_PERIODH_MSK);
*/

	//alt_avalon_timer_sc_init(TIMER_0_BASE, TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
	//		TIMER_0_IRQ, 5);



#ifdef PIO_1_BASE
    init_button_pio();
#endif


  unsigned int led = 0;

  printf("Embarcados++ \n");

  tc_init(NIOS2_CPU_FREQ);

  while(1){

	  if (edge_capture != 0){
		  flag=!flag;
		  //printf("%d", flag);
		  edge_capture = 0;
	  }


	  //printf("Value: %d\n", (IORD_32DIRECT(PIO_1_BASE, 0)) );

	  if(flag) {

		  IOWR_32DIRECT(PIO_0_BASE, 0, 0x3F);
		  usleep(500000);
		  IOWR_32DIRECT(PIO_0_BASE, 0, 0x00);
		  usleep(500000);
	  }
	  else{
		  led = 0;
	  }
  };

  return 0;
}
