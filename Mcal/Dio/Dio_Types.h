#ifndef __DIO_TYPES_H
#define __DIO_TYPES_H

#include "Std_Types.h"
#include "stm32f407xxx.h"

#define DIO_CHANNELS_PER_PORT 16U
#define DIO_PORT_A             0U
#define DIO_PORT_B             1U   
#define DIO_PORT_C             2U
#define DIO_PORT_D             3U
#define DIO_PORT_E             4U
#define DIO_PORT_F             5U
#define DIO_PORT_G             6U
#define DIO_PORT_H             7U


#define DIO_LEVEL_LOW           0U
#define DIO_LEVEL_HIGH          1U

/* Channel definitions for DIO module */
#define DIO_CHANNEL_0          0U
#define DIO_CHANNEL_1          1U
#define DIO_CHANNEL_2          2U
#define DIO_CHANNEL_3          3U
#define DIO_CHANNEL_4          4U
#define DIO_CHANNEL_5          5U
#define DIO_CHANNEL_6          6U
#define DIO_CHANNEL_7          7U
#define DIO_CHANNEL_8          8U
#define DIO_CHANNEL_9          9U
#define DIO_CHANNEL_10         10U
#define DIO_CHANNEL_11         11U
#define DIO_CHANNEL_12         12U
#define DIO_CHANNEL_13         13U
#define DIO_CHANNEL_14         14U
#define DIO_CHANNEL_15         15U

#define DIO_CHANNEL_ID(GROUP, CHANNEL)  (Dio_ChannelType)((GROUP << 8) | CHANNEL)


/**
 * @brief Dio_ChannelType is used to identify a specific channel of the DIO module. 
 * It is defined as an unsigned 8-bit integer (uint8) to allow for a wide range of channel identifiers,
 *  which can be used to represent different pins or channels in the DIO module.
 * Dio_ChanneType will be a unique identifier for each channel in the DIO module,
 * allowing for precise control and access to individual channels when performing read or write operations.
 * last bit 8  bits for channel number, first bit 8 bits for port number
 */
typedef uint16 Dio_ChannelType;


/**
 * @brief Dio_PortType is used to identify a specific port of the DIO module. 
 * It is defined as an unsigned 8-bit integer (uint8) to allow for a wide range of port identifiers,
 *  which can be used to represent different ports in the DIO module.
 */
typedef uint8 Dio_PortType;

/**
 * @brief Dio_ChannelGroupType is a structure that represents a group of channels within a specific port.
 * It contains two members: 'port', which identifies the port to which the channel group belongs, and 'channel',
 * which identifies the specific channel within that port.
 * This structure allows for the grouping of channels within a port, enabling more efficient management and access
 * to multiple channels that belong to the same port in the DIO module.
 */
typedef struct
{
    uint16 mask; /*This element mask which defines the positions of the channel group. */
    uint8 offset; /*This element shall be the position of the Channel Group on the port, counted from the LSB.*/
    Dio_PortType port; /*This shall be the port on which the Channel group is defined */
} Dio_ChannelGroupType;

/**
 * @brief Dio_LevelType is used to represent the level of a DIO channel.
 * It is defined as an unsigned 8-bit integer (uint8) to allow for two distinct levels: 
 * STD_LOW (0) and STD_HIGH (1).
 */
typedef uint8 Dio_LevelType;

/**
 * @brief Dio_PortLevelType is used to represent the level of an entire port in the DIO module.
 * It is defined as an unsigned 16-bit integer (uint16) to allow for a wide range of port level values,
 * which can be used to represent the state of multiple channels within a port simultaneously.
 */
typedef uint16 Dio_PortLevelType;
#endif /*__DIO_TYPES_H*/