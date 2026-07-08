#include "ScheM_Can.h"
#include "stm32f407xxx_can.h"

extern Can_ControllerStateType Can_ControllerState[CAN_MAX_CONTROLLERS];

extern CAN_Reg_TypeDef_t* Can_ControllerInstance[CAN_MAX_CONTROLLERS];


/*This 2-demention array is imported from Can.c use to read status and swPduHandle of specific Tx Mailbox*/
extern Can_TxMailboxContextType Can_TxMailboxContext[CAN_NUMBER_CONTROLLERS][CAN_NUMBER_TX_MAILBOXES];


/**
 * @brief: This function performs the polling of TX confirmation when CAN_TX_PROCESSING is set
 * to POLLING
 */
void Can_MainFunction_Write(void)
{
    for(uint8 i = 0 ; i < CAN_NUMBER_CONTROLLERS ; i++)
    {
        for(uint8 j = 0 ; j < CAN_NUMBER_TX_MAILBOXES ; j++)
        {
            switch(j)
            {
                case CAN_TX_MAILBOX_0:
                    if(Can_ControllerInstance[i]->TSR & CAN_TSR_RQCP0)
                    {
                        if(Can_ControllerInstance[i]->TSR & CAN_TSR_TXOK0)
                        {
                            if(Can_TxMailboxContext[i][j].Busy == TRUE)
                            {
                                CanIf_TxConfirmation(Can_TxMailboxContext[i][j].SwPduHandle);
                            }
                        }
                        /*release Context*/
                        Can_TxMailboxContext[i][j].Busy = FALSE;
                        /*clear RQCP*/
                        Can_ControllerInstance[i]->TSR |= CAN_TSR_RQCP0;
                    }
                    break;

                case CAN_TX_MAILBOX_1:
                    if(Can_ControllerInstance[i]->TSR & CAN_TSR_RQCP1)
                    {
                        if(Can_ControllerInstance[i]->TSR & CAN_TSR_TXOK1)
                        {
                            if(Can_TxMailboxContext[i][j].Busy == TRUE)
                            {
                                CanIf_TxConfirmation(Can_TxMailboxContext[i][j].SwPduHandle);
                            }
                        }
                        /*release Context*/
                        Can_TxMailboxContext[i][j].Busy = FALSE;
                        /*clear RQCP*/
                        Can_ControllerInstance[i]->TSR |= CAN_TSR_RQCP1;
                    }
                    break;

                case CAN_TX_MAILBOX_2:
                    if(Can_ControllerInstance[i]->TSR & CAN_TSR_RQCP2)
                    {
                        if(Can_ControllerInstance[i]->TSR & CAN_TSR_TXOK2)
                        {
                            if(Can_TxMailboxContext[i][j].Busy == TRUE)
                            {
                                CanIf_TxConfirmation(Can_TxMailboxContext[i][j].SwPduHandle);
                            }
                        }
                        /*release Context*/
                        Can_TxMailboxContext[i][j].Busy = FALSE;
                        /*clear RQCP*/
                        Can_ControllerInstance[i]->TSR |= CAN_TSR_RQCP2;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }
}

#define RX_FIFO_BUFFER_SIZE   8U /*uint in byte*/

/**
 * 
 */
static inline Std_ReturnType ScheMCan_lHwReadRxFifo0(uint8 ControllerId, Can_HwType* pv_Mailbox, 
                                                    PduInfoType* pv_PduInforPtr, uint8* swRxfifo_Buffer)
{
    if(Can_ControllerInstance[ControllerId]->RF0R & CAN_RF0R_FMP0)
    {
        /*At here at least one message is pending in the FIFO*/
        uint8 DataLengthCode = Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RDTR & CAN_RDTR_DLC;
        /*by the way, save the length into pv_PduInforPtr*/
        pv_PduInforPtr->SduLength = DataLengthCode;
        for(uint8 i = 0U ; i < DataLengthCode ; i++)
        {
            if(i < 4U)
            {
                swRxfifo_Buffer[i] = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RDLR >> (8U*i));
            }
            else
            {
                swRxfifo_Buffer[i] = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RDHR >> (8U*(i - 4U)));
            }
        }
    }
    else
    {
        return  E_NOT_OK;
    }
    /*Pass pointer address to SduDataPtr of struct PduInfor*/
    pv_PduInforPtr->SduDataPtr = swRxfifo_Buffer;

    /*Packing infomation*/
    pv_Mailbox->Hoh = CanConf_CanHardwareObject_Rx0;
    pv_Mailbox->ControllerId = ControllerId;
    /*Shaping CanId according to autosar requirements*/
    if(Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RIR & CAN_RIR_IDE)
    {
        /*At here, ID 29 bits*/
        pv_Mailbox->CanId = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RIR >> 3U ) & 0x1FFFFFFFU ;
    }
    else
    {
        /*At here, ID 11 bits*/
        pv_Mailbox->CanId = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[0].RIR & CAN_RIR_STID) >> 3U;
    }

    /*Release Rx Fifo*/
    Can_ControllerInstance[ControllerId]->RF0R |= CAN_RF0R_RFOM0;
    return E_OK;
}

