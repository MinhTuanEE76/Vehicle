#include "Port_Cfg.h"
#include "Port_Types.h"
#include "stm32f407xxx_gpio.h"


static const Port_PinConfigsType Port_PinConfigs[] =
{
    /**
     * Configuration for PORTA
     */
    {
        .PinId = PORT_PIN_A7, .PinMode = PORT_PIN_MODE_OUTPUT, .OutputSpeed = PORT_OSPEED_MEDIUM,
        .OutputType = PORT_OUTPUT_PushPull, .PullUpPullDown = PORT_PULL_NONE, .InitialValue = STD_LOW
    },
    
    {
        .PinId = PORT_PIN_A6, .PinMode = PORT_PIN_MODE_OUTPUT, .OutputSpeed = PORT_OSPEED_MEDIUM,
        .OutputType = PORT_OUTPUT_PushPull, .PullUpPullDown = PORT_PULL_NONE, .InitialValue = STD_LOW
    },

    {
        .PinId = PORT_PIN_A11,
        .PinMode = PORT_PIN_MODE_AF,
        .OutputSpeed = PORT_OSPEED_VERY_HIGH,
        .OutputType = PORT_OUTPUT_PushPull,
        .PullUpPullDown = PORT_PULL_UP,
        .AlternateFunction = GPIO_AF_PA11_CAN1_RX,
        .InitialValue = STD_LOW
    },

    {
        .PinId = PORT_PIN_A12,
        .PinMode = PORT_PIN_MODE_AF,
        .OutputSpeed = PORT_OSPEED_VERY_HIGH,
        .OutputType = PORT_OUTPUT_PushPull,
        .PullUpPullDown = PORT_PULL_UP,
        .AlternateFunction = GPIO_AF_PA12_CAN1_TX,
        .InitialValue = STD_LOW
    },
    
    /**
     * Configuration for PORTB
    */
    {
        .PinId = PORT_PIN_B8, .PinMode = PORT_PIN_MODE_OUTPUT, .OutputSpeed = PORT_OSPEED_MEDIUM,
        .OutputType = PORT_OUTPUT_PushPull, .PullUpPullDown = PORT_PULL_NONE, .InitialValue = STD_LOW
    },


    /**
    * Configuration for PORTC
    */
    
    /**
    * Configuration for PORTD
    */

    /** 
    * Configuration for PORTE
    */
};    

/* Port configuration structure instance */
const Port_ConfigType Port_ConfigTable =
{
    .PinConfigs = Port_PinConfigs,
    .PinCount = sizeof(Port_PinConfigs) / sizeof(Port_PinConfigsType)
};