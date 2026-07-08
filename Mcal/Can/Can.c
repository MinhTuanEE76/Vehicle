#include "Can.h"
#include "stm32f407xxx_can.h"
#include "Mcu.h"

static const Can_ConfigType *ConfigPtr = NULL_PTR;
static const Can_BaudrateConfigType *BaudConfigPtr = Can_BaudrateConfigsData;

static Can_DriverStateType Can_DriverState = CAN_UNINIT;

Can_ControllerStateType Can_ControllerState[CAN_MAX_CONTROLLERS];

CAN_Reg_TypeDef_t* Can_ControllerInstance[CAN_MAX_CONTROLLERS] =
{
    CAN1,
    CAN2
};

Can_TxMailboxContextType Can_TxMailboxContext[CAN_NUMBER_CONTROLLERS][CAN_NUMBER_TX_MAILBOXES];

static void Can_Hw_InitControlller(const Can_ControllerConfigType *ControllerCfg);
static void Can_Hw_InitHwObject(const Can_HardwareObjectConfigType *HohCfg);
static void Can_lHwInitHth(const Can_HardwareObjectConfigType *HthCfg);
static void Can_lHwInitHrh(const Can_HardwareObjectConfigType *HrhCfg);

/*========================================Start local function===================================*/

/**
 * @brief Function initial Can controller which will be used
 * @param none use global ConfigPtr pointer that contain configuration infor
 */
static void Can_lInitController(void)
{
    for (uint8 i = 0; i < ConfigPtr->NumControllers; i++)
    {
        const Can_ControllerConfigType *ControllerCfg = &ConfigPtr->ControllerConfigs[i];
        // set controller state
        Can_ControllerState[i] = CAN_CS_STOPPED;
        Can_Hw_InitControlller(ControllerCfg);
    }
}

/**
 * @brief Function initial Hardware Object
 * use pointer ConfigPtr to confgire
 */
static void Can_lInitHardwareObject(void)
{
    for(uint8 i = 0 ; i < ConfigPtr->NumHohs ; i++)
    {
        const Can_HardwareObjectConfigType* HwObjectCfg = &ConfigPtr->HohConfigs[i];
        Can_Hw_InitHwObject(HwObjectCfg);
    }
}

/**/
static void Can_Hw_InitControlller(const Can_ControllerConfigType *ControllerCfg)
{
    CAN_Reg_TypeDef_t *Instance = Can_ControllerInstance[ControllerCfg->ControllerId];
    /*Manipulate register to convert to CAN_CS_STOP */
    Instance->MCR |= CAN_MCR_INRQ;
    while (!(Instance->MSR & CAN_MSR_INAK))
    {
        // wait to InitRequest ACK
        /*future: add timeout */
    }

    /*Note: to configure controller, state is must be STOP*/
    Can_SetBaudrate(ControllerCfg->ControllerId, ControllerCfg->BaudrateConfig->BaudrateConfigID);
    Instance->MCR &= ~CAN_MCR_INRQ;
    while (Instance->MSR & CAN_MSR_INAK)
    {
       /*wait to  CAN_MCR_INRQ = 0*/
    }
    
}

/**
 * @brief Configure Hardware Object correspond with Object type(HTH or HRH)
 */
static void Can_Hw_InitHwObject(const Can_HardwareObjectConfigType *HohCfg)
{
   switch (HohCfg->ObjectType)
   {
   case CAN_HOH_TRANSMIT:
        Can_lHwInitHth(HohCfg);
        break;

   case CAN_HOH_RECEIVE:
        Can_lHwInitHrh(HohCfg);
        break;

   default:
        break;
   }   
}

/**
 * @brief: Depend on MCU to configure.There are MCUs which don't need configure TX  
 */
static void Can_lHwInitHth(const Can_HardwareObjectConfigType *HthCfg)
{
    //nothing
}

/**Flow init Hardware Rx Object
 * Enter Filter Init Mode-> Disable Filter Bank -> Configure Filter Scale -> Configure Filter Mode
 * Configure FIFO Assignment -> Configure Filter ID / Mask -> Enable Filter Bank -> Leave Filter Init Mode
 */
