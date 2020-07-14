/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : eMIOS_Pwm2.c
**     Project     : AWAKE_SINGLE_Z4_0
**     Processor   : MPC5748G_324
**     Component   : emios_pwm
**     Version     : Component SDK_S32_PA_11, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32_PA_11
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-06-20, 02:31, # CodeGen: 7
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc. 
**     Copyright 2016-2017 NXP 
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file eMIOS_Pwm2.c
** @version 01.00
*/         
/*!
**  @addtogroup eMIOS_Pwm2_module eMIOS_Pwm2 module documentation
**  @{
*/         

/* Module eMIOS_Pwm2.
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, external symbol defined without a prior
 * declaration.
 * The symbols are declared in the driver header as external; the header is not included
 * by this file.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variable will be used in other source files in application code.
 */

#include "eMIOS_Pwm2.h"



/* eMIOS PWM mode configuration structure */
/* eMIOS PWM mode configuration structure for eMIOS_Pwm2_PWMChnConfig3 */
emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig3 =
{
    .mode                  = EMIOS_MODE_OPWMT,             /*!< Sub-mode selected             */
    .internalPrescaler     = EMIOS_CLOCK_DIVID_BY_1,       /*!< Internal prescaler value      */
    .internalPrescalerEn   = true,                         /*!< Internal prescaler is enabled */
    .outputActiveMode      = EMIOS_POSITIVE_PULSE,         /*!< Output active value, active low or high level */
    .periodCount           = 65535UL,                      /*!< Period count         */
    .dutyCycleCount        = 0UL,                          /*!< Duty cycle count     */
    .timebase              = EMIOS_BUS_SEL_A,              /*!< Counter bus selected */
    .idealDutyCycle        = 1UL,                          /*!< Ideal duty cycle value using to compare with the selected time base */
    .triggerEventPlacement = 0UL,                          /*!< Trigger Event placement */
    .deadTime              = 0UL                           /*!< The dead time value and is compared against the internal counter */
};

/* END eMIOS_Pwm2. */

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
