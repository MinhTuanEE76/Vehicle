#ifndef __CAN_H
#define __CAN_H


#include "Can_PBcfg.h"

#include "Can_Internal.h"


/**
 * @brief Initializes the CAN driver.
 * Description: This function initializes the CAN driver by configuring the CAN controller(s) based on the
 * provided configuration structure. It sets up the necessary hardware resources, such as message buffers and interrupts,
 * to enable CAN communication. The configuration structure contains all the necessary parameters for initializing 
 * the CAN controller(s),
 * @param Config Pointer to the configuration structure for the CAN driver.
 *  This structure should be defined according to the specific requirements of the CAN controller being used and may include parameters such as baud rate, message buffer configurations, and interrupt settings.
 */
void Can_Init(const Can_ConfigType* Config);

/**
 * @brief Retrieves the version information of the CAN driver.
 */
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief De-initializes the CAN driver.
 * Description: This function de-initializes the CAN driver by resetting the CAN controller(s)
 */
void Can_DeInt(void);


/**
 * @brief Sets the baud rate for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which the baud rate is to be set.
 * @param BaudRateConfigID The identifier of the baud rate configuration to be applied to the specified CAN controller.
 *  This ID should correspond to a valid baud rate configuration defined in the CAN driver's configuration structure.
 */
void Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);

/**
 * @brief Sets the operating mode of a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which the operating mode is to be set
 * @param Transition The desired operating mode to transition the specified CAN controller to. 
 * This parameter should be of type Can_ControllerStateType and can take values such as 
 * CAN_CS_STARTED, CAN_CS_STOPPED, or CAN_CS_SLEEP, depending on the desired state of the CAN controller.
 */
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);

/**
 * 
 */
Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType* ControllerModePtr);

/**
 * @brief Disables interrupts for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to disable interrupts.
 */
void Can_DisableControllerInterrupts(uint8 Controller);

/**
 * @brief Enables interrupts for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to enable interrupts.
 */
void Can_EnableControllerInterrupts(uint8 Controller);

/**
 * @brief Checks if a specific CAN controller has woken up from sleep mode.
 * @param Controller The identifier of the CAN controller to check for wakeup status.
 */
Std_ReturnType Can_CheckWakeup(uint8 Controller);

/**
 * @brief Retrieves the current error state of a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to retrieve the error state.
 */
Std_ReturnType Can_GetControllerErrorState(uint8 ControllerID, Can_ErrorType* ErrorState);

/**
 * @brief Retrieves the current state of a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to retrieve the current state.
 * Description: Return the Rx counter for a CAN controller. This function is used to monitor the 
 * health of the CAN communication by providing the number of reception errors that have occurred for 
 * the specified CAN controller. The Rx error counter is typically used in conjunction with the Tx error counter
 * to determine the overall error state of the CAN controller and to take appropriate actions, 
 * such as entering a bus-off state if the error count exceeds a certain threshold.
 */
Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerID, uint8* RxErrorCounter);

/**
 * @brief Retrieves the current transmission error counter for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to retrieve the transmission error counter.
 * Description: Return the Tx counter for a CAN controller. This function is used to monitor the health of the 
 * CAN communication by providing the number of transmission errors that have occurred for the specified CAN controller. 
 * The Tx error counter is typically used in conjunction with the Rx error counter to determine the overall error state 
 * of the CAN controller and to take appropriate actions, such as entering a bus-off state if the error count exceeds a 
 * certain threshold.
 */
Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerID, uint8* TxErrorCounter);

/**
 * @brief Transmits a CAN message using a specific CAN controller.
 * @param Hth The hardware transmit handle associated with the CAN controller to be used for transmission.
 * @param PduInfo Pointer to a structure containing the information of the CAN message to be transmitted,
 *  including the CAN identifier, data length, and data bytes.
 */
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo);


#endif /*__CAN_H*/