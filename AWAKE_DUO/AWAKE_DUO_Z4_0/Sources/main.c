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
#include "emios_hw_access.h"  // Import eMIOS HW Header for direct access to registers, bypassing the functions.
#include "siul2_hw_access.h"  // Import SIUL2 HW Header for direct access to registers, bypassing the functions.
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Values at the memory addresses where the status of each eMIOS channel is stored
#define J13_4_status *(__IO*)0xffc3c290 //eMIOS 2, Channel 19
#define J13_6_status *(__IO*)0xffc3c3f0 //eMIOS 2, Channel 30
#define J13_8_status *(__IO*)0xffc381f0 //eMIOS 0, Channel 14
#define J13_10_status *(__IO*)0xffc382f0 //eMIOS 0, Channel 22
#define J13_14_status *(__IO*)0xffc3c210 //eMIOS 2, Channel 15
#define J13_16_status *(__IO*)0xffc3c1f0 //eMIOS 2, Channel 14

void print(const char *sourceStr){
	uint32_t bytesRemaining = 0U;
	/* Send data via LINFLEXD */
	LINFLEXD_UART_DRV_SendData(INST_LINFLEXD_UART1,(uint8_t *) sourceStr, strlen(sourceStr));
	while(LINFLEXD_UART_DRV_GetTransmitStatus(INST_LINFLEXD_UART1,&bytesRemaining) != STATUS_SUCCESS){}
}

void sysInit(void) {
	/* Initialize and configure pins */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

	/* Initialize clocks */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
			g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	/* Initialize LINFlexD module for UART usage */
	LINFLEXD_UART_DRV_Init(INST_LINFLEXD_UART1, &linflexd_uart1_State, &linflexd_uart1_InitConfig0);

	EMIOS_DRV_InitGlobal(INST_EMIOS_MC2, &eMIOS_Mc2_InitConfig0);
	EMIOS_DRV_MC_InitCounterMode(INST_EMIOS_MC2, EMIOS_CNT_BUSA_DRIVEN,
			&eMIOS_Mc2_CntChnConfig0);
	EMIOS_DRV_PWM_InitMode(INST_EMIOS_MC2, EMIOS_PWM2_CHANNEL20,
			&eMIOS_Pwm2_PWMChnConfig0);
	EMIOS_DRV_PWM_InitMode(INST_EMIOS_MC2, 24, &eMIOS_Pwm2_PWMChnConfig0);

	EMIOS_DRV_EnableGlobalEmios(INST_EMIOS_MC2);
}

/*! 
 \brief The main function for the project.
 \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
 */
int main(void) {
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
#ifdef PEX_RTOS_INIT
	PEX_RTOS_INIT(); /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of Processor Expert internal initialization.                    ***/

	sysInit();

	char buff1[5] = { 0, };
	__IO * J13_2_status = 0xffc3c2b0; //eMIOS 2, Channel 20
	for (;;) {
		//retValue1 = EMIOS_DRV_ReadOutputPinState(INST_EMIOS_MC2, 24);
		sprintf(buff1, "%d", * J13_2_status);
		print(buff1);
	}
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
