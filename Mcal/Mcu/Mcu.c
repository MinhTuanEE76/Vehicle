#include "Mcu.h"
#include "stm32f407xxx_rcc.h"

static const Mcu_ConfigType* Mcu_ConfigPtr = NULL_PTR;


/**
 * MCU driver status variable to track initialization state.
 * Initialized to MCU_UNINIT to indicate that the driver is not yet initialized.
 * @brief Mcu_StatusType is an enumeration that defines in Mcu_Private.h.
 */
static Mcu_StatusType Mcu_Status = MCU_UNINIT; 
static Mcu_ClockType Mcu_Clock_Id = MCU_CLOCK_168MHZ; // default Clock ID is a clock0

/*==================================================LOCAL FUNCTION===========================================*/

/**
 * 
 */

uint8 Mcu_lConvertPllpDivtoBitValue(uint8 Pllp)
{
    switch(Pllp)
    {
        case 2U:
            return RCC_PLLP_DIV2;
        case 4U:
            return RCC_PLLP_DIV4;
        case 6U:
            return RCC_PLLP_DIV6;
        case 8U:
            return RCC_PLLP_DIV8;

        default:
            return RCC_PLLP_DIV2;
    }
}


/**
 * @brief: Enable HSE 
 */
static inline void Mcu_lEnableHSE(void)
{
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY))
    {
        //wait to HSERDY is set
    }
}

/**
 * @brief Select Pll Source according to configuration parameter in pointer Mcu_ConfigPtr
 * 0: HSI clock selected as PLL and PLLI2S clock entry
 * 1: HSE oscillator clock selected as PLL and PLLI2S clock entry
 */
static inline void Mcu_lSelectPllSource(const Mcu_ClockConfigType* ClkConfig)
{
    if(ClkConfig->PllSource == MCU_PLL_SOURCE_HSE)
    {
        Mcu_lEnableHSE();
        RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
    }
    if(ClkConfig->PllSource == MCU_PLL_SOURCE_HSI)
    {
        RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
    }
}


/**
 * @brief: configurate clock comply by defined paramaters in ClkConfig
 */
static void Mcu_lConfigurePll(const Mcu_ClockConfigType* ClkConfig)
{
    /*configure PLLQ*/
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;
    RCC->PLLCFGR |= (ClkConfig->PllQ << RCC_PLLCFGR_PLLQ_Pos);
    /*configure PLLM*/
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR |= (ClkConfig->PllM << RCC_PLLCFGR_PLLM_Pos);
    /*Configure PLLN*/
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= (ClkConfig->PllN << RCC_PLLCFGR_PLLN_Pos);
    /*Configure PLLP*/
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
    uint8 Pllp = Mcu_lConvertPllpDivtoBitValue(ClkConfig->PllP);
    RCC->PLLCFGR |= (Pllp << RCC_PLLCFGR_PLLP_Pos);

    /*APB high-speed prescaler (APB2)*/
    RCC->CFGR &= ~RCC_CFGR_PPRE2;
    RCC->CFGR |= (ClkConfig->Apb2Prescaler << RCC_CFGR_PPRE2_Pos);
    /* APB Low speed prescaler (APB1)*/
    RCC->CFGR &= ~ RCC_CFGR_PPRE1;
    RCC->CFGR |= (ClkConfig->Apb1Prescaler << RCC_CFGR_PPRE1_Pos);
    /*AHB prescaler*/
    RCC->CFGR &= ~RCC_CFGR_HPRE;
    RCC->CFGR |= (ClkConfig->AhbPrescaler << RCC_CFGR_HPRE_Pos);
}

/**
 * @brief: Enbale PLL and wait PLL lock -> RCC_CR_PLLRDY is set
 */
static inline void Mcu_lEnablePll(void)
{
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY))
    {
        //wait to PLL ready
    }
}

/**
* @brief: Disabe PLL in to prepare configuration
*/
static inline void Mcu_lDisablePll(void)
{
    RCC->CR &= ~RCC_CR_PLLON;

    while((RCC->CR & RCC_CR_PLLRDY) != 0U)
    {
        /* Wait PLL unlock */
    }
}

/**
 * @brief : function enable clock peripheral such as : UART,I2C,SPI,CAN (no GPIO)
 * This function is called in the Mcu_initClock or Mcu_DistributePll
 */

static void Mcu_lEnablePeripheralClock(void)
{
    RCC_ENABLE_CAN1_CLK();
}
/*==================================================END OF LOCAL FUNCTION====================================*/