static void Can_lHwInitHrh(const Can_HardwareObjectConfigType *HrhCfg)
{
    /*Get Can Instance have to configure*/
    CAN_Reg_TypeDef_t *Instance = Can_ControllerInstance[HrhCfg->ControllerId];
    /*Enter filter Hardware Rx Object*/
    if(HrhCfg->FilterConfig->FilterEnable)
    {
        Instance->FMR |= CAN_FMR_FINIT;
    }
    else return;

    /*Disable filter bank*/
    Instance->FA1R &= ~(1U << HrhCfg->FilterConfig->FilterBank);
    /*Configure Filter Scale*/
    if(HrhCfg->FilterConfig->FilterScale == CAN_FILTER_SCALE_32BIT)
    {
        Instance->FS1R |= (1U << HrhCfg->FilterConfig->FilterBank);
    }
    else
    {
        Instance->FS1R &= ~(1U << HrhCfg->FilterConfig->FilterBank);
    }
    /*Configure Filter mode*/
    if(HrhCfg->FilterConfig->FilterMode == CAN_FILTER_MODE_MASK)
    {
        Instance->FM1R &= ~(1U << HrhCfg->FilterConfig->FilterBank);
    }
    else
    {
        Instance->FM1R |= (1U << HrhCfg->FilterConfig->FilterBank);
    }
    /*Configure FIFO Assignment*/
    if(HrhCfg->FilterConfig->FifoAssignment == CAN_RX_FIFO0)
    {
        Instance->FFA1R &= ~(1U << HrhCfg->FilterConfig->FilterBank);
    }
    else
    {
        /*Select FIFO1*/
        Instance->FFA1R |= (1U << HrhCfg->FilterConfig->FilterBank);
    }
    /*Mask and ID*/
    Instance->sFilterRegister[HrhCfg->FilterConfig->FilterBank].FR1 = HrhCfg->FilterConfig->FilterId << 21U;
    Instance->sFilterRegister[HrhCfg->FilterConfig->FilterBank].FR2 = HrhCfg->FilterConfig->FilterMask << 21U;
    /*Activate filter bank*/
    Instance->FA1R |= (1U << HrhCfg->FilterConfig->FilterBank);
    /*Leave filter init*/
    Instance->FMR &= ~(CAN_FMR_FINIT);
}

/*========================================End local function===================================*/

/**
 * @brief Initializes the CAN driver.
 * @param Config Pointer to the CAN configuration structure.
 */
void Can_Init(const Can_ConfigType *Config)
{
    if (Config == NULL_PTR)
    {
        return;
    }

    /*Check driver state*/
    if (Can_DriverState != CAN_UNINIT)
    {
        return;
    }

    ConfigPtr = Config;

    Can_lInitController();
    Can_lInitHardwareObject();

    Can_DriverState = CAN_READY;
}

/**
 * @brief Set baudrate for Can_Controller
 * @param Controller BaudRateConfigID
 */
void Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    if (Can_ControllerState[Controller] != CAN_CS_STOPPED)
    {
        return;
    }

    for (uint8 i = 0; i < ConfigPtr->ControllerConfigs->NumBaudrates; i++)
    {
        if (BaudRateConfigID == BaudConfigPtr[i].BaudrateConfigID)
        {
            /*At here i is index of configuration array which contain corresponding BaudrateID*/

            uint8 SJW = BaudConfigPtr[i].SJW - 1U;
            uint8 BS1 = BaudConfigPtr[i].BS1 - 1U;
            uint8 BS2 = BaudConfigPtr[i].BS2 - 1U;
            uint32 Prescaler = BaudConfigPtr[i].Prescaler - 1U;

            Can_ControllerInstance[Controller]->BTR &= ~CAN_BTR_BRP_Msk;
            Can_ControllerInstance[Controller]->BTR |= (Prescaler << CAN_BTR_BRP_Pos);
  
            Can_ControllerInstance[Controller]->BTR &= ~CAN_BTR_SJW_Msk;
            Can_ControllerInstance[Controller]->BTR |= SJW << CAN_BTR_SJW_Pos;

            Can_ControllerInstance[Controller]->BTR &= ~CAN_BTR_TS1_Msk;
            Can_ControllerInstance[Controller]->BTR |= BS1 << CAN_BTR_TS1_Pos;

            Can_ControllerInstance[Controller]->BTR &= ~CAN_BTR_TS2_Msk;
            Can_ControllerInstance[Controller]->BTR |= BS2 << CAN_BTR_TS2_Pos;

            break;
        }
    }
}

