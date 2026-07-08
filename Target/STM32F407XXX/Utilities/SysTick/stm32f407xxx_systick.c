#include "stm32f407xxx_systick.h"
#include "Mcu.h"

static volatile uint32 Systick_GlobalTick = 0U;


static inline void SYSTICK_IncTick(void);


void SYSTICK_Init(void)
{
    uint32 reload;

    /* SysTick clock source = HCLK */
    reload = (Mcu_GetHclkFreq() / 1000U);

    if ((reload == 0U) || (reload > SYSTICK_MAX_RELOAD))
    {
        return;
    }

    /* Disable SysTick */
    SYSTICK->CTRL = 0U;

    /* Set reload value for 1ms tick */
    SYSTICK->LOAD = reload - 1U;

    /* Clear current value register */
    SYSTICK->VAL = 0U;

    /*
     * CLKSOURCE = 1 -> Processor clock (HCLK)
     * TICKINT   = 1 -> Enable SysTick interrupt
     * ENABLE    = 1 -> Start counter
     */
    SYSTICK->CTRL =
          SYSTICK_CTRL_CLKSOURCE
        | SYSTICK_CTRL_TICKINT
        | SYSTICK_CTRL_ENABLE;
}

void SYSTICK_DelayMs(uint32 DelayMs)
{
    uint32 TickStart = SYSTICK_GetTick();

    while ((SYSTICK_GetTick() - TickStart) < DelayMs)
    {
        /* Wait */
    }
}

uint32 SYSTICK_GetTick(void)
{
    return Systick_GlobalTick;
}

void SysTick_Handler(void)
{
    SYSTICK_IncTick();
}


static inline void SYSTICK_IncTick(void)
{
    Systick_GlobalTick++;
}