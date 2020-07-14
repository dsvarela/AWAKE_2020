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
#include <math.h>

#define RED 			10
#define RED_PORT 		PTA
#define GREEN 			7
#define GREEN_PORT 		PTA
#define BEG				0
#define BEG_PORT 		PTA
#define END 			4
#define END_PORT 		PTA

/* Global Variables */
int config = 0;  // Assert whether the configurations have already been uploaded by the user.
int Count = 0;
// Write eMIOS Module and Channel of pins in the board in the following order:
// {J13.2, J13.4, J13.6, J13.8, J13.\0, J13.14, J13.16}
int Module = 2;
int Channel = 20;
uint32_t retValue1 = 0;


void sysInit(void)
{
	/* Initialize and configure pins */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

	PINS_DRV_TogglePins(RED_PORT, (1<<RED));
	PINS_DRV_TogglePins(GREEN_PORT, (1<<GREEN));
	PINS_DRV_TogglePins(BEG_PORT, (1<<BEG));
	PINS_DRV_TogglePins(END_PORT, (1<<END));

	/* Initialize clocks */
	CLOCK_SYS_Init(g_clockManConfigsArr,   CLOCK_MANAGER_CONFIG_CNT,
			g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	/* Initialize LINFlexD module for UART usage */
	LINFLEXD_UART_DRV_Init(INST_LINFLEXD_UART1, &linflexd_uart1_State, &linflexd_uart1_InitConfig0);
}

void eMIOSInit(void){
	/* eMIOS counter BUS A (MCB Mode) initialized on eMIOS 2 Module. */
	EMIOS_DRV_MC_InitCounterMode(INST_EMIOS_MC2, EMIOS_CNT_BUSA_DRIVEN, &eMIOS_Mc2_CntChnConfig0);  // Drive J13.2, J13.4, J13.6, J13.14, J13.16

	/* eMIOS PWM mode Initialization for eMIOS2 */
	EMIOS_DRV_PWM_InitMode(INST_EMIOS_MC2, EMIOS_PWM2_CHANNEL20, &eMIOS_Pwm2_PWMChnConfig3);  // J13.2 - PF[20]

	/* If you want initialize eMIOS Global */
	EMIOS_DRV_InitGlobal(INST_EMIOS_MC2, &eMIOS_Mc2_InitConfig0);  // Init eMIOS2 with initial configurations

	eMIOS_MCR_SET_GTBE(2, 0UL);  // Enable eMIOS2
}

void eMIOSConfig(int *Loop, int *Period, int *LEdge, int *TEdge){

	eMIOS_MCR_SET_GPREN(2, 0UL);  // Enable eMIOS2
	eMIOS_MCR_SET_GTBE(2, 0UL);  // Enable eMIOS2

	/* If you want initialize eMIOS Global */
	//eMIOS_Mc1_InitConfig0.clkDivVal = *Global;
	EMIOS_DRV_InitGlobal(INST_EMIOS_MC2, &eMIOS_Mc2_InitConfig0);  // Init eMIOS2 with initial configurations

	// Drive J13.2
	eMIOS_Mc2_CntChnConfig0.period = *Period;
	EMIOS_DRV_MC_InitCounterMode(INST_EMIOS_MC2, EMIOS_CNT_BUSA_DRIVEN, &eMIOS_Mc2_CntChnConfig0);

	/* eMIOS PWM mode Initialization for eMIOS2 */
	// J13.2 - PF[20]
	eMIOS_Pwm2_PWMChnConfig3.dutyCycleCount = *Period;
	eMIOS_Pwm2_PWMChnConfig3.triggerEventPlacement = *TEdge + 1UL;
	EMIOS_DRV_PWM_InitMode(INST_EMIOS_MC2, EMIOS_PWM2_CHANNEL20, &eMIOS_Pwm2_PWMChnConfig3);

	// Loop to set Leading and Trailing Edge Positions on every pin.
	EMIOS_DRV_PWM_SetLeadingEdgePlacement(Module,  Channel, *LEdge + 1UL);
	EMIOS_DRV_PWM_SetTrailingEdgePlacement(Module, Channel, *TEdge + 1UL);

	eMIOS_MCR_SET_GPREN(2, 1UL);  // Enable eMIOS2
	/* Enable global timebase */
	eMIOS_MCR_SET_GTBE(2, 0UL);  // Disable Global Timebase on eMIOS2
}

void eMIOSReset(void){
	/* Enable global prescaler */
	eMIOS_MCR_SET_GPREN(2, 0UL);  // Disable eMIOS2
	/* Enable global timebase */
	eMIOS_MCR_SET_GTBE(2, 0UL);  // Disable Global Timebase on eMIOS2

	/* eMIOS Counter mode Initialization for eMIOS_Mc_CntChnConfig0 */
	EMIOS_DRV_MC_InitCounterMode(INST_EMIOS_MC2, EMIOS_CNT_BUSA_DRIVEN, &eMIOS_Mc2_CntChnConfig0);

	/* Enable global prescaler */
	eMIOS_MCR_SET_GPREN(2, 1UL);  // Disable eMIOS2
	/* Enable global timebase */
	eMIOS_MCR_SET_GTBE(2, 0UL);  // Disable Global Timebase on eMIOS2
}

/*
 * print((const char *)".");
 *
 */
void print(const char *sourceStr){
	uint32_t bytesRemaining = 0U;
	/* Send data via LINFLEXD */
	LINFLEXD_UART_DRV_SendData(INST_LINFLEXD_UART1,(uint8_t *) sourceStr, strlen(sourceStr));
	while(LINFLEXD_UART_DRV_GetTransmitStatus(INST_LINFLEXD_UART1,&bytesRemaining) != STATUS_SUCCESS){}
}

//Reads a char sent to check if connection is established and what button was pressed by the user in the GUI.
int readOption(){
	uint8_t strReceived = 0U;
	uint8_t buffer[1] = {'\0'};
	uint32_t byteRemaining = 0U;
	while(strReceived == 0U)
	{
		/* Because the terminal appends new line to user data,
		 * receive and store data into a buffer until it is received
		 */
		LINFLEXD_UART_DRV_ReceiveData(INST_LINFLEXD_UART1,buffer, 1U);
		while(LINFLEXD_UART_DRV_GetReceiveStatus(INST_LINFLEXD_UART1,&byteRemaining) != STATUS_SUCCESS){}
		strReceived = 1U;
	}
	if (buffer[0] == 's'){
		return 1;
	}
	else if (buffer[0] == 'i'){
		return 2;
	}
	else return 0;
}

int readCycles(int *Loop, int *Period, int *LEdge, int *TEdge)
{

	//Read Incoming String
	bool strReceived = false;
	uint8_t buf_read[128] = {'\0', }; //The buffer is as big as the biggest possible incoming string. Alter if input changes.
	uint8_t i = 0;
	uint32_t bytesRemaining = 0U;
	while(strReceived == false)
	{
		/* Because the terminal appends new line to user data,
		 * receive and store data into a buffer until it is received
		 */
		LINFLEXD_UART_DRV_ReceiveData(INST_LINFLEXD_UART1, &buf_read[i], 1UL);
		/* Wait for transfer to be completed */
		while(LINFLEXD_UART_DRV_GetReceiveStatus(INST_LINFLEXD_UART1, &bytesRemaining) != STATUS_SUCCESS);
		/* Check if current byte is new line */
		if(buf_read[i++] == '\n')
			strReceived = true;
	}
	strtok((char *)buf_read, "\n"); //Clear the \n from the incoming string.
	char temp[5]={'\0', }; //Temp variable for assigning the incoming string to the struct.

	/*
	 * Sequentially get the comma separated string and extract each value.
	 */
	strcpy(temp, strtok((char *)buf_read, ","));
	int PNum = atoi(temp);  // Number of times to repeat the Pulse
	memset(temp, '\0', 5);

	strcpy(temp, strtok(NULL, ","));
	(*Loop) = atoi(temp);
	memset(temp, '\0', 5);

	strcpy(temp, strtok(NULL, ","));
	(*Period) = atoi(temp);
	memset(temp, '\0', 5);

	strcpy(temp, strtok(NULL, ","));
	(*LEdge) = atoi(temp);
	memset(temp, '\0', 5);

	strcpy(temp, strtok(NULL, ","));
	(*TEdge) = atoi(temp);
	memset(temp, '\0', 5);

	return PNum;
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
	int Button;  // Store integer corresponding to the user's input on the GUI.
	int enable = 0;  // Flag the current state of the eMIOS channel.
	int PNum = 0;  // Number of times to repeat the Total Period.
	int m;
	int n;
	int Loop = NULL;
	// Period on eMIOS
	int Period = NULL;
	// Array to store the Leading Edge / Trigger on all configurable PWM outputs.
	int LEdge = NULL;
	// Array to store the Trailing Edge / Trigger on all configurable PWM outputs.
	int TEdge = NULL;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
#ifdef PEX_RTOS_INIT
	PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Initialize peripheral driver */
	sysInit();
	// eMIOSInit();

	/* Infinite loop */
	while(1)
	{
		while(1){
			Button = readOption();  //Read what button has been pressed in the GUI.
			if (Button != 0){
				break;
			}
		}
		print((const char *)".");  //Send confirmation receipt.
		PINS_DRV_TogglePins(BEG_PORT, (1<<BEG));

		if (Button == 2){
			PINS_DRV_TogglePins(RED_PORT, (1<<RED));
			if (config == 1){
				if (enable == 0){
					enable=1;  // Use variable to remember the eMIOS channels are on.
				}

			}
		}

		if (Button == 1){
			PINS_DRV_TogglePins(GREEN_PORT, (1<<GREEN));
			PNum = readCycles(&Loop, &Period, &LEdge, &TEdge);
			print((const char *)".");  //Send confirmation receipt.

			// Write Received Parameters to the respective pins.
			eMIOSConfig(&Loop, &Period, &LEdge, &TEdge);

			// Enable Interrupt Request on Channel with the Maximum Trailing Edge
			EMIOS_DRV_ChannelEnableInterruptRequest(Module, Channel);

			config = 1;
		}

		if (enable == 1){
			PINS_DRV_TogglePins(END_PORT, (1<<END));
			// eMIOS_MCR_SET_GPREN(0, 1UL);  // Enable eMIOS0
			// eMIOS_MCR_SET_GPREN(2, 1UL);  // Enable eMIOS2
			eMIOS_MCR_SET_GTBE(2, 1UL);  // Enable Global Timebase on eMIOS1 (so eMIOS0 and eMIOS2 sync with eMIOS1)

			for(n = 0; n < PNum; n++){
				// Read Flag State of Channel with the latest trailing edge
				while(!((EMIOS_GET_REG(eMIOS[Module]->GFLAG, EMIOS_REGISTER_F31_F0_MASK, EMIOS_REGISTER_F31_F0_SHIFT) >> Channel) & 0x01UL)){
					// Do nothing while this flag isn't set.
				}

			    retValue1 = 0;
			    /* Capture value in interrupt */
			    EMIOS_DRV_IC_GetLastMeasurement(INST_EMIOS_MC1, EMIOS_IC1_CHANNEL11, &retValue1);
			    //sprintf(buff1, '%d', retValue1);

				// Set Register B (Trailing Edge) in all Pins to be the same as Register A (Leading Edge), disabling the Pulse.
				REG_RMW32(&eMIOS[INST_EMIOS_MC2]->UC[EMIOS_PWM2_CHANNEL20].B, eMIOS_B_B_MASK, eMIOS_B_B(LEdge + 1UL));

				// Set the Channel Flag State of the Channel with the last Trailing Edge Back Low
				REG_RMW32(&eMIOS[Module]->UC[Channel].S, (eMIOS_S_FLAG_MASK & eMIOS_S_OVFL_MASK) & eMIOS_S_OVR_MASK, eMIOS_S_FLAG(1UL));

				// Mute Outputs the number of times necessary to finish the milliseconds time interval.
				for (m = 0; m < Loop; m++){
					// Read Flag State of Channel 31 on eMIOS1
					while(!((EMIOS_GET_REG(eMIOS[Module]->GFLAG, EMIOS_REGISTER_F31_F0_MASK, EMIOS_REGISTER_F31_F0_SHIFT) >> Channel) & 0x01UL)){
						// Do nothing while this flag isn't set.
					}
					// Set Channel 31 Flag State Back Low
					REG_RMW32(&eMIOS[Module]->UC[Channel].S, (eMIOS_S_FLAG_MASK & eMIOS_S_OVFL_MASK) & eMIOS_S_OVR_MASK, eMIOS_S_FLAG(1UL));
				}

			    retValue1 = 0;
			    /* Capture value in interrupt */
			    EMIOS_DRV_IC_GetLastMeasurement(INST_EMIOS_MC1, EMIOS_IC1_CHANNEL11, &retValue1);
			    //sprintf(buff1, '%d', retValue1);

				// Set Register B back to calculated value, Re-enabling the pulse.
				REG_RMW32(&eMIOS[INST_EMIOS_MC2]->UC[EMIOS_PWM2_CHANNEL20].B, eMIOS_B_B_MASK, eMIOS_B_B(TEdge + 1UL));

				// Set Channel Flag State Back Low
				REG_RMW32(&eMIOS[Module]->UC[Channel].S, (eMIOS_S_FLAG_MASK & eMIOS_S_OVFL_MASK) & eMIOS_S_OVR_MASK, eMIOS_S_FLAG(1UL));
			}

			// Stop clock, reset them and set everything for the next loop.
			eMIOSReset();
			// Disable Interrupt Request on Channel with the Maximum Trailing Edge
			EMIOS_SetUCRegCFen(Module, Channel, 0UL);
			enable = 0;
			print((const char *)".");  //Send confirmation receipt.
			PINS_DRV_TogglePins(BEG_PORT, (1<<BEG));
			PINS_DRV_TogglePins(END_PORT, (1<<END));
			PINS_DRV_TogglePins(RED_PORT, (1<<RED));
		}
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
