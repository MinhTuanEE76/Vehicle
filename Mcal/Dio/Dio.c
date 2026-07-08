#include "Dio.h"

static GPIO_Reg_TypeDef_t* GPIO_Ports_Table[] = 
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH
};

/**
 * @brief Reads the level of a specific channel in the DIO module.
 * @param ChannelId The identifier of the channel to be read.
 * Example: Dio_ReadChannel(DIO_CHANNEL_ID(GROUPA, DIO_CHANNEL_5))
 *  will read the level of channel 5 in port 0 (GPIOA).
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    uint8 port = (ChannelId >> 8) & 0xFF; // Extract the port number from the ChannelId
    uint8 channel = ChannelId & 0xFF; // Extract the channel number from the ChannelId

    return GPIO_Ports_Table[port]->IDR & (1U << channel) ? STD_HIGH : STD_LOW;
}

/**
 * @brief Writes a level to a specific channel in the DIO module.
 * @param ChannelId The identifier of the channel to be written to.
 * @param Level The level to be written to the channel.
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint8 port = ChannelId >> 8U; // Extract the port number from the ChannelId
    uint8 channel = ChannelId & 0xFFU; // Extract the channel number from the ChannelId
    if(Level == STD_HIGH)
    {
        GPIO_Ports_Table[port]->BSRR = (1U << channel); // Set the bit corresponding to the channel
    }
    else
    {
        GPIO_Ports_Table[port]->BSRR = (1U << (channel + 16U)); // Reset the bit corresponding to the channel
    }
}

/**
 * @brief Reads the level of a specific port in the DIO module.
 * @param PortId The identifier of the port to be read.
 * @return The level of the specified port.
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    return GPIO_Ports_Table[PortId]->IDR; // Read the input data register for the specified port
}

/**
 * @brief Writes a level to a specific port in the DIO module.
 * @param PortId The identifier of the port to be written to.
 * @param Level The level to be written to the port.
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    GPIO_Ports_Table[PortId]->ODR = Level; // Write the specified level to the output data register for the specified port
}

/**
 * @brief Flips the level of a specific channel in the DIO module.
 * @param ChannelId The identifier of the channel to be flipped.
 * @return The new level of the channel after flipping.
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    uint8 port = ChannelId >> 8U; // Extract the port number from the ChannelId
    uint8 channel = ChannelId & 0xFFU; // Extract the channel number from the ChannelId

    /*Toggle the bit corresponding to the channel*/
    GPIO_Ports_Table[port]->ODR ^= (1U << channel);

    return GPIO_Ports_Table[port]->ODR & (1U << channel) ? STD_HIGH : STD_LOW;
}