/**
 * @brief Sets the operating mode of a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which the operating mode is to be set
 * @param Transition The desired operating mode to transition the specified CAN controller to. 
 * This parameter should be of type Can_ControllerStateType and can take values such as 
 * CAN_CS_STARTED, CAN_CS_STOPPED, or CAN_CS_SLEEP, depending on the desired state of the CAN controller.
 */
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    if (Controller >= CAN_MAX_CONTROLLERS)
    {
        return E_NOT_OK;
    }

    if (Can_DriverState == CAN_UNINIT)
    {   
        return E_NOT_OK;
    }

    CAN_Reg_TypeDef_t* Instance = Can_ControllerInstance[Controller];

    switch(Transition)
    {
        case CAN_CS_UNINIT:
            return E_NOT_OK;
            break;

        case CAN_CS_STARTED:
            if(Can_ControllerState[Controller] == CAN_CS_STOPPED)
            {
                /*STOPPED->STARTED: SLAK = 0 INAK = 0*/
                Instance->MCR &= ~CAN_MCR_INRQ;
                Instance->MCR &= ~CAN_MCR_SLEEP;
                while((Instance->MSR & CAN_MSR_INAK)  || (Instance->MSR & CAN_MSR_SLAK))
                {
                    /*wait to reset INAK and SLAK*/
                }
                /*Update controller status*/
                Can_ControllerState[Controller] = CAN_CS_STARTED;
                
                return E_OK;
            }
            else if(Can_ControllerState[Controller] == CAN_CS_SLEEP)
            {
                /*SLEEP->STARTED : SLAK = 0 INAK = 0 */
                Instance->MCR &= ~CAN_MCR_INRQ;
                Instance->MCR &= ~CAN_MCR_SLEEP;
                while((Instance->MSR & CAN_MSR_INAK)  || (Instance->MSR & CAN_MSR_SLAK))
                {
                    /*wait to reset INAK and SLAK*/
                }
                /*Update controller status*/
                Can_ControllerState[Controller] = CAN_CS_STARTED;

                return E_OK;
            }
            return E_NOT_OK;
            break;

        case CAN_CS_STOPPED:
            if(Can_ControllerState[Controller] == CAN_CS_SLEEP)
            {
                /*SLEEP->STOPPED: SLAK = 0 INAK = 1*/
                Instance->MCR |= CAN_MCR_INRQ;
                Instance->MCR &= ~CAN_MCR_SLEEP;
                while(!(Instance->MSR & CAN_MSR_INAK) || (Instance->MSR & CAN_MSR_SLAK))
                {
                    /*wait for condition*/
                    /*timeout in future*/
                }

                Can_ControllerState[Controller] = CAN_CS_STOPPED;

                return E_OK;
            }
            else if(Can_ControllerState[Controller] == CAN_CS_STARTED)
            {
                /*STARTED -> STOPPED : INAK = 1*/
                Instance->MCR |= CAN_MCR_INRQ;
                while(!(Instance->MSR & CAN_MSR_INAK));

                Can_ControllerState[Controller] = CAN_CS_STOPPED;

                return E_OK;
            }
            return E_NOT_OK;
            break;
        case CAN_CS_SLEEP:
            if(Can_ControllerState[Controller] == CAN_CS_STOPPED)
            {
                /*STOPPED -> SLEEP : INAK = 0 SLAK = 1*/
                Instance->MCR |= CAN_MCR_SLEEP;
                Instance->MCR &= ~CAN_MCR_INRQ;
                while ((Instance->MSR & CAN_MSR_INAK) || !(Instance->MSR & CAN_MSR_SLAK))
                {
                    /* code */
                }
                
                Can_ControllerState[Controller] = CAN_CS_SLEEP;
                return E_OK;
            }
            else if(Can_ControllerState[Controller] == CAN_CS_STARTED)
            {
                /*STARTED -> SLEEP: SLAK = 1*/
                Instance->MCR |= CAN_MCR_SLEEP;
                while (!(Instance->MSR & CAN_MSR_SLAK))
                {
                    /* code */
                }

                Can_ControllerState[Controller] = CAN_CS_SLEEP;
                return E_OK;
            }
            return E_NOT_OK;
            break;

        default:
            return E_NOT_OK;
            break;
    }
}
/**
 * @brief: Get controller's current status
 * @param Controller Controller ID
 * @param ControllerModePtr : pointer which saves returned state
 */
Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType* ControllerModePtr)
{
    if(ControllerModePtr == NULL_PTR || Controller >= CAN_MAX_CONTROLLERS || Can_DriverState == CAN_UNINIT)
    {
        return E_NOT_OK;
    }

    *ControllerModePtr = Can_ControllerState[Controller];
    return E_OK;
}

