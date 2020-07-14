/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ###################################################################
 **     Filename    : main.c
 **     Processor   : MPC574xG
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.00
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"

volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "siul2_hw_access.h"  // Import SIUL2 HW Header for direct access to registers, bypassing the functions.
#define LED1        (1<<10)	/* GPIO  10 - pin PA[10] */
#define LED2        (1<<7)  	/* GPIO 7 - pin PA[7] */
#define LED7        (1<<0)    /* GPIO 0 - pin PA[0] */
#define LED8        (1<<4)	/* GPIO   4 - pin PA[4] */
#define LED_PORT     PTA      /* base pointer */
/*
 * PIT's Channel 0 interrupt handler
 * It toggles the LED1 once half a second
 */
void PIT_Ch0_IRQHandler(void)
{
	LED_PORT->PGPDO ^= REV_BIT_16(LED1);
	LED_PORT->PGPDO ^= REV_BIT_16(LED2);
	LED_PORT->PGPDO ^= REV_BIT_16(LED7);
	LED_PORT->PGPDO ^= REV_BIT_16(LED8);
	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig0.hwChannel);     /* Clear channel 0 interrupt flag */
}

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
 */
int main(void)
{
	/* Write your local variable definition here */
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
#ifdef PEX_RTOS_INIT
	PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Initialize clocks */
	CLOCK_SYS_Init(g_clockManConfigsArr,   CLOCK_MANAGER_CONFIG_CNT,
			g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	/* Initialize and configure pins */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
	/* Initialize PIT */
	/* It needs to be done only once */
	PIT_DRV_Init(INST_PIT1, &pit1_InitConfig);
	/* Disable PIT channel 0 interrupt for all cores*/
	/* This is done because all interrupts are enabled on core Z4_0 by default*/
	INT_SYS_DisableIRQ_MC_All(PIT_Ch0_IRQn);
	/* Initialize PIT channel 0 */
	PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig0);
	/* Start PIT channel 0 counting */
	PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig0.hwChannel);

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for(;;) {
		if(exit_code != 0) {
			break;
		}
	}
	return exit_code;
	/*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.1 [05.21]
 **     for the NXP C55 series of microcontrollers.
 **
 ** ###################################################################
 */
