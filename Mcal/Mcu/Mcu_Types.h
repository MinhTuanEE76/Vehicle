#ifndef __MCU_TYPES_H
#define __MCU_TYPES_H
#include "Std_Types.h"

/*
    This type specifies the system clock source. It is used in the configuration structure of the MCU module.
    Available via Mcu.h
*/
typedef enum
{
    MCU_CLOCK_SOURCE_HSI,
    MCU_CLOCK_SOURCE_HSE,
    MCU_CLOCK_SOURCE_PLL
} Mcu_SystemClockSourceType;
/*
    This type specifies the PLL clock source. It is used in the configuration structure of the MCU module.
    Available via Mcu.h
*/
typedef enum
{
    MCU_PLL_SOURCE_HSI,
    MCU_PLL_SOURCE_HSE
} Mcu_PllSourceType;

/*
 * This type specifies one MCU clock configuration.
 * It contains all parameters required to configure
 * the STM32F407 clock tree.
 *
 * Available via Mcu.h
 */
typedef struct
{
    uint32 HseFrequency;
    uint32 HsiFrequency;

    /*
     * System clock source after initialization.
     */
    Mcu_SystemClockSourceType SystemClockSource;
    /*
     * PLL input clock source.
     */
    Mcu_PllSourceType PllSource;

    uint32 AhbPrescaler;
    uint32 Apb1Prescaler;
    uint32 Apb2Prescaler;
    /*
     * PLL configuration factors.
     *
     * PLL_VCO = PLL_Input / PLLM * PLLN
     * SYSCLK  = PLL_VCO / PLLP
     * USBCLK  = PLL_VCO / PLLQ
     */
    uint8  PllM;
    uint16 PllN;
    uint8  PllP;
    uint8  PllQ;

    uint8 FlashLatency;
} Mcu_ClockConfigType;

/*
 * This type contains all configuration data
 * required by the MCU driver.
 *
 * Available via Mcu.h
 */
typedef struct
{
    /*
     * Pointer to the clock configuration table.
     */
    const Mcu_ClockConfigType *ClockConfigs;

    /*
     * Number of configured clock settings.
     */
    uint8 NumberOfClockConfigs;

} Mcu_ConfigType;

/*
    This is a status value returned by the function Mcu_GetPllStatus of the MCU module
    Available via Mcu.h
*/
typedef enum{
    MCU_PLL_LOCKED = 0U,
    MCU_PLL_UNLOCKED,
    MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

/*
    ThetypeMcu_ClockType defines the identification(ID) for clock
    setting configured via the configuration structure
*/
typedef uint8 Mcu_ClockType;

/*
    This is the type of the reset enumerator containing the subset of reset types. It is not required that
    all reset types are supported by hardware
*/
typedef enum
{
    MCU_POWER_ON_RESET = 0x00U,
    MCU_WATCHDOG_RESET,
    MCU_SW_RESET,
    MCU_RESET_UNDEFINED
} Mcu_ResetType;

/*
    This type specifies the reset reason in raw register format read from a reset status register
*/
typedef uint32 Mcu_RawResetType;
/*
    This type specifies the identification (ID) for a MCU mode, 
    which is configured in the configuration structure.
*/
typedef uint32 Mcu_ModeType;
/**
    This type specifies the identification (ID) for a MCU RAM section,
    which is configured in the configuration structure.
 */
typedef uint32 Mcu_RamSectionType;

/**
    This type specifies the state of a MCU RAM section.
    It is used as return value of the function Mcu_GetRamState.
 */
typedef uint32 Mcu_RamStateType;

#endif /*__MCU_TYPES_H*/