/**
 * @brief: 
 */
#define CAN_HOH_INVALID (uint8)0xFF

static uint8 Can_lFindControllerID_FromHwHandle(Can_HwHandleType Hth)
{
    for(uint8 i = 0 ; i < Can_HohLookupTableSize; i++)
    {
        if(Hth == Can_HohLookupTabble[i].HohId)
        {
            return Can_HohLookupTabble[i].ControllerId;
        }
    }
    return CAN_HOH_INVALID;
}

/**
 * @brief:
 */
static uint8 Can_lGetMailboxFree(CAN_Reg_TypeDef_t *Instance)
{
    if(Instance->TSR & CAN_TSR_TME0)
    {
        return CAN_TX_MAILBOX0_IS_FREE;
    }

    if(Instance->TSR & CAN_TSR_TME1)
    {
        return CAN_TX_MAILBOX1_IS_FREE;
    }

    if(Instance->TSR & CAN_TSR_TME2)
    {
        return CAN_TX_MAILBOX2_IS_FREE;
    }

    return CAN_TX_MAILBOX_IS_BUSY;
}

/**
 * @brief:
 */

static inline void Can_lConfigureMailboxIdentifier(Can_IdType Id, CAN_TxMailBox_TypeDef_t* pTx_Mailbox)
{
    /*Default set Data frame*/
    pTx_Mailbox->TIR &= ~CAN_TIR_RTR;
    /*Determine IDE and STD or FD Can. Bit 31 -> IDE, bit 30->STD/FD*/
    if(Id & 0x80000000U)
    {
        /*At here: bit31 is set->extended ID*/
        pTx_Mailbox->TIR |= CAN_TIR_IDE;
        pTx_Mailbox->TIR &= ~(CAN_TIR_EXID | CAN_TIR_STID);
        pTx_Mailbox->TIR |= ((Id & 0x1FFFFFFFU) << CAN_TIR_EXID_Pos);
        if(Id & 0x40000000U)
        {
            /*At here: bit30 is set-> using can-fd*/
            //stm32 not support Can-fd
        }
        else
        {
            /*At here: bit 30 is reset-> using standard Can*/
            /*stm32 default is standard Can*/
        }
    }
    else
    {
        /*At here: bit31 is reset->standard ID*/
        pTx_Mailbox->TIR &= ~CAN_TIR_IDE;
        pTx_Mailbox->TIR &= ~ (CAN_TIR_STID | CAN_TIR_EXID);
        pTx_Mailbox->TIR |= ((Id & 0x7FFU) << CAN_TIR_STID_Pos);
        if(Id & 0x40000000U)
        {
            /*At here: bit30 is set-> using can-fd*/
            //stm32 not support Can-fd
        }
        else
        {
            /*At here: bit 30 is reset-> using standard Can*/
            /*stm32 default is standard Can*/
        }
    }
}

static inline void Can_lPushDataToTransmitMailbox(CAN_TxMailBox_TypeDef_t* pTx_Mailbox,
                                                            uint8* pData, uint8 length)
{
    /*Clear previous data*/
    pTx_Mailbox->TDLR = 0U;
    pTx_Mailbox->TDHR = 0U;

    for(uint8 i = 0; i < length ; i++)
    {
        if(i < 4U)
        {
            pTx_Mailbox->TDLR |= pData[i] << 8U*i;
        }
        else
        {
            pTx_Mailbox->TDHR |= pData[i] << 8U*(i - 4U);
        }
    }
}

/**
 * @brief:
 */
