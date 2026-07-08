#ifndef __COM_STACK_TYPES_H__
#define __COM_STACK_TYPES_H__

#include "Std_Types.h"

/**
 * @brief Represents the identifier of a Protocol Data Unit (PDU).
 * Description: This type is used to uniquely identify a PDU within the communication stack.
 */
typedef uint16 PduIdType; /* Type for PDU identifiers */

/**
 * @brief Represents the length of a Protocol Data Unit (PDU).
 * Description: This type is used to specify the length of a PDU in bytes.
 */
typedef uint16 PduLengthType; /* Type for PDU length */

/**
 * @brief Represents the handle for a Partial Network Cluster (PNC).
 * Description: This type is used to identify specific Partial Network Clusters (PNCs) 
 * within the communication stack. A PNC is a group of nodes that can be woken up together 
 * in a partial network scenario, allowing for power-saving features in automotive communication networks.
 */
typedef uint16 PNCHandleType; /* Type for Partial Network Cluster (PNC) handles */

typedef uint8 NetworkHandleType; /* Type for network handles, if needed in the future */
typedef uint16 CbktHandleType; /* Type for callback handles, if needed in the future . Used for the handle Ids of Com and LdCom user callbacks.*/

/**
 * @brief Enumeration for Transport Protocol (TP) parameters.
 * Description: This enumeration defines the possible parameters that can be used in Transport Protocol (TP)
 * communication, such as Separation Time (STmin), Block Size (BS), and Block Count (BC). These parameters are
 * used to control the flow of data in TP communication, allowing for efficient transmission of large PDUs 
 * that cannot be sent in a single frame. The enumeration values are defined as follows:
 */
typedef enum
{
    TP_STMIN =0x00U, /*Separation Time*/
    TP_BS   =0x01U, /*Block Size*/
    TP_BC   =0x02U, /*Block Count*/
} TPParameterType; /* Enumeration for Transport Protocol (TP) parameters, if needed in the future */

/**
 * @brief Enumeration for buffer request return types.
 * Description: This enumeration defines the possible return types for buffer requests in the communication stack.
 * It can be used to indicate the status of a buffer request, such as whether it was successful, 
 * if there was an error,
 * if the buffer is currently busy, or if a buffer overflow occurred. The enumeration values are defined as follows:
 */
typedef enum
{
    BUFREQ_OK = 0x00U, /* Buffer request successful */
    BUFREQ_E_NOT_OK,   /* Buffer request failed due to an error */
    BUFREQ_E_BUSY,     /* Buffer is currently busy and cannot be used */
    BUFREQ_E_OVFL      /* Buffer overflow occurred */
} BufRequest_ReturnType; /* Enumeration for buffer request return types, if needed in the future */

/**
 * @brief Enumeration for Transport Protocol (TP) data states.
 * Description: This enumeration defines the possible states of data in Transport Protocol (TP) communication.
 * It can be used to indicate whether the data has been successfully transmitted or received, 
 * if a retry is possible in case of a failure, or if the data transmission or reception is pending and waiting for confirmation. 
 * The enumeration values are defined as follows:
 */
typedef enum
{
    TP_DATACONF = 0x00U, /* Data has been successfully transmitted or received */   
    TP_DATARETRY,         /* Data transmission or reception failed, but a retry is possible */
    TP_CONFPENDING,        /* Data transmission or reception is pending and waiting for confirmation */
} TpDataStateType; /* Enumeration for Transport Protocol (TP) data states, if needed in the future */

/**
 * @brief Enumeration for timestamp quality types.
 * Description: This enumeration defines the possible quality types for timestamps in the communication stack.
 */
typedef enum
{
    VALID = 0x00U, /* Timestamp is valid and can be used for processing */
    INVALID,        /* Timestamp is invalid and should not be used for processing */
    UNCERTAIN       /* Timestamp is uncertain and may require additional validation or handling */
} TimeStampQualType;
/**
 * @brief Structure representing the information of a Protocol Data Unit (PDU).
 * Description: This structure contains pointers to the PDU data and metadata, as well as the length of the PDU data.
 * It is used to pass PDU information between different layers of the communication stack.
 * Note: The MetaDataPtr is optional and may be used to store additional information about the PDU,
 *  such as its source or destination address, or any other relevant metadata that may be needed for processing the PDU.
 */
typedef struct
{
    uint8* SduDataPtr; /* Pointer to the PDU data */
    uint8* MetaDataPtr; /* Pointer to the PDU metadata (if applicable) */
    PduLengthType SduLength; /* Length of the PDU data in bytes */
} PduInfoType; /* Type for PDU information */

/**
 * @brief Structure representing the information of a PDU route.
 * Description: This structure contains the identifier of the PDU route and a pointer to the PDU information. 
 * It is used to pass PDU route information between different layers of the communication stack, 
 * allowing for efficient routing and processing of PDUs based on their identifiers.
 */
typedef struct
{
    TpDataStateType TpDataState; /* State of the Transport Protocol (TP) data */
    PduLengthType TxTpDataCnt; /* Count of the TP data that has been transmitted or received */
} RetryInfoType; /* Type for retry information, if needed in the future */

/**
 * @brief Structure representing the information of a PDU route.
 * Description: This structure contains the identifier of the PDU route and a pointer to the PDU information.
 * It is used to pass PDU route information between different layers of the communication stack,
 * allowing for efficient routing and processing of PDUs based on their identifiers.
 * Note: The PduInfoPtr is a pointer to a PduInfoType structure that contains the actual PDU data and metadata,
 * while the PduRouteId is used to identify the specific route that the PDU should take through the communication stack.
 * This structure is essential for managing the flow of PDUs and ensuring that they are processed correctly based on their routes and associated information.
 */
typedef struct
{
    uint32 nanoseconds; /* Type for timestamp information in nanoseconds, if needed in the future */
    uint32 seconds; /* Type for timestamp information in seconds, if needed in the future */
} TimeStampType; 

/**
 * Time tuple structure for ingress/egress timestamping and time quality information.
 * Description: This structure contains the timestamp information for both ingress and egress events, 
 * as well as the quality information for each timestamp.
 */
typedef struct
{
    TimeStampType timestampClockValue; /*Value of the clock, which is used of ingress/egress timestamping*/
    TimeStampType disciplinedClockValue; /*Value of the adjustable HW clock*/
    TimeStampQualType timeQuality; /*Status of time tuple*/
} TimeTupleType; 

/**
 * @brief Structure representing an element in a linked list.
 * Description: This structure contains the data of the list element, as well as a pointer to
 * the next element in the list.
 * Note: The DataLength field specifies the length of the data in bytes, while the DataPtr is a pointer to the actual data.
 * The NextListElemPtr is a pointer to the next element in the linked list, allowing for efficient traversal and management of the list. This structure can be used in various contexts within the communication stack,
 */
//typedef struct
//{
//    uint16 DataLength; /* Length of the data in bytes */
//    uint8* DataPtr; /* Pointer to the data */
//    ListElemStructType* NextListElemPtr; /* Pointer to the next element in the list */
//} ListElemStructType;


#endif /* __COM_STACK_TYPES_H__ */