/**
 * 
 */
static inline Std_ReturnType ScheMCan_lHwReadRxFifo1(uint8 ControllerId, Can_HwType* pv_Mailbox, 
                                                    PduInfoType* pv_PduInforPtr, uint8* swRxfifo_Buffer)
{
    if(Can_ControllerInstance[ControllerId]->RF1R & CAN_RF1R_FMP1)
    {
        /*At here at least one message is pending in the FIFO*/
        uint8 DataLengthCode = Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RDTR & CAN_RDTR_DLC;
        /*by the way, save the length into pv_PduInforPtr*/
        pv_PduInforPtr->SduLength = DataLengthCode;
        for(uint8 i = 0U ; i < DataLengthCode ; i++)
        {
            if(i < 4U)
            {
                swRxfifo_Buffer[i] = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RDLR >> (8U*i));
            }
            else
            {
                swRxfifo_Buffer[i] = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RDHR >> (8U*(i - 4U)));
            }
        }
    }
    else
    {
        return E_NOT_OK;
    }

    /*Pass pointer address to SduDataPtr of struct PduInfor*/
    pv_PduInforPtr->SduDataPtr = swRxfifo_Buffer;
    pv_Mailbox->ControllerId = ControllerId;
    /*Packing infomation*/
    pv_Mailbox->Hoh = CanConf_CanHardwareObject_Rx1;
    /*Shaping CanId according to autosar requirements*/
    if(Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RIR & CAN_RIR_IDE)
    {
        /*At here, ID 29 bits*/
        pv_Mailbox->CanId = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RIR >> 3U) & 0x1FFFFFFFU ;
    }
    else
    {
        /*At here, ID 11 bits*/
        pv_Mailbox->CanId = (Can_ControllerInstance[ControllerId]->sFIFOMailBox[1].RIR & CAN_RIR_STID) >> 3U;
    }  
    
    /*Release Rx Fifo*/
    Can_ControllerInstance[ControllerId]->RF1R |= CAN_RF1R_RFOM1;
    return E_OK;
}


/**
 * 
 */
static inline Std_ReturnType ScheMCan_lGetFrameFromRxFifo(uint8 ControllerID, uint8 RxFifoID,
                                            Can_HwType* pv_Mailbox, PduInfoType* pvPduInfoPtr, uint8* swRxfifo_Buffer)
{
    switch(RxFifoID)
    {
        case CAN_RX_FIFO0:
            return ScheMCan_lHwReadRxFifo0(ControllerID,pv_Mailbox,pvPduInfoPtr,swRxfifo_Buffer);
            break;
        case CAN_RX_FIFO1:
            return ScheMCan_lHwReadRxFifo1(ControllerID,pv_Mailbox,pvPduInfoPtr,swRxfifo_Buffer);
            break;
        default:
            return E_NOT_OK;
            break;
    }
}


/**
 * @brief: This function performs the polling of RX indication when CAN_RX_PROCESSING is set
 * to POLLING
 */
void Can_MainFunction_Read(void)
{
    uint8 swRxfifo_Buffer[RX_FIFO_BUFFER_SIZE];
    Can_HwType pv_Mailbox;
    PduInfoType pv_PduInforPtr;

    for(uint8 i = 0 ; i < CAN_NUMBER_CONTROLLERS ; i++)
    {
        for(uint8 j = 0 ; j < CAN_NUMBER_RX_FIFOS ; j++)
        {
            while(ScheMCan_lGetFrameFromRxFifo(i,j,&pv_Mailbox,&pv_PduInforPtr,swRxfifo_Buffer) == E_OK)
            {
                CanIf_RxIndication(&pv_Mailbox,&pv_PduInforPtr);
                /*Fifo have been released in ScheMCan_lGetFrameFromRxFifo when it return E_OK*/
            }            
        }
    } 
}