static Std_ReturnType Can_lTransmitMailbox(CAN_Reg_TypeDef_t* Instance,
                            uint8 MailboxId,const Can_PduType* PduInfo)
{
    if(PduInfo->sdu == NULL_PTR || PduInfo->length == 0U)
    {
        return E_NOT_OK;
    }

    CAN_TxMailBox_TypeDef_t *pTx_Mailbox = &Instance->sTxMailBox[MailboxId];
    /*Encode ID from PduInfo to get information : STD/EXT and CAN_STD/CAN_FD*/
    /*Note: current project don't support remote frame. In additon, STM32F407 no Can-FD*/
    Can_lConfigureMailboxIdentifier(PduInfo->id,pTx_Mailbox);

    /*Push data franme into register to prepare transmission*/
    Can_lPushDataToTransmitMailbox(pTx_Mailbox,PduInfo->sdu, PduInfo->length);
    /*Data Length Code*/
    pTx_Mailbox->TDTR &= ~CAN_TDTR_DLC;
    pTx_Mailbox->TDTR |= PduInfo->length << CAN_TDTR_DLC_Pos;
    return E_OK;
}

/**
 * @brief Transmits a CAN message using a specific CAN controller.
 * @param Hth The hardware transmit handle associated with the CAN controller to be used for transmission.
 * @param PduInfo Pointer to a structure containing the information of the CAN message to be transmitted,
 *  including the CAN identifier, data length, and data bytes.
 */
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo)
{
    if(Can_DriverState != CAN_READY)
    {
        return E_NOT_OK;
    }
    
    /*find Controller ID corresponding with the Hardware Object Hth*/
    uint8 ControllerID = Can_lFindControllerID_FromHwHandle(Hth);
    /*Validate ControllerID*/
    if(ControllerID == CAN_HOH_INVALID)
    {
        return E_NOT_OK;
    }

    if(Can_ControllerState[ControllerID] != CAN_CS_STARTED)
    {
        return E_NOT_OK;
    }

    /*Specific Can Controller be used*/
    CAN_Reg_TypeDef_t* Instance = Can_ControllerInstance[ControllerID];

    uint8 MailboxTransmit = Can_lGetMailboxFree(Instance);//return mailbox is free or all mail is busy
    if(MailboxTransmit == CAN_TX_MAILBOX_IS_BUSY)
    {
        return E_NOT_OK;
    }

    /*Save Context to inform specific PduHandle is process*/
    if(Can_TxMailboxContext[ControllerID][MailboxTransmit].Busy == FALSE)
    {
        Can_TxMailboxContext[ControllerID][MailboxTransmit].Busy = TRUE;
        Can_TxMailboxContext[ControllerID][MailboxTransmit].SwPduHandle = PduInfo->swPduHandle;
    }
    else
    {
        /*Previous PDU is not Informed to CanIf*/
        return E_NOT_OK;
    }
    
    /*At here mailbox is available to write to register in Mailbox : ID, DLC, DATA*/
    Can_lTransmitMailbox(Instance,MailboxTransmit,PduInfo);
    /*Transmit mailbox request*/
    Instance->sTxMailBox[MailboxTransmit].TIR |= CAN_TIR_TXRQ;

    return E_OK;
}


static Can_InterruptMaskType Can_lBuildInterruptMask(uint8 Controller);
static void Can_lEnableInterruptMask(uint8 Controller, Can_InterruptMaskType Mask);
static void Can_lDisableInterruptMask(uint8 Controller, Can_InterruptMaskType Mask);
/*===========================================ENABLE/DISABLE INTERRUPT=================================*/
/**
 * @brief Disables interrupts for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to disable interrupts.
 */
void Can_DisableControllerInterrupts(uint8 Controller)
{
    Can_InterruptMaskType Mask;

    if((Controller >= CAN_MAX_CONTROLLERS) ||
       (Can_DriverState == CAN_UNINIT))
    {
        return;
    }

    Mask = Can_lBuildInterruptMask(Controller);
    Can_lDisableInterruptMask(Controller,Mask);

}

/**
 * @brief Enables interrupts for a specific CAN controller.
 * @param Controller The identifier of the CAN controller for which to enable interrupts.
 */
void Can_EnableControllerInterrupts(uint8 Controller)
{
    Can_InterruptMaskType Mask;

    Mask = Can_lBuildInterruptMask(Controller);

    Can_lEnableInterruptMask( Controller,Mask);
}

/**
 * 
 */
