#ifndef __SCHEM_CAN_H
#define __SCHEM_CAN_H   

#include "Can_PBcfg.h"
#include "CanIf.h"

/**
 * @brief: This function performs the polling of TX confirmation when CAN_TX_PROCESSING is set
 * to POLLING
 */
void Can_MainFunction_Write(void);

/**
 * @brief: This function performs the polling of RX indication when CAN_RX_PROCESSING is set
 * to POLLING
 */
void Can_MainFunction_Read(void);

/**
 * @brief: This function handles the bus off event for the CAN driver.
 */
void Can_MainFunction_BusOff(void);

/**
 * @brief: This function handles the wakeup event for the CAN driver.
 */
void Can_MainFunction_Wakeup(void);

/**
 * @brief: This function handles the mode transition for the CAN driver.
 */
void Can_MainFunction_Mode(void);


#endif /**/