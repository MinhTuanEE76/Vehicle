#include "Can_PBcfg.h"


/*----------------------------------------Configuration Parameter-------------------------------------*/

const Can_BaudrateConfigType Can_BaudrateConfigsData[] =
{
    {
        .BaudrateConfigID = CanConf_CanBaudrate_500K,
        .Prescaler = 6U,
        .SJW = 1U,
        .BS1 = 13U,
        .BS2 = 2U
    },
};

static const Can_FilterConfigType Can_FilterConfigureData[] = 
{
    {
       .FilterEnable = TRUE,
       .FilterMode = CAN_FILTER_MODE_MASK,
       .FilterScale = CAN_FILTER_SCALE_32BIT,
       .FilterMask  = 0x700,
       .FilterId    = 0x100,
       .FifoAssignment = CAN_RX_FIFO0 ,
       .FilterBank = 0U
    }
};

static const Can_HardwareObjectConfigType Can_HohConfigsData[] =
{
    {
        .HohId = CanConf_CanHardwareObject_Rx0,

        .ControllerId = CanConf_CanController_CAN1,

        .ObjectType = CAN_HOH_RECEIVE,
        .FilterConfig = &Can_FilterConfigureData[0]
    },
 
};

static const Can_ControllerConfigType Can_ControllerConfigsData[] =
{
    {
        .ControllerId = CanConf_CanController_CAN1,

        .BaudrateConfig = &Can_BaudrateConfigsData[0],

        .NumBaudrates = 1U,

        .WakeupSupport = TRUE
    }
};

const Can_ConfigType Can_ConfigSets[] = 
{
    {
        .ControllerConfigs = &Can_ControllerConfigsData[0],
        .NumControllers = 1U,
        .NumHohs = 1U,
        .HohConfigs = &Can_HohConfigsData[0]
    }
};

/*---------------------------------------------End configuration-------------------------------------*/

/*-------------------------------Lookup table for hardware object handle ----------------------------*/
const Can_HohLookupType Can_HohLookupTabble[] = 
{
    {
        .HohId        = CanConf_CanHardwareObject_Tx0,
        .ControllerId = CanConf_CanController_CAN1,
        .ObjectType   = CAN_HOH_TRANSMIT
    }
    ,
    {
        .HohId          = CanConf_CanHardwareObject_Tx1,
        .ControllerId   = CanConf_CanController_CAN1,
        .ObjectType     = CAN_HOH_TRANSMIT
    } 
};

const uint8 Can_HohLookupTableSize = sizeof(Can_HohLookupTabble) / sizeof(Can_HohLookupTabble[0]);;

/*-----------------------------Interrupt Configure Table ---------------------------------*/

/**
 * Can_ConfigureInterruptTable using ID to identifier Controller correspond with array order
 */

const Can_ControllerConfigInterruptType Can_ConfigureInterruptTable[] = 
{
    /*Can Controller 1*/
    {
        .TxProcessing = CAN_PROCESSING_POLLING,
        .Rx0Processing = CAN_PROCESSING_INTERRUPT,
        .StatusChangeErrorInterrupt = CAN_PROCESSING_POLLING,
        .Rx1Processing = CAN_PROCESSING_INTERRUPT
    },

    /*Can Controller 2*/
    {
        .TxProcessing = CAN_PROCESSING_POLLING,
        .Rx0Processing = CAN_PROCESSING_INTERRUPT,
        .StatusChangeErrorInterrupt = CAN_PROCESSING_POLLING,
        .Rx1Processing = CAN_PROCESSING_INTERRUPT
    }
};