static Can_InterruptMaskType Can_lBuildInterruptMask(uint8 Controller)
{
    Can_InterruptMaskType Mask = CAN_INT_NONE;

    const Can_ControllerConfigInterruptType* Config = &Can_ConfigureInterruptTable[Controller];

    if(Config->TxProcessing == CAN_PROCESSING_INTERRUPT)
    {
        Mask |= CAN_INT_TX;
    }

    if(Config->Rx0Processing == CAN_PROCESSING_INTERRUPT)
    {
        Mask |= CAN_INT_RX0_PENDING;
    }

    if(Config->Rx1Processing == CAN_PROCESSING_INTERRUPT)
    {
        Mask |= CAN_INT_RX1_PENDING;
    }

    if(Config->StatusChangeErrorInterrupt == CAN_PROCESSING_INTERRUPT)
    {
        Mask |= CAN_INT_BUSOFF;
        Mask |= CAN_INT_ERROR_WARNING;
        Mask |= CAN_INT_ERROR_PASSIVE;
        Mask |= CAN_INT_LAST_ERROR;
        Mask |= CAN_INT_WAKEUP;
        Mask |= CAN_INT_SLEEP;
    }

    return Mask;
}

/**
 * 
 */

static void Can_lEnableInterruptMask(uint8 Controller, Can_InterruptMaskType Mask)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    /*---------------- TX ----------------*/
    if(Mask & CAN_INT_TX)
    {
        Instance->IER |= CAN_IER_TMEIE;
    }

    /*------------- RX FIFO0 ------------*/
    if(Mask & CAN_INT_RX0_PENDING)
    {
        Instance->IER |= CAN_IER_FMPIE0;
    }

    if(Mask & CAN_INT_RX0_FULL)
    {
        Instance->IER |= CAN_IER_FFIE0;
    }

    if(Mask & CAN_INT_RX0_OVERRUN)
    {
        Instance->IER |= CAN_IER_FOVIE0;
    }

    /*------------- RX FIFO1 ------------*/
    if(Mask & CAN_INT_RX1_PENDING)
    {
        Instance->IER |= CAN_IER_FMPIE1;
    }

    if(Mask & CAN_INT_RX1_FULL)
    {
        Instance->IER |= CAN_IER_FFIE1;
    }

    if(Mask & CAN_INT_RX1_OVERRUN)
    {
        Instance->IER |= CAN_IER_FOVIE1;
    }
    
    /*--------------- ERROR -------------*/
    if(Mask & CAN_INT_ERROR_WARNING)
    {
        Instance->IER |= CAN_IER_EWGIE;
    }

    if(Mask & CAN_INT_ERROR_PASSIVE)
    {
        Instance->IER |= CAN_IER_EPVIE;
    }

    if(Mask & CAN_INT_BUSOFF)
    {
        Instance->IER |= CAN_IER_BOFIE;
    }

    if(Mask & CAN_INT_LAST_ERROR)
    {
        Instance->IER |= CAN_IER_LECIE;
    }

    /*--------------- STATUS ------------*/
    if(Mask & CAN_INT_WAKEUP)
    {
        Instance->IER |= CAN_IER_WKUIE;
    }

    if(Mask & CAN_INT_SLEEP)
    {
        Instance->IER |= CAN_IER_SLKIE;
    }
}

/**
 * 
 */
static void Can_lDisableInterruptMask(uint8 Controller, Can_InterruptMaskType Mask)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    /*---------------- TX ----------------*/
    if(Mask & CAN_INT_TX)
    {
        Instance->IER &= ~CAN_IER_TMEIE;
    }

    /*------------- RX FIFO0 ------------*/
    if(Mask & CAN_INT_RX0_PENDING)
    {
        Instance->IER &= ~CAN_IER_FMPIE0;
    }

    if(Mask & CAN_INT_RX0_FULL)
    {
        Instance->IER &= ~CAN_IER_FFIE0;
    }

    if(Mask & CAN_INT_RX0_OVERRUN)
    {
        Instance->IER &= ~CAN_IER_FOVIE0;
    }

    /*------------- RX FIFO1 ------------*/
    if(Mask & CAN_INT_RX1_PENDING)
    {
        Instance->IER &= ~CAN_IER_FMPIE1;
    }

    if(Mask & CAN_INT_RX1_FULL)
    {
        Instance->IER &= ~CAN_IER_FFIE1;
    }

    if(Mask & CAN_INT_RX1_OVERRUN)
    {
        Instance->IER &= ~CAN_IER_FOVIE1;
    }

    /*--------------- ERROR -------------*/
    if(Mask & CAN_INT_ERROR_WARNING)
    {
        Instance->IER &= ~CAN_IER_EWGIE;
    }

    if(Mask & CAN_INT_ERROR_PASSIVE)
    {
        Instance->IER &= ~CAN_IER_EPVIE;
    }

    if(Mask & CAN_INT_BUSOFF)
    {
        Instance->IER &= ~CAN_IER_BOFIE;
    }

    if(Mask & CAN_INT_LAST_ERROR)
    {
        Instance->IER &= ~CAN_IER_LECIE;
    }

    /*--------------- STATUS ------------*/
    if(Mask & CAN_INT_WAKEUP)
    {
        Instance->IER &= ~CAN_IER_WKUIE;
    }

    if(Mask & CAN_INT_SLEEP)
    {
        Instance->IER &= ~CAN_IER_SLKIE;
    }
}

