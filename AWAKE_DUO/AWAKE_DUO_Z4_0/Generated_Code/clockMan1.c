/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : clockMan1.c
**     Project     : AWAKE_DUO_Z4_0
**     Processor   : MPC5748G_324
**     Component   : clock_manager
**     Version     : Component SDK_S32_PA_11, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32_PA_11
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-07-15, 12:18, # CodeGen: 1
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
** @file clockMan1.c
** @version 01.00
*/         
/*!
**  @addtogroup clockMan1_module clockMan1 module documentation
**  @{
*/         

/* clockMan1. */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files, with the same initialized values.
 */

#include "clockMan1.h"
/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 9.4, Duplicate initialization of object element.
 * It's the only way to initialize an array that is member of struct.
 *
 */
/* *************************************************************************    
 * Configuration structure for peripheral clock configuration 0
 * ************************************************************************* */
/*! @brief peripheral clock configuration 0 */     
mc_me_peripheral_clock_config_t peripheralClockMcMeConfig0[] = {
    {
        .clockName                      = DMA0_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = PITRTI0_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = SIUL0_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = eMIOS0_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = eMIOS1_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = eMIOS2_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = ENET0_TIME_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = ENET1_TIME_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
    {
        .clockName                      = PIT0_CLK,
        .mc_me_RunPeriphConfig          = MC_ME_PERIPH_CONFIG_1,
        .mc_me_LowPowerPeriphConfig     = MC_ME_PERIPH_CONFIG_1,
    },
};

/* *************************************************************************    
 * Configuration structure for Clock Configuration 0
 * ************************************************************************* */
/*! @brief User Configuration structure clock_managerCfg_0 */     
clock_manager_user_config_t clockMan1_InitConfig0 = {

    /*! @brief Configuration of MC_ME */
    .mcmeConfig =
    {
        .run0 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .run1 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .run2 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .run3 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .drun =
        {
            .clocksEnabled =
            {
                .irc0          = true,
                .irc1          = true,
                .xosc0         = true,
                .xosc1         = true,
                .pll0          = true,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_PLL_PHI0,    
        },
    
        .stop0 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .standby0 =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .safe =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .reset =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
    
    
        .lpurun =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .lpustop =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .lpustandby =
        {
            .clocksEnabled =
            {
                .irc0          = false,
                .irc1          = true,
                .xosc0         = false,
                .xosc1         = false,
                .pll0          = false,
            },       
            .sysclk            = CGM_SYSTEM_CLOCK_SRC_FIRC,    
        },
    
        .periphRunConfig =
        {
            {
                /* MC_ME_PERIPH_CONFIG_0 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_1 */
                .reset              = false,
                .safe               = true,                
                .test               = false,
                .drun               = true,                
                .run0               = true,                
                .run1               = true,                
                .run2               = true,                
                .run3               = true,                
            },
            {
                /* MC_ME_PERIPH_CONFIG_2 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_3 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_4 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_5 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_6 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_7 */
                .reset              = false,
                .safe               = false,
                .test               = false,
                .drun               = false,
                .run0               = false,
                .run1               = false,
                .run2               = false,
                .run3               = false,
            },
        },        
        .periphLowPowerConfig =
        {
            {
                /* MC_ME_PERIPH_CONFIG_0 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_1 */
                .halt0               = false,
                .standby0            = true,                
                .stop0               = true,                
            },
            {
                /* MC_ME_PERIPH_CONFIG_2 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_3 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_4 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_5 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_6 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
            {
                /* MC_ME_PERIPH_CONFIG_7 */
                .halt0               = false,
                .standby0            = false,
                .stop0               = false,
            },
        },        
        .count                    = 9,
        .peripherals              = peripheralClockMcMeConfig0,
    },
    
    .cgmConfig =
    {
        .sc_dc0              = CGM_CLOCK_DIV_BY_1,
        .sc_dc1              = CGM_CLOCK_DIV_BY_2,
        .sc_dc2              = CGM_CLOCK_DIV_BY_4,
        .sc_dc3              = CGM_CLOCK_DIV_BY_4,
        .sc_dc4              = CGM_CLOCK_DIV_BY_2,
        .sc_dc5              = CGM_CLOCK_DIV_BY_2,
        .sc_dc6              = CGM_CLOCK_DIV_BY_8,
    
        .ac2_sc              = CGM_ENETx_SOURCE_F40,
        
        .ac4_sc              = CGM_USDHCx_SOURCE_F40,
        
        .ac5_sc              = CGM_PLL_REFERENCE_FXOSC,
        
        .ac6_sc              = CGM_CLOCKOUT0_SRC_FXOSC,
        .ac6_dc0             = CGM_CLOCK_DIV_BY_1,
        
        .ac8_sc              = CGM_SPI0_SOURCE_F40,
        
        .ac9_sc              = CGM_FLEXCANx_SOURCE_FS80,
        
        .clkout1_sc          = CGM_CLOCKOUT1_SRC_FXOSC_DIVIDED,
        .clkout1_dc          = CGM_CLOCK_DIV_BY_1,
        
    },
        
    .cgmcsConfig =
    {
        .irc0Config =
        {
            .divider = IRC_CLOCK_DIV_BY_1,
        },
        .irc1Config =
        {
            .divider = IRC_CLOCK_DIV_BY_1,
        },
        .xosc0Config =
        {
            .freq               = 32768,
            .autoLevelControl   = true,
            .startupDelay       = 1,
            .divider            = XOSC_CLOCK_DIV_BY_1,
        },
        .xosc1Config =
        {
            .freq               = 40000000,
            .startupDelay       = 1,
            .divider            = XOSC_CLOCK_DIV_BY_1,
            .bypassOption       = XOSC_USE_CRYSTAL,
            .mode               = XOSC_FULL_SWING_PIERCE_MODE,
        },
        .pll0Config =
        {
            .predivider                   = PLLDIG_CLOCK_PREDIV_BY_2,
            .denominatorFracLoopDiv       = 9999,
            .numeratorFracLoopDiv         = 0,
            .mulFactorDiv                 = 32,
            .phi0Divider                  = PLLDIG_PHI_DIV_BY_4,
            .phi1Divider                  = PLLDIG_PHI_DIV_BY_8,
            .modulation                   = false,
            .modulationPeriod             = 0,
            .incrementStep                = 0,                
            .sigmaDelta                   = false,
            .secondOrderSigmaDelta        = false,
            .thirdOrderSigmaDelta         = false,
            .ditherControl                = false,
            .ditherControlValue           = 0,
        },
        .enetExtClkFreq0               = 50000000,
    },
    
    .cmuConfig =
    {
        .cmu_rcdiv0               = CMU_LO_FREQ_1,                   /* Lowest accepted frequency divider */

        .cmu = 
        {
            {
                .enable           = false,                           /* CMU_0 disabled                    */
                .lo_freq          = 0,                               /* Lowest accepted frequency         */
                .hi_freq          = 4095,                            /* Highest accepted frequency        */
            },
        },
    },
	  
};        

/*! @brief Array of pointers to User configuration structures */
clock_manager_user_config_t const * g_clockManConfigsArr[] = {
    &clockMan1_InitConfig0
};
/*! @brief Array of pointers to User defined Callbacks configuration structures */
clock_manager_callback_user_config_t * g_clockManCallbacksArr[] = {(void*)0};
/* END clockMan1. */

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
