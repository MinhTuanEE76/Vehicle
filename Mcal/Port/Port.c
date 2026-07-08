#include "Port.h"
#include "stm32f407xxx_rcc.h"

static const Port_ConfigType* Port_ConfigPtr = NULL_PTR;

static GPIO_Reg_TypeDef_t* const Port_GpioTable[] =
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH
};

/*================================================Local Function==============================================*/

/**
 * @brief: Configure pin direction according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 */
static inline void Port_lConfigureMode(const Port_PinConfigsType* PinConfigs)
{
    uint8 Position = PinConfigs->PinId & 0xFU; /* Get the pin position within the port (0-15) */
    /* Clear the 2 bits for the pin and set the new mode */
    Port_GpioTable[PinConfigs->PinId >> 4U]->MODER &= ~(PIN_MASK_2BIT << (Position*2U));
    Port_GpioTable[PinConfigs->PinId >> 4U]->MODER |= (PinConfigs->PinMode << (2U*Position));
}

/**
 * @brief: Configure pin output type according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 */
static inline void Port_lConfigureOutputType(const Port_PinConfigsType* PinConfigs)
{
    uint8 Position = PinConfigs->PinId & 0xFU; /* Get the pin position within the port (0-15) */
    Port_GpioTable[PinConfigs->PinId >> 4U]->OTYPER &= ~(PIN_MASK_1BIT << Position);
    Port_GpioTable[PinConfigs->PinId >> 4U]->OTYPER |= (PinConfigs->OutputType << Position);
}

/**
 * @brief: Configure pin output speed according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 */
static inline void Port_lConfigureOutputSpeed(const Port_PinConfigsType* PinConfigs)
{
    uint8 Position = PinConfigs->PinId & 0xFU; /* Get the pin position within the port (0-15) */
    Port_GpioTable[PinConfigs->PinId >> 4U]->OSPEEDR &= ~(PIN_MASK_2BIT << (Position*2U));
    Port_GpioTable[PinConfigs->PinId >> 4U]->OSPEEDR |= (PinConfigs->OutputSpeed << (2U*Position));
}

/**
 * @brief: Configure pin pull-up/pull-down according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 */
static inline void Port_lConfigurePullupPullDown(const Port_PinConfigsType* PinConfigs)
{
    uint8 Position = PinConfigs->PinId & 0xFU; /* Get the pin position within the port (0-15) */
    Port_GpioTable[PinConfigs->PinId >> 4U]->PUPDR &= ~(PIN_MASK_2BIT << (Position*2U));
    Port_GpioTable[PinConfigs->PinId >> 4U]->PUPDR |= (PinConfigs->PullUpPullDown << (2U*Position));
}

/**
 * @brief: Configure pin level according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 * @param: Position: position of the pin in the port
 */
static inline void Port_ConfigurePinLevel(const Port_PinConfigsType* PinConfigs, uint8 Position)
{
    if(PinConfigs->InitialValue == STD_LOW)
    {
        Port_GpioTable[PinConfigs->PinId >> 4U]->ODR &= ~(PIN_MASK_1BIT << Position);
    }
    else
    {
        Port_GpioTable[PinConfigs->PinId >> 4U]->ODR |= (PIN_MASK_1BIT << Position);
    }
}

/**
 * @brief: Configure pin alternate function according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 * @param: Position: position of the pin in the port
 */
static inline void Port_lConfigureAlternateFunction(const Port_PinConfigsType* PinConfigs)
{
    uint8 Position = PinConfigs->PinId & 0xFU; /* Get the pin position within the port (0-15) */
    if(Position < 8U)
    {
        Port_GpioTable[PinConfigs->PinId >> 4U]->AFR[0] &= ~(0xFU << (Position*4U)); /* Clear the 4 bits for the pin */
        Port_GpioTable[PinConfigs->PinId >> 4U]->AFR[0] |= (PinConfigs->AlternateFunction << (Position*4U)); /* Set the alternate function */
    }
    else
    {
        Position -= 8U;

        Port_GpioTable[PinConfigs->PinId >> 4U]->AFR[1] &= ~(0xFU << (Position*4U)); /* Clear the 4 bits for the pin */
        Port_GpioTable[PinConfigs->PinId >> 4U]->AFR[1] |= (PinConfigs->AlternateFunction << (Position*4U)); /* Set the alternate function */
    }
}

