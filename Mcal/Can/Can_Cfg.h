#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Can_GeneralTypes.h"

#define CAN_MAX_CONTROLLERS         0x02U
#define CAN_MAX_HOHS                5U


/* Controller Symbolic Names */

#define CanConf_CanController_CAN1      ((uint8)0U)
#define CanConf_CanController_CAN2      ((uint8)1U)

#define CanConf_CanBaudrate_500K        ((uint16)0U)
#define CanConf_CanBaudrate_1M          ((uint16)1U)

#define CanConf_CanHardwareObject_Tx0   ((Can_HwHandleType)0U)
#define CanConf_CanHardwareObject_Tx1   ((Can_HwHandleType)1U)
#define CanConf_CanHardwareObject_Tx2   ((Can_HwHandleType)2U)

#define CanConf_CanHardwareObject_Rx0   ((Can_HwHandleType)3U)
#define CanConf_CanHardwareObject_Rx1   ((Can_HwHandleType)4U)

#define CAN_HW_TX_MAILBOX0     0U
#define CAN_HW_TX_MAILBOX1     1U
#define CAN_HW_TX_MAILBOX2     2U

#define CAN_HW_RX_FIFO0        0U
#define CAN_HW_RX_FIFO1        1U

#define CAN_TX_MAILBOX0_IS_FREE     0U
#define CAN_TX_MAILBOX1_IS_FREE     1U
#define CAN_TX_MAILBOX2_IS_FREE     2U
#define CAN_TX_MAILBOX_IS_BUSY      3U

#define CAN_NUMBER_CONTROLLERS      2U
#define CAN_NUMBER_TX_MAILBOXES     3U
#define CAN_NUMBER_RX_FIFOS         2U

typedef uint32 Can_InterruptMaskType;

#define CAN_INT_NONE               ((Can_InterruptMaskType)0UL)

/* TX */
#define CAN_INT_TX                 ((Can_InterruptMaskType)(1UL << 0))

/* RX FIFO0 */
#define CAN_INT_RX0_PENDING        ((Can_InterruptMaskType)(1UL << 1))
#define CAN_INT_RX0_FULL           ((Can_InterruptMaskType)(1UL << 2))
#define CAN_INT_RX0_OVERRUN        ((Can_InterruptMaskType)(1UL << 3))

/* RX FIFO1 */
#define CAN_INT_RX1_PENDING        ((Can_InterruptMaskType)(1UL << 4))
#define CAN_INT_RX1_FULL           ((Can_InterruptMaskType)(1UL << 5))
#define CAN_INT_RX1_OVERRUN        ((Can_InterruptMaskType)(1UL << 6))

/* Error */
#define CAN_INT_ERROR_WARNING      ((Can_InterruptMaskType)(1UL << 7))
#define CAN_INT_ERROR_PASSIVE      ((Can_InterruptMaskType)(1UL << 8))
#define CAN_INT_BUSOFF             ((Can_InterruptMaskType)(1UL << 9))
#define CAN_INT_LAST_ERROR         ((Can_InterruptMaskType)(1UL << 10))

/* Status */
#define CAN_INT_WAKEUP             ((Can_InterruptMaskType)(1UL << 11))
#define CAN_INT_SLEEP              ((Can_InterruptMaskType)(1UL << 12))



/**
 * @brief CAN baudrate configuration.
 *
 * Each baudrate configuration can be selected
 * at runtime using Can_SetBaudrate().
 */
typedef struct
{
    uint16 BaudrateConfigID;

    uint16 Prescaler;
    uint8 SJW;
    uint8 BS1;
    uint8 BS2;

} Can_BaudrateConfigType;

/**
 * @brief Configuration of a CAN controller.
 *
 * This structure contains all configuration parameters
 * required to initialize a CAN controller instance.
 *
 * Each CAN controller configured in the ECU shall have
 * exactly one instance of this structure.
 */
typedef struct
{
    uint8 ControllerId;

    const Can_BaudrateConfigType* BaudrateConfig;

    uint8 NumBaudrates;

    boolean WakeupSupport;

} Can_ControllerConfigType;


typedef enum
{
    CAN_FILTER_MODE_MASK,
    CAN_FILTER_MODE_LIST
} Can_FilterModeType;

typedef enum
{
    CAN_FILTER_SCALE_16BIT,
    CAN_FILTER_SCALE_32BIT
} Can_FilterScaleType;

typedef enum
{
    CAN_RX_FIFO0 = 0U,
    CAN_RX_FIFO1
} Can_RxFifoType;

typedef struct
{
    boolean FilterEnable;

    uint8 FilterBank;

    Can_FilterModeType FilterMode;

    Can_FilterScaleType FilterScale;

    uint32 FilterId;

    uint32 FilterMask;

    Can_RxFifoType FifoAssignment;

} Can_FilterConfigType;

/**
 * @brief Hardware Object configuration.
 *
 * Represents either an HRH or HTH.
 */
typedef struct
{
    Can_HwHandleType HohId;

    uint8 ControllerId;

    Can_HohType ObjectType;

    const Can_FilterConfigType* FilterConfig; 

} Can_HardwareObjectConfigType;

/**
 * @brief:type for Lookup table to mapping AUTOSAR hoh ID-> CAN Hardwar
 */
typedef struct
{
    Can_HwHandleType HohId;
    uint8 ControllerId;
    Can_HohType ObjectType;
} Can_HohLookupType;

/**
 * @brief CAN Driver configuration container.
 *
 * Root configuration structure passed to Can_Init().
 *
 * It contains references to:
 *  - CAN controllers
 *  - Hardware Objects (HRH/HTH)
 *  - Baudrate configurations
 *
 * Content is hardware specific.
 */
typedef struct
{
    const Can_ControllerConfigType* ControllerConfigs;
    uint8 NumControllers;
    const Can_HardwareObjectConfigType* HohConfigs;
    uint16 NumHohs;
} Can_ConfigType;

/**
 * 
 */
typedef struct
{
    boolean Busy;
    PduIdType SwPduHandle;
} Can_TxMailboxContextType;

/**
 * 
 */
typedef enum
{
    CAN_PROCESSING_POLLING,
    CAN_PROCESSING_INTERRUPT
} Can_ProcessingType;

/**
 * Event flags and interrupt generation
 */
typedef struct
{
    Can_ProcessingType Rx0Processing;
    Can_ProcessingType Rx1Processing;
    Can_ProcessingType TxProcessing;
    Can_ProcessingType StatusChangeErrorInterrupt;
} Can_ControllerConfigInterruptType;



#endif