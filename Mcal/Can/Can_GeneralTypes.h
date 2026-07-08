#ifndef __CAN_TYPES_H__
#define __CAN_TYPES_H__

#include "Std_Types.h"
#include "Com_StackTypes.h"

/**
 * @brief Represents the identifier of an L-PDU.
 * The two most significant bits specify the frame type:
 * 00 - CAN message with Standard CAN ID
 * 01 - CAN FD frame with Standard CAN ID
 * 10 - CAN message with Extended CAN ID
 * 11 - CAN FD frame with Extended CAN ID
 */
typedef uint32 Can_IdType;



/**
 * @brief Represents the handle for a hardware object (e.g., a CAN controller or a message buffer).
 * This type is used to identify specific hardware resources within the CAN driver.
 */
typedef uint32 Can_HwHandleType; /* Type for hardware object handles */

/**
 * @brief Enumeration for CAN error states
 * Description: This enumeration defines the possible error states of a CAN controller.
 */
typedef enum
{
    CAN_ERRORSTATE_ACTIVE , //The CAN controller takes fully part in communication.
    CAN_ERRORSTATE_PASSIVE, //The CAN controller takes part in communication but with limited functionality.
    CAN_ERRORSTATE_BUSOFF   //The CAN controller is switched off and does not take part in communication.
} Can_ErrorStateType;

/**
 * @brief Enumeration for CAN controller states
 * Description: This enumeration defines the possible states of a CAN controller.
 */
typedef enum
{
    CAN_CS_UNINIT = 0x00U,  // The CAN controller is uninitialized
    CAN_CS_STARTED,   // The CAN controller is started and operational
    CAN_CS_STOPPED,   // The CAN controller is stopped and not operational
    CAN_CS_SLEEP      // The CAN controller is in sleep mode (if supported)
} Can_ControllerStateType;


/**
 * @brief Hardware object type.
 *
 * HRH : Receive object.
 * HTH : Transmit object.
 */
typedef enum
{
    CAN_HOH_RECEIVE = 0U,
    CAN_HOH_TRANSMIT
} Can_HohType;

/**
 * @brief Enumeration for CAN error types
 * Description: This enumeration defines the possible error types that can occur during CAN communication.
 */
typedef enum
{
    CAN_ERROR_BIT_MONITORING1 = 0x01U,      //A 0 was transmitted and a 1 was readback
    CAN_ERROR_BIT_MONITORING2 = 0x02U,      //A 1 was transmitted and a 0 was readback, or a dominant level was expected but a recessive level was read back
    CAN_ERROR_BIT             = 0x03U,      //The HW detected a bit error during transmission or reception
    CAN_ERROR_CHECK_ACK_FAILED,             //Acknowledgment check failed
    CAN_ERROR_ACK_DELIMITER   ,             //Acknowledgement delimiter check failed
    CAN_ERROR_ARBITRATION_LOST,             //Arbitration lost during transmission
    CAN_ERROR_OVERLOAD        ,             //Overload condition occurred   
    CAN_ERROR_CHECK_FORM_FAILED,            //Form check failed (e.g., fixed format of the CAN frame is not met)    
    CAN_ERROR_CHECK_STUFFING_FAILED,        //Stuffing check failed (e.g., more than 5 consecutive bits of the same level were detected)
    CAN_ERROR_CHECK_CRC_FAILED,             //CRC check failed (e.g., the calculated CRC value does not match the received CRC value)
    CAN_ERROR_BUS_LOCK                      //Bus lock condition occurred (e.g., the CAN controller has entered a bus-off state due to excessive errors)
} Can_ErrorType;

/**
 * @brief Structure for CAN PDU (Protocol Data Unit)
 * Description: This is the type of the data structure used to represent a CAN message
 * in the driver interface.
 * This type unites PduId(swPduHandle),SduLength(length),SduData(sdu),and CanId(id) for any CANL-SDU.
 */
typedef struct
{
    PduIdType swPduHandle; /* Unique ID for the PDU */
    uint8 length;          /* Length of the CAN message in bytes */
    Can_IdType id;         /* CAN identifier (11-bit or 29-bit) */
    uint8* sdu;           /* Pointer to the CAN message data (up to 8 bytes) */
} Can_PduType;  

/**
 * @brief Structure for CAN hardware-specific information
 * Description: This is the type of the data structure used to represent hardware-specific information
 */
typedef struct
{
    Can_IdType CanId ;        /* Standard/Extended CANID of CANL-PDU */
    Can_HwHandleType Hoh;     /* ID of the corresponding Hardware Object Range */
    uint8 ControllerId;       /* ID of the corresponding CAN controller */
} Can_HwType;

/**
 * @brief Structure for CAN timestamp
 * Description: This is the type of the data structure used to represent a timestamp for CAN messages 
 */
typedef struct
{
    uint32 nanoseconds;
    uint32 seconds;
} Can_TimeStampType;

#endif /* __CAN_TYPES_H__ */