/**
 * @brief: Enable clock for the corresponding GPIO port according to configuration parameter in pointer Port_ConfigPtr
 * @param: PinConfigs: pointer to Port_ConfigType structure which contains pin configuration parameters
 */
static inline void Port_lEnableClock(const Port_PinConfigsType* PinConfig)
{
    switch(PinConfig->PinId >> 4U)
    {
        case 0U: /* GPIOA */
            RCC_ENABLE_PORTA_CLK();
            break;
        case 1U: /* GPIOB */
            RCC_ENABLE_PORTB_CLK();
            break;
        case 2U: /* GPIOC */
            RCC_ENABLE_PORTC_CLK();
            break;
        case 3U: /* GPIOD */
            RCC_ENABLE_PORTD_CLK();
            break;
        case 4U: /* GPIOE */
            RCC_ENABLE_PORTE_CLK();
            break;
        case 5U: /* GPIOF */
            RCC_ENABLE_PORTF_CLK();
            break;
        case 6U: /* GPIOG */
            RCC_ENABLE_PORTG_CLK();
            break;
        case 7U: /* GPIOH */
            RCC_ENABLE_PORTH_CLK();
            break;
        default:
            /* Invalid port, do nothing or handle error */
            break;
    }
}
/*============================================End ofLocal Function============================================*/


/**
 * @brief Sets the direction of a specific pin.
 * @param Pin The ID of the pin to configure.
 * @param Direction The direction to set.
 */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    if(Port_ConfigPtr == NULL_PTR)
    {
        return;
    }
    /*Find the pin in the configuration array*/
    for (uint8 i = 0; i < Port_ConfigPtr->PinCount; i++)
    {
        if(Port_ConfigPtr->PinConfigs[i].PinId == Pin)
        {
            /*Configure the pin direction*/
            Port_lConfigureMode(&Port_ConfigPtr->PinConfigs[i]);
            break;
        }
    }   
}

/**
 * @brief Refreshes the direction of all configured pins to their initial state.
 */
void Port_RefreshPortDirection(void)
{
    if(Port_ConfigPtr == NULL_PTR)
    {
        return;
    }
    /*Refresh the direction of each pin in the configuration array*/
    for (uint8 i = 0; i < Port_ConfigPtr->PinCount; i++)
    {
        /*Configure the pin direction*/
        Port_lConfigureMode(&Port_ConfigPtr->PinConfigs[i]);
    }
}


/**
 * @brief initializes the Port driver.
 * @param ConfigPtr Pointer to the configuration structure.
 */
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    if(ConfigPtr == NULL_PTR)
    {
        return;
    }

    //assign pointer which pointing port pin configuration structure
    Port_ConfigPtr = ConfigPtr;

    /*configure each pin*/
    for (uint8 i = 0; i < Port_ConfigPtr->PinCount; i++)
    {
        /*Enable clock for the corresponding GPIO port*/
        Port_lEnableClock(&Port_ConfigPtr->PinConfigs[i]);

        /*Direction: Input or output*/
        Port_lConfigureMode(&Port_ConfigPtr->PinConfigs[i]);
        /*Pushpull or open drain*/
        Port_lConfigureOutputType(&Port_ConfigPtr->PinConfigs[i]);
        /*Pullup or Pulldowmn register*/
        Port_lConfigurePullupPullDown(&Port_ConfigPtr->PinConfigs[i]);
        /*Output Speed*/
        Port_lConfigureOutputSpeed(&Port_ConfigPtr->PinConfigs[i]);
        /*Initial Value*/
        Port_ConfigurePinLevel(&Port_ConfigPtr->PinConfigs[i], Port_ConfigPtr->PinConfigs[i].PinId);
        /*Alternate Function*/
        if (Port_ConfigPtr->PinConfigs[i].PinMode == PORT_PIN_MODE_AF)
        {
            Port_lConfigureAlternateFunction(&Port_ConfigPtr->PinConfigs[i]);
        }
    }
}