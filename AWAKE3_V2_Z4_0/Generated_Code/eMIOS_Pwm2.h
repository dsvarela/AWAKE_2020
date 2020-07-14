/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : eMIOS_Pwm2.h
**     Project     : AWAKE3_V2_Z4_0
**     Processor   : MPC5748G_324
**     Component   : emios_pwm
**     Version     : Component SDK_S32_PA_11, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32_PA_11
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-07-14, 16:25, # CodeGen: 0
**     Contents    :
**         EMIOS_DRV_PWM_InitMode                     - status_t EMIOS_DRV_PWM_InitMode(uint8_t emiosGroup, uint8_t channel,...
**         EMIOS_DRV_PWM_ForcePWMMatchLeadingEdge     - void EMIOS_DRV_PWM_ForcePWMMatchLeadingEdge(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_ForcePWMMatchTrailingEdge    - void EMIOS_DRV_PWM_ForcePWMMatchTrailingEdge(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_GetPeriod                    - uint32_t EMIOS_DRV_PWM_GetPeriod(uint8_t emiosGroup, uint8_t channel);
**         EMIOS_DRV_PWM_SetPeriod                    - void EMIOS_DRV_PWM_SetPeriod(uint8_t emiosGroup, uint8_t channel, uint32_t...
**         EMIOS_DRV_PWM_GetDutyCycle                 - uint32_t EMIOS_DRV_PWM_GetDutyCycle(uint8_t emiosGroup, uint8_t channel);
**         EMIOS_DRV_PWM_SetDutyCycle                 - status_t EMIOS_DRV_PWM_SetDutyCycle(uint8_t emiosGroup, uint8_t channel,...
**         EMIOS_DRV_PWM_GetLeadingEdgePlacement      - uint32_t EMIOS_DRV_PWM_GetLeadingEdgePlacement(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_SetLeadingEdgePlacement      - void EMIOS_DRV_PWM_SetLeadingEdgePlacement(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_GetTrailingEdgePlacement     - uint32_t EMIOS_DRV_PWM_GetTrailingEdgePlacement(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_SetTrailingEdgePlacement     - void EMIOS_DRV_PWM_SetTrailingEdgePlacement(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_SetCenterAlignDeadTime       - void EMIOS_DRV_PWM_SetCenterAlignDeadTime(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_GetCenterAlignDeadTime       - uint32_t EMIOS_DRV_PWM_GetCenterAlignDeadTime(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_SetCenterAlignIdealDutyCycle - void EMIOS_DRV_PWM_SetCenterAlignIdealDutyCycle(uint8_t emiosGroup, uint8_t...
**         EMIOS_DRV_PWM_GetCenterAlignIdealDutyCycle - uint32_t EMIOS_DRV_PWM_GetCenterAlignIdealDutyCycle(uint8_t emiosGroup,...
**         EMIOS_DRV_PWM_SetTriggerPlacement          - void EMIOS_DRV_PWM_SetTriggerPlacement(uint8_t emiosGroup, uint8_t channel,...
**         EMIOS_DRV_PWM_GetTriggerPlacement          - uint32_t EMIOS_DRV_PWM_GetTriggerPlacement(uint8_t emiosGroup, uint8_t channel);
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
** @file eMIOS_Pwm2.h
** @version 01.00
*/         
/*!
**  @addtogroup eMIOS_Pwm2_module eMIOS_Pwm2 module documentation
**  @{
*/         
#ifndef eMIOS_Pwm2_H
#define eMIOS_Pwm2_H

/* MODULE eMIOS_Pwm2.
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The global macro will be used in function call of the module.
 */

#include "emios_common.h"
#include "emios_mc_driver.h"
#include "emios_pwm_driver.h"
#include "eMIOS_Mc2.h"
#include "Cpu.h"


/* eMIOS PWM channel for eMIOS_2 */
#define EMIOS_PWM2_CHANNEL14    (14U)
#define EMIOS_PWM2_CHANNEL15    (15U)
#define EMIOS_PWM2_CHANNEL19    (19U)
#define EMIOS_PWM2_CHANNEL20    (20U)
#define EMIOS_PWM2_CHANNEL30    (30U)

/* eMIOS PWM mode configuration structure for eMIOS_2 */
extern emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig0;
extern emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig1;
extern emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig2;
extern emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig3;
extern emios_pwm_param_t eMIOS_Pwm2_PWMChnConfig4;

#endif /* ifndef eMIOS_Pwm2_H */

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
