#ifndef __MCU_H
#define __MCU_H

#include "Mcu_Types.h"
#include "Mcu_Private.h"
#include "Mcu_Cfg.h"

#define MCU_INIT_SID                  (0x00U)
#define MCU_INITRAMSECTION_SID        (0x01U)
#define MCU_INITCLOCK_SID             (0x02U)
#define MCU_DISTRIBUTE_PLL_CLOCK_SID  (0x03U)
#define MCU_GET_PLL_STATUS_SID        (0x04U)
#define MCU_GET_RESET_REASON_SID      (0x05U)
#define MCU_GET_RESET_RAW_VALUE_SID   (0x06U)
#define MCU_PERFORM_RESET_SID         (0x07U)

#define MCU_CLOCK_168MHZ               0U
#define MCU_CLOCK_84MHZ                1U
#define MCU_CLOCK_42MHZ                2U
#define MCU_CLOCK_HSE                  3U
#define MCU_CLOCK_HSI                  4U

/**
 * Initializes the MCU driver.
 * @param ConfigPtr Pointer to the configuration structure.
 */
void Mcu_Init(const Mcu_ConfigType* ConfigPtr);

/**
 * Initializes a RAM section.
 * @param RamSection ID of the RAM section to be initialized.
 * @return Std_ReturnType Standard return type.
 */
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection);

/**
 * Initializes the system clock based on the specified clock setting.
 * @param ClockSetting ID of the clock setting to be applied.
 * @return Std_ReturnType Standard return type.
 */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);

/**
 * Distributes the PLL clock.
 * @return Std_ReturnType Standard return type.
 */
Std_ReturnType Mcu_DistributePllClock(void);

/**
 * Gets the current PLL lock status.
 * @return Mcu_PllStatusType Current PLL lock status.
 */
Mcu_PllStatusType Mcu_GetPllStatus(void);

/**
 * Gets the current reset reason.
 * @return Mcu_ResetType Current reset reason.
 */
Mcu_ResetType Mcu_GetResetReason(void);

/**
 * Gets the current reset reason in raw register format.
 * @return Mcu_RawResetType Current reset reason in raw register format.
 */
Mcu_RawResetType Mcu_GetResetRawValue(void);

/**
 * Performs a system reset.
 */
void Mcu_PerformReset(void);

/**
 * Sets the MCU mode.
 * @param McuMode ID of the MCU mode to be set.
 */
void Mcu_SetMode(Mcu_ModeType McuMode);

/**
 * Gets the version information of the MCU driver.
 * @param versioninfo Pointer to the version information structure.
 */
void Mcu_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * Gets the status of a RAM section.
 * @param RamSection ID of the RAM section to be checked.
 * @return Mcu_RamStateType Status of the specified RAM section.
 */
Mcu_RamStateType Mcu_GetRamState(Mcu_RamSectionType RamSection);



/******************************************************************************
 * Extension APIs
 *
 * AUTOSAR MCU Driver does not define APIs to retrieve calculated
 * SYSCLK/HCLK/PCLK frequencies.
 *
 * These helper functions are provided for application and
 * peripheral driver usage.
 ******************************************************************************/
uint32 Mcu_GetSysClkFreq(void);
uint32 Mcu_GetHclkFreq(void);
uint32 Mcu_GetPclk1Freq(void);
uint32 Mcu_GetPclk2Freq(void);

#endif /* __MCU_H */
