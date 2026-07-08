#ifndef __PORT_TYPES_H__
#define __PORT_TYPES_H__

#include "Std_Types.h"
#include "stm32f407xxx_gpio.h"

#define PORT_PIN_A0     ((0U << 4U) | 0U)
#define PORT_PIN_A1     ((0U << 4U) | 1U)
#define PORT_PIN_A2     ((0U << 4U) | 2U)
#define PORT_PIN_A3     ((0U << 4U) | 3U)
#define PORT_PIN_A4     ((0U << 4U) | 4U)
#define PORT_PIN_A5     ((0U << 4U) | 5U)
#define PORT_PIN_A6     ((0U << 4U) | 6U)
#define PORT_PIN_A7     ((0U << 4U) | 7U)
#define PORT_PIN_A8     ((0U << 4U) | 8U)
#define PORT_PIN_A9     ((0U << 4U) | 9U)
#define PORT_PIN_A10    ((0U << 4U) | 10U)
#define PORT_PIN_A11    ((0U << 4U) | 11U)
#define PORT_PIN_A12    ((0U << 4U) | 12U)
#define PORT_PIN_A13    ((0U << 4U) | 13U)
#define PORT_PIN_A14    ((0U << 4U) | 14U)
#define PORT_PIN_A15    ((0U << 4U) | 15U)

#define PORT_PIN_B0     ((1U << 4U) | 0U)
#define PORT_PIN_B1     ((1U << 4U) | 1U)
#define PORT_PIN_B2     ((1U << 4U) | 2U)
#define PORT_PIN_B3     ((1U << 4U) | 3U)
#define PORT_PIN_B4     ((1U << 4U) | 4U)
#define PORT_PIN_B5     ((1U << 4U) | 5U)
#define PORT_PIN_B6     ((1U << 4U) | 6U)
#define PORT_PIN_B7     ((1U << 4U) | 7U)
#define PORT_PIN_B8     ((1U << 4U) | 8U)
#define PORT_PIN_B9     ((1U << 4U) | 9U)
#define PORT_PIN_B10    ((1U << 4U) | 10U)
#define PORT_PIN_B11    ((1U << 4U) | 11U)
#define PORT_PIN_B12    ((1U << 4U) | 12U)
#define PORT_PIN_B13    ((1U << 4U) | 13U)
#define PORT_PIN_B14    ((1U << 4U) | 14U)
#define PORT_PIN_B15    ((1U << 4U) | 15U)

#define PORT_PIN_C0     ((2U << 4U) | 0U)
#define PORT_PIN_C1     ((2U << 4U) | 1U)
#define PORT_PIN_C2     ((2U << 4U) | 2U)
#define PORT_PIN_C3     ((2U << 4U) | 3U)
#define PORT_PIN_C4     ((2U << 4U) | 4U)
#define PORT_PIN_C5     ((2U << 4U) | 5U)
#define PORT_PIN_C6     ((2U << 4U) | 6U)
#define PORT_PIN_C7     ((2U << 4U) | 7U)
#define PORT_PIN_C8     ((2U << 4U) | 8U)
#define PORT_PIN_C9     ((2U << 4U) | 9U)
#define PORT_PIN_C10    ((2U << 4U) | 10U)
#define PORT_PIN_C11    ((2U << 4U) | 11U)
#define PORT_PIN_C12    ((2U << 4U) | 12U)
#define PORT_PIN_C13    ((2U << 4U) | 13U)
#define PORT_PIN_C14    ((2U << 4U) | 14U)
#define PORT_PIN_C15    ((2U << 4U) | 15U)

#define PORT_PIN_D0     ((3U << 4U) | 0U)
#define PORT_PIN_D1     ((3U << 4U) | 1U)
#define PORT_PIN_D2     ((3U << 4U) | 2U)
#define PORT_PIN_D3     ((3U << 4U) | 3U)
#define PORT_PIN_D4     ((3U << 4U) | 4U)
#define PORT_PIN_D5     ((3U << 4U) | 5U)
#define PORT_PIN_D6     ((3U << 4U) | 6U)
#define PORT_PIN_D7     ((3U << 4U) | 7U)
#define PORT_PIN_D8     ((3U << 4U) | 8U)
#define PORT_PIN_D9     ((3U << 4U) | 9U)
#define PORT_PIN_D10    ((3U << 4U) | 10U)
#define PORT_PIN_D11    ((3U << 4U) | 11U)
#define PORT_PIN_D12    ((3U << 4U) | 12U)
#define PORT_PIN_D13    ((3U << 4U) | 13U)
#define PORT_PIN_D14    ((3U << 4U) | 14U)
#define PORT_PIN_D15    ((3U << 4U) | 15U)

