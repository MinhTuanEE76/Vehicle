#include "Mcu_Cfg.h"
#include "stm32f407xxx_rcc.h"

#ifndef MCU_FLASH_LATENCY_CFG_H
#define MCU_FLASH_LATENCY_CFG_H

#define FLASH_ACR_LATENCY_5WS    5U
#define FLASH_ACR_LATENCY_4WS    4U
#define FLASH_ACR_LATENCY_3WS    3U
#define FLASH_ACR_LATENCY_2WS    2U
#define FLASH_ACR_LATENCY_1WS    1U
#define FLASH_ACR_LATENCY_0WS    0U

#endif /* MCU_FLASH_LATENCY_CFG_H */


/*
 * Clock configuration table.
 *
 * HSE frequency: 8 MHz
 */
static const Mcu_ClockConfigType Mcu_ClockConfig_Data[] =
{
    /*
     * Clock Setting 0
     *
     * PLL Source : HSE (8 MHz)
     * SYSCLK     : 168 MHz
     * AHB Clock  : 168 MHz
     * APB1 Clock : 42 MHz
     * APB2 Clock : 84 MHz
     * USB Clock  : 48 MHz
     */
    {
        .HseFrequency      = 8000000UL,

        .SystemClockSource = MCU_CLOCK_SOURCE_PLL,
        .PllSource         = MCU_PLL_SOURCE_HSE,

        .PllM              = 8U,
        .PllN              = 336U,
        .PllP              = 2U,
        .PllQ              = 7U,

        .AhbPrescaler      = RCC_CFGR_HPRE_DIV1,
        .Apb1Prescaler     = RCC_CFGR_PPRE1_DIV4,
        .Apb2Prescaler     = RCC_CFGR_PPRE2_DIV2,

        .FlashLatency      = FLASH_ACR_LATENCY_5WS
    },

    /*
     * Clock Setting 1
     *
     * PLL Source : HSE (8 MHz)
     * SYSCLK     : 84 MHz
     * AHB Clock  : 84 MHz
     * APB1 Clock : 42 MHz
     * APB2 Clock : 84 MHz
     * USB Clock  : 48 MHz
     */
    {
        .HseFrequency      = 8000000UL,

        .SystemClockSource = MCU_CLOCK_SOURCE_PLL,
        .PllSource         = MCU_PLL_SOURCE_HSE,

        .PllM              = 8U,
        .PllN              = 336U,
        .PllP              = 4U,
        .PllQ              = 7U,

        .AhbPrescaler      = RCC_CFGR_HPRE_DIV1,
        .Apb1Prescaler     = RCC_CFGR_PPRE1_DIV2,
        .Apb2Prescaler     = RCC_CFGR_PPRE2_DIV1,

        .FlashLatency      = FLASH_ACR_LATENCY_2WS
    },

    /*
     * Clock Setting 2
     *
     * PLL Source : HSE (8 MHz)
     * SYSCLK     : 42 MHz
     * AHB Clock  : 42 MHz
     * APB1 Clock : 42 MHz
     * APB2 Clock : 42 MHz
     * USB Clock  : 48 MHz
     */
    {
        .HseFrequency      = 8000000UL,

        .SystemClockSource = MCU_CLOCK_SOURCE_PLL,
        .PllSource         = MCU_PLL_SOURCE_HSE,

        .PllM              = 8U,
        .PllN              = 336U,
        .PllP              = 8U,
        .PllQ              = 7U,

        .AhbPrescaler      = RCC_CFGR_HPRE_DIV1,
        .Apb1Prescaler     = RCC_CFGR_PPRE1_DIV1,
        .Apb2Prescaler     = RCC_CFGR_PPRE2_DIV1,

        .FlashLatency      = FLASH_ACR_LATENCY_1WS
    },

    /*
     * Clock Setting 3
     *
     * System Clock Source : HSE
     * SYSCLK              : 8 MHz
     * PLL                 : Disabled
     */
    {
        .HseFrequency      = 8000000UL,

        .SystemClockSource = MCU_CLOCK_SOURCE_HSE,
        .PllSource         = MCU_PLL_SOURCE_HSE,

        .PllM              = 0U,
        .PllN              = 0U,
        .PllP              = 0U,
        .PllQ              = 0U,

        .AhbPrescaler      = RCC_CFGR_HPRE_DIV1,
        .Apb1Prescaler     = RCC_CFGR_PPRE1_DIV1,
        .Apb2Prescaler     = RCC_CFGR_PPRE2_DIV1,

        .FlashLatency      = FLASH_ACR_LATENCY_0WS
    },

    /*
     * Clock Setting 4
     *
     * System Clock Source : HSI
     * SYSCLK              : 16 MHz
     * PLL                 : Disabled
     */
    {
        .HseFrequency      = 8000000UL,

        .SystemClockSource = MCU_CLOCK_SOURCE_HSI,
        .PllSource         = MCU_PLL_SOURCE_HSI,

        .PllM              = 0U,
        .PllN              = 0U,
        .PllP              = 0U,
        .PllQ              = 0U,

        .AhbPrescaler      = RCC_CFGR_HPRE_DIV1,
        .Apb1Prescaler     = RCC_CFGR_PPRE1_DIV1,
        .Apb2Prescaler     = RCC_CFGR_PPRE2_DIV1,

        .FlashLatency      = FLASH_ACR_LATENCY_0WS
    }
};


const Mcu_ConfigType Mcu_ConfigTable =
{
    .ClockConfigs         = Mcu_ClockConfig_Data,
    .NumberOfClockConfigs = MCU_NUMBER_OF_CLOCK_CONFIGS
};