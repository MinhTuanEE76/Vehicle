#include "nvic.h"


/**
 * @brief Enable an interrupt line in NVIC
 */
inline void Nvic_EnableIRQ(IRQn_Type IRQn)
{
    if (IRQn < 0)
    {
        return;
    }

    NVIC->ISER[IRQn >> 5U] |= (1U << (IRQn & 0x1FU));    
}

/**
 * @brief Disable an interrupt line in NVIC
 */


inline void Nvic_DisableIRQ(IRQn_Type IRQn)
{
    if (IRQn < 0)
    {
        return;
    }

    NVIC->ICER[((uint32)IRQn >> 5U)] = (1UL << ((uint32)IRQn & 0x1FU));
}

/**
 * @brief Set interrupt priority
 */
void Nvic_SetPriority(IRQn_Type IRQn, uint8 Priority)
{

}

/**
 * @brief Clear pending interrupt
 */
void Nvic_ClearPendingIRQ(IRQn_Type IRQn)
{

}