#define PORT_PIN_E0     ((4U << 4U) | 0U)
#define PORT_PIN_E1     ((4U << 4U) | 1U)
#define PORT_PIN_E2     ((4U << 4U) | 2U)
#define PORT_PIN_E3     ((4U << 4U) | 3U)
#define PORT_PIN_E4     ((4U << 4U) | 4U)
#define PORT_PIN_E5     ((4U << 4U) | 5U)
#define PORT_PIN_E6     ((4U << 4U) | 6U)
#define PORT_PIN_E7     ((4U << 4U) | 7U)
#define PORT_PIN_E8     ((4U << 4U) | 8U)
#define PORT_PIN_E9     ((4U << 4U) | 9U)
#define PORT_PIN_E10    ((4U << 4U) | 10U)
#define PORT_PIN_E11    ((4U << 4U) | 11U)
#define PORT_PIN_E12    ((4U << 4U) | 12U)
#define PORT_PIN_E13    ((4U << 4U) | 13U)
#define PORT_PIN_E14    ((4U << 4U) | 14U)
#define PORT_PIN_E15    ((4U << 4U) | 15U)

#define PORT_NUMBER_PIN  16U  /*Number of pin on each port */

/**
 * @brief Type definition for Port Output Speed.
 * The type Port_OspeedType shall be an unsigned integer type that can hold all possible Port Output Speed values.
 */
typedef enum
{
    PORT_OSPEED_LOW = 0x00U,
    PORT_OSPEED_MEDIUM = 0x01U,
    PORT_OSPEED_HIGH,
    PORT_OSPEED_VERY_HIGH
} Port_OspeedType;

/**
 * @brief Type definition for Port Pull-up/Pull-down.
 * The type Port_PullType shall be an unsigned integer type that can hold all possible Port Pull-up/Pull-down values.
 */
typedef enum
{
    PORT_PULL_NONE = 0x00U,
    PORT_PULL_UP,
    PORT_PULL_DOWN
} Port_PinPullType;

/**
 * @brief Type definition for Port Output Type.
 * The type Port_OutputType shall be an enumeration type that can hold all possible Port Output types.
 */
typedef enum
{
    PORT_OUTPUT_PushPull = 0x00U,
    PORT_OUTPUT_OpenDrain
} Port_OutputType;

/**
 * @brief Type definition for Port Pin ID.
 * The type Port_PinType shall be an unsigned integer type that can hold all possible Port Pin IDs. 
 * The range of Port Pin IDs is dependent on the number of Port Pins implemented in the microcontroller.
 */
typedef uint16 Port_PinType; /* Port Pin ID */

/**
 * @brief Type definition for Port Pin Direction.
 * The type Port_PinDirectionType shall be an enumeration type that can hold all possible Port Pin directions.
 */
typedef enum
{
    PORT_PIN_IN  = 0x00U, /* Port Pin configured as input */
    PORT_PIN_OUT = 0x01U /* Port Pin configured as output */
} Port_PinDirectionType;

/**
 * @brief Type definition for Port Pin Mode.
 * The type Port_PinModeType shall be an unsigned integer type that can hold all possible Port Pin modes.
 */
typedef uint8 Port_PinModeType; /* Port Pin Mode Type */

#define PORT_PIN_MODE_INPUT         (Port_PinModeType)0x00U
#define PORT_PIN_MODE_OUTPUT        (Port_PinModeType)0x01U
#define PORT_PIN_MODE_AF            (Port_PinModeType)0x02U
#define PORT_PIN_MODE_ANALOG        (Port_PinModeType)0x03U

typedef uint8 Port_AlternateModeType; /* Port Alternate Function Mode Type */

/**
 * @brief Structure for Port Pin configuration.
 * The contents of the initialization data structure are specific to the microcontroller.
 * The type of the Port Pin configuration structure shall be named Port_PinConfigsType. The structure shall contain at least the following members:
    - PinId: Port Pin ID.
    - PinDirection: Port Pin Direction (input or output).
    - OutputType: Port Output Type (push-pull or open-drain).
    - OutputSpeed: Port Output Speed (low, medium, high, very high).
    - PullUpPullDown: Port Pull-up/Pull-down (none, pull-up, pull-down).
    - InitialValue: Initial level of the pin (STD_LOW or STD_HIGH).
    - PinMode: Port Pin Mode (input, output, alternate function, analog).
    - AlternateFunction: Alternate function mode for the pin (if applicable).
 */
typedef struct 
{
    Port_PinType                PinId; /* Port Pin ID */
    Port_PinDirectionType       PinDirection; /* Port Pin Direction */
    Port_OutputType             OutputType; /* Port Output Type */
    Port_OspeedType             OutputSpeed; /* Port Output Speed */
    Port_PinPullType            PullUpPullDown; /* Port Pull-up/Pull-down */
    uint8                       InitialValue; /* Port Pin Initial Value */  
    Port_PinModeType            PinMode; /* Port Pin Mode */
    Port_AlternateModeType      AlternateFunction; /* Port Alternate Function Mode */
}Port_PinConfigsType;
/*Note: We can using PinDirection or PinMode to configure the pin direction
 STM32 has 4 modes: input, output, alternate function and analog. 
  So we can use PinMode to configure the pin direction and mode in one parameter.
*/

/**
 * @brief Structure for Port initialization configuration.
 * The contents of the initialization data structure are specific to the
    microcontroller.
 */
typedef struct
{
    const Port_PinConfigsType* PinConfigs; /* Pointer to an array of Port_PinConfigsType structures */
    uint8 PinCount; /* Number of Port Pins configured in the array */
} Port_ConfigType;

#endif /* __PORT_TYPES_H__ */