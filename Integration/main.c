#include "Port.h"
#include "Mcu.h"
#include "Dio.h"
#include "Can.h"
#include "stm32f407xxx_systick.h"


int main(void)
{
    /* Initialize the MCU */
    Mcu_Init(&Mcu_ConfigTable);
    Mcu_InitClock(MCU_CLOCK_168MHZ); /* Select clock setting 0 from the configuration table */
    Mcu_DistributePllClock();
    /* Initialize the Port driver with the configuration structure */
    Port_Init(&Port_ConfigTable);
    /* Initialize the SysTick timer */
    SYSTICK_Init();

    Can_Init(Can_ConfigSets);
    while(1)
    {
        Dio_FlipChannel(DIO_CHANNEL_ID(DIO_PORT_A,DIO_CHANNEL_6));
        Dio_FlipChannel(DIO_CHANNEL_ID(DIO_PORT_B,DIO_CHANNEL_8));

        SYSTICK_DelayMs(500);      /* Delay 500ms */
    }

    return 0;
}
