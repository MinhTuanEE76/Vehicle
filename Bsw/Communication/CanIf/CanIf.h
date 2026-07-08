#ifndef __CANIF_H
#define __CANIF_H

#include "Can_GeneralTypes.h"


/**
 * @details : 
 * - Transmit and receive path of the corresponding channel are disabled => nocommunication mode
 * - Transmit path of the corresponding channel is disabled. The receive path is enabled
 * - Transmit path of the corresponding channel is in offline active mode (see SWS_CANIF_00072).
 *   The receive path is disabled.This mode requires CanIfTxOfflineActiveSupport = TRUE
 * - Transmit and receive path of the corresponding channel are enabled => full operation mode
 */
typedef enum
{
    CANIF_OFFLINE = 0x00U,
    CANIF_TX_OFFLINE,
    CANIF_TX_OFFLINE_ACTIVE,
    CANIF_ONLINE
} CanIf_PduModeType;

/**
 * @brief Return value of CAN L-PDU notification status.
 */
typedef enum 
{
    CANIF_NO_NOTIFICATION = 0x00U,
    CANIF_TX_RX_NOTIFICATION
} CanIf_NotifStatusType;

/*
    This type defines a data structure for the post build parameters of the CAN interface for all
    underlying CAN drivers. At initialization the CanIf gets a pointer to a structure of this type
    to get access to its configuration data, which is necessary for initialization.
*/
typedef struct 
{

} CanIf_ConfigType;

/*================================Function definitions==============================*/

void CanIf_Init(const CanIf_ConfigType* ConfigPtr);
void CanIf_DeInit(void);

Std_ReturnType CanIf_SetControllerMode (uint8 ControllerId, Can_ControllerStateType ControllerMode);
Std_ReturnType CanIf_GetControllerMode (uint8 ControllerId, Can_ControllerStateType* ControllerModePtr);
Std_ReturnType CanIf_GetControllerErrorState (uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr);

Std_ReturnType CanIf_Transmit (PduIdType TxPduId, const PduInfoType* PduInfoPtr);
Std_ReturnType CanIf_ReadRxPduData (PduIdType CanIfRxSduId, PduInfoType* CanIfRxInfoPtr);

CanIf_NotifStatusType CanIf_ReadTxNotifStatus (PduIdType CanIfTxSduId);
CanIf_NotifStatusType CanIf_ReadRxNotifStatus (PduIdType CanIfRxSduId);

Std_ReturnType CanIf_SetPduMode (uint8 ControllerId, CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_GetPduMode (uint8 ControllerId, CanIf_PduModeType* PduModePtr);

void CanIf_GetVersionInfo (Std_VersionInfoType* VersionInfo);
void CanIf_SetDynamicTxId (PduIdType CanIfTxSduId, Can_IdType CanId);

CanIf_NotifStatusType CanIf_GetTxConfirmationState (uint8 ControllerId);

Std_ReturnType CanIf_SetBaudrate (uint8 ControllerId, uint16 BaudRateConfigID);

Std_ReturnType CanIf_GetControllerRxErrorCounter (uint8 ControllerId, uint8* RxErrorCounterPtr);
Std_ReturnType CanIf_GetControllerTxErrorCounter (uint8 ControllerId, uint8* TxErrorCounterPtr);

Std_ReturnType CanIf_EnableBusMirroring (uint8 ControllerId, boolean MirroringActive);

/*=====================================Callback notifications===================================*/

Std_ReturnType CanIf_TriggerTransmit (PduIdType TxPduId, PduInfoType* PduInfoPtr);
void CanIf_TxConfirmation (PduIdType CanTxPduId);
void CanIf_RxIndication (const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);
void CanIf_ControllerBusOff (uint8 ControllerId);

void CanIf_ConfirmPnAvailability (uint8 TransceiverId);
void CanIf_ClearTrcvWufFlagIndication (uint8 TransceiverId);
void CanIf_CheckTrcvWakeFlagIndication (uint8 TransceiverId);


void CanIf_ControllerModeIndication (uint8 ControllerId, Can_ControllerStateType ControllerMode);
void CanIf_ErrorNotification (uint8 ControllerId,Can_ErrorType Can_ErrorType);



#endif /*CanIf.h*/