/**
 * Initializes the MCU driver.
 * @param ConfigPtr Pointer to the configuration structure.
 * @brief Mcu_Init is only store configuration and set status
 */
void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
    if(ConfigPtr == NULL_PTR)
    {
        // Handle error: Invalid configuration pointer
        return;
    }

    Mcu_ConfigPtr = ConfigPtr;
    Mcu_Status = MCU_INIT;
}


/**
 * Initializes the system clock based on the specified clock setting.
 * @param ClockSetting ID of the clock setting to be applied.
 * @return Std_ReturnType Standard return type.
 */
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    if(Mcu_Status == MCU_UNINIT)
    {
        return E_NOT_OK;
    }

    
    /*Check ClockSetting is validatable*/
    if(ClockSetting >= Mcu_ConfigPtr->NumberOfClockConfigs)
    {
        return E_NOT_OK;
    }
    //assign ClockSetting to Mcu_CLock_Id
    Mcu_Clock_Id = ClockSetting;

    /*Get clock configuration*/
    const Mcu_ClockConfigType* ClockCfg = &(Mcu_ConfigPtr->ClockConfigs[ClockSetting]);

    /*Set Flash Latency*/
    FLASH->ACR &= ~(0xFU);
    FLASH->ACR |= ClockCfg->FlashLatency;
    
    switch(ClockCfg->SystemClockSource)
    {
        case MCU_CLOCK_SOURCE_HSE:
            Mcu_lEnableHSE();
            return E_OK;
            break;

        case MCU_CLOCK_SOURCE_HSI:
            //default HSI on with 16Mhx OSC
            return E_OK;
            break;

        case MCU_CLOCK_SOURCE_PLL:
            /*Disable PLL before configurating*/
            Mcu_lDisablePll();
            /*Select PLL source*/
            Mcu_lSelectPllSource(ClockCfg);
            /*Configure PLL*/
            Mcu_lConfigurePll(ClockCfg);
            /*Enable PLL*/
            Mcu_lEnablePll();

            return E_OK;
            break;

        default:
            return E_NOT_OK;
            break;
    }
}

/**
 * Gets the current PLL lock status.
 * @return Mcu_PllStatusType Current PLL lock status.
 */
Mcu_PllStatusType Mcu_GetPllStatus(void)
{
    if(Mcu_Status == MCU_UNINIT)
    {
        return MCU_PLL_STATUS_UNDEFINED;
    }
    
    if((RCC->CR & RCC_CR_PLLRDY) != 0U)
    {
        return MCU_PLL_LOCKED;
    }

    return MCU_PLL_UNLOCKED;
}

/**
 * Distributes the PLL clock.
 * @return Std_ReturnType Standard return type.
 */
Std_ReturnType Mcu_DistributePllClock(void)
{
    /*check init*/
    if(Mcu_Status == MCU_UNINIT)
    {
        return E_NOT_OK;
    }   

    /*Enable clock peripheral*/
    Mcu_lEnablePeripheralClock();
    
    /*Distribute clock*/
    switch(Mcu_ConfigPtr->ClockConfigs[Mcu_Clock_Id].SystemClockSource)
    {
        case MCU_CLOCK_SOURCE_HSE:
            break;
        case MCU_CLOCK_SOURCE_HSI:
            //already distributed by RCC_CR_HSEON or RCC_CR_HSION
            return E_OK;
            break;

        case MCU_CLOCK_SOURCE_PLL:
            /*Check PLL lock*/
            if(Mcu_GetPllStatus() != MCU_PLL_LOCKED)
            {
                return E_NOT_OK;
            }
            //implement with sysclk = pll
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            //wait sysclk switch
            while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
            {

            }
            return E_OK;
            break;

        default:
            return E_NOT_OK;
            break;
    }
    return E_NOT_OK;
}

/*=============================================================================
 *Extension APIs
 *===========================================================================*/


/**
 * @brief: Get AHB, APB1 and APB2 divider value according to configuration parameter in pointer Mcu_ConfigPtr
 * AHB prescaler can be configured to divide system clock by 1, 2, 4, 8, 16, 64, 128, 256 or 512
 * APB1 prescaler can be configured to divide AHB clock by 1, 2, 4, 8 or 16
 * APB2 prescaler can be configured to divide AHB clock by 1, 2, 4, 8 or 16
 */