/*=====================================================================================
 * TX INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable TX mailbox empty interrupt.
 *
 * This interrupt is used when TxProcessing = INTERRUPT.
 * Normally enabled when at least one frame is queued for transmission.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableTxInterrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER |= CAN_IER_TMEIE;
}

/**
 * @brief Disable TX mailbox empty interrupt.
 *
 * This interrupt should be disabled when there is no pending
 * software transmission request to avoid unnecessary ISR execution.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableTxInterrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER &= ~CAN_IER_TMEIE;
}

/*=====================================================================================
 * RX FIFO0 INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable RX FIFO0 message pending interrupt.
 *
 * Interrupt generated whenever a new frame arrives in FIFO0.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableRx0Interrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER |= CAN_IER_FMPIE0;
}

/**
 * @brief Disable RX FIFO0 message pending interrupt.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableRx0Interrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER &= ~CAN_IER_FMPIE0;
}

/*=====================================================================================
 * RX FIFO1 INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable RX FIFO1 message pending interrupt.
 *
 * Interrupt generated whenever a new frame arrives in FIFO1.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableRx1Interrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER |= CAN_IER_FMPIE1;
}

/**
 * @brief Disable RX FIFO1 message pending interrupt.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableRx1Interrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER &= ~CAN_IER_FMPIE1;
}

/*=====================================================================================
 * BUSOFF INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable BusOff interrupt.
 *
 * Interrupt generated when controller enters BusOff state.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableBusOffInterrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER |= CAN_IER_BOFIE;
}

/**
 * @brief Disable BusOff interrupt.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableBusOffInterrupt(uint8 Controller)
{
    Can_ControllerInstance[Controller]->IER &= ~CAN_IER_BOFIE;
}

/*=====================================================================================
 * ERROR INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable CAN error related interrupts.
 *
 * Includes:
 *  - Error Warning
 *  - Error Passive
 *  - Last Error Code
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableErrorInterrupt(uint8 Controller)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    Instance->IER |= CAN_IER_EWGIE;
    Instance->IER |= CAN_IER_EPVIE;
    Instance->IER |= CAN_IER_LECIE;
}

/**
 * @brief Disable CAN error related interrupts.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableErrorInterrupt(uint8 Controller)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    Instance->IER &= ~CAN_IER_EWGIE;
    Instance->IER &= ~CAN_IER_EPVIE;
    Instance->IER &= ~CAN_IER_LECIE;
}

/*=====================================================================================
 * WAKEUP / SLEEP INTERRUPT CONTROL
 *====================================================================================*/

/**
 * @brief Enable wakeup and sleep acknowledge interrupts.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lEnableWakeupSleepInterrupt(uint8 Controller)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    Instance->IER |= CAN_IER_WKUIE;
    Instance->IER |= CAN_IER_SLKIE;
}

/**
 * @brief Disable wakeup and sleep acknowledge interrupts.
 *
 * @param Controller CAN controller ID
 */
static inline void Can_lDisableWakeupSleepInterrupt(uint8 Controller)
{
    CAN_Reg_TypeDef_t* Instance;

    Instance = Can_ControllerInstance[Controller];

    Instance->IER &= ~CAN_IER_WKUIE;
    Instance->IER &= ~CAN_IER_SLKIE;
}

/*===========================================ENABLE/DISABLE INTERRUPT=================================*/
