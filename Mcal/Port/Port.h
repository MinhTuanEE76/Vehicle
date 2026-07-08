#ifndef __PORT_H
#define __PORT_H


#include "Port_Types.h"
#include "Port_Cfg.h"


/**
 * @brief Initializes the Port driver.
 * @param ConfigPtr Pointer to the configuration structure.
 */
void Port_Init(const Port_ConfigType* ConfigPtr);

/**
 * @brief Sets the direction of a specific pin.
 * @param Pin The ID of the pin to configure.
 * @param Direction The direction to set.
 */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

/**
 * @brief Refreshes the direction of all configured pins to their initial state.
 */
void Port_RefreshPortDirection(void);

/**
 * @brief Gets the version information of the Port driver.
 * @param versioninfo Pointer to the version information structure.
 */
void Port_GetVersionInfo(const Std_VersionInfoType* versioninfo);

/**
 * @brief Sets the mode of a specific pin.
 * @param Pin The ID of the pin to configure.
 * @param Mode The mode to set.
 */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);


#endif /* __PORT_H */