static uint32 Mcu_lGetAhbDivider(uint32 Hpre)
{
    switch(Hpre)
    {
        case RCC_CFGR_HPRE_DIV1:
            return 1U;

        case RCC_CFGR_HPRE_DIV2:
            return 2U;

        case RCC_CFGR_HPRE_DIV4:
            return 4U;

        case RCC_CFGR_HPRE_DIV8:
            return 8U;

        case RCC_CFGR_HPRE_DIV16:
            return 16U;

        case RCC_CFGR_HPRE_DIV64:
            return 64U;

        case RCC_CFGR_HPRE_DIV128:
            return 128U;

        case RCC_CFGR_HPRE_DIV256:
            return 256U;

        case RCC_CFGR_HPRE_DIV512:
            return 512U;

        default:
            return 1U;
    }
}

/**
 * @brief Gets the APB1 divider value.
 * @param Ppre1 The APB1 prescaler value.
 * @return uint32 The APB1 divider value.
 */
static uint32 Mcu_lGetApb1Divider(uint32 Ppre1)
{
    switch(Ppre1)
    {
        case RCC_CFGR_PPRE1_DIV1:  return 1U;
        case RCC_CFGR_PPRE1_DIV2:  return 2U;
        case RCC_CFGR_PPRE1_DIV4:  return 4U;
        case RCC_CFGR_PPRE1_DIV8:  return 8U;
        case RCC_CFGR_PPRE1_DIV16: return 16U;
        default: return 1U;
    }
}
/**
 * @brief Gets the APB2 divider value.
 * @param Ppre2 The APB2 prescaler value.
 * @return uint32 The APB2 divider value.
 */
static uint32 Mcu_lGetApb2Divider(uint32 Ppre2)
{
    switch(Ppre2)
    {
        case RCC_CFGR_PPRE2_DIV1:  return 1U;
        case RCC_CFGR_PPRE2_DIV2:  return 2U;
        case RCC_CFGR_PPRE2_DIV4:  return 4U;
        case RCC_CFGR_PPRE2_DIV8:  return 8U;
        case RCC_CFGR_PPRE2_DIV16: return 16U;
        default: return 1U;
    }
}


/**
 * @brief Gets the system clock frequency.
 * @return uint32 The system clock frequency in Hz.
 */
uint32 Mcu_GetSysClkFreq(void)
{
    const Mcu_ClockConfigType* ClockCfg;
    uint32 VcoIn;
    uint32 VcoOut;

    if(Mcu_ConfigPtr == NULL_PTR)
    {
        return 0U;
    }

    ClockCfg = &Mcu_ConfigPtr->ClockConfigs[Mcu_Clock_Id];

    switch(ClockCfg->SystemClockSource)
    {
        case MCU_CLOCK_SOURCE_HSI:
            return 16000000UL;

        case MCU_CLOCK_SOURCE_HSE:
            return ClockCfg->HseFrequency;

        case MCU_CLOCK_SOURCE_PLL:

            if(ClockCfg->PllSource == MCU_PLL_SOURCE_HSE)
            {
                VcoIn = ClockCfg->HseFrequency / ClockCfg->PllM;
            }
            else
            {
                VcoIn = 16000000UL / ClockCfg->PllM;
            }

            VcoOut = VcoIn * ClockCfg->PllN;

            return (VcoOut / ClockCfg->PllP);

        default:
            return 0U;
    }
}

/**
 * @brief Gets the AHB clock frequency.
 * @return uint32 The AHB clock frequency in Hz.
 */
uint32 Mcu_GetHclkFreq(void)
{
    const Mcu_ClockConfigType* ClockCfg;

    if(Mcu_ConfigPtr == NULL_PTR)
    {
        return 0U;
    }

    ClockCfg = &Mcu_ConfigPtr->ClockConfigs[Mcu_Clock_Id];

    return (Mcu_GetSysClkFreq() /
            Mcu_lGetAhbDivider(ClockCfg->AhbPrescaler));
}

uint32 Mcu_GetPclk1Freq(void)
{
    const Mcu_ClockConfigType* ClockCfg;

    if(Mcu_ConfigPtr == NULL_PTR)
    {
        return 0U;
    }

    ClockCfg = &Mcu_ConfigPtr->ClockConfigs[Mcu_Clock_Id];

    return (Mcu_GetHclkFreq() /
            Mcu_lGetApb1Divider(ClockCfg->Apb1Prescaler));
}

uint32 Mcu_GetPclk2Freq(void)
{
    const Mcu_ClockConfigType* ClockCfg;

    if(Mcu_ConfigPtr == NULL_PTR)
    {
        return 0U;
    }

    ClockCfg = &Mcu_ConfigPtr->ClockConfigs[Mcu_Clock_Id];

    return (Mcu_GetHclkFreq() /
            Mcu_lGetApb2Divider(ClockCfg->Apb2Prescaler));
}
