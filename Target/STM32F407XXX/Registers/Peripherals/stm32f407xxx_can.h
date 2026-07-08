#ifndef __STM32F407XXX_CAN_H
#define __STM32F407XXX_CAN_H

#include "stm32f407xxx.h"

/* =========================================================
 * CAN_MCR
 * ========================================================= */
#define CAN_MCR_INRQ                    (1U << 0)
#define CAN_MCR_SLEEP                   (1U << 1)
#define CAN_MCR_TXFP                    (1U << 2)
#define CAN_MCR_RFLM                    (1U << 3)
#define CAN_MCR_NART                    (1U << 4)
#define CAN_MCR_AWUM                    (1U << 5)
#define CAN_MCR_ABOM                    (1U << 6)
#define CAN_MCR_TTCM                    (1U << 7)
#define CAN_MCR_RESET                   (1U << 15)
#define CAN_MCR_DBF                     (1U << 16)

/* =========================================================
 * CAN_MSR
 * ========================================================= */
#define CAN_MSR_INAK                    (1U << 0)
#define CAN_MSR_SLAK                    (1U << 1)
#define CAN_MSR_ERRI                    (1U << 2)
#define CAN_MSR_WKUI                    (1U << 3)
#define CAN_MSR_SLAKI                   (1U << 4)
#define CAN_MSR_TXM                     (1U << 8)
#define CAN_MSR_RXM                     (1U << 9)
#define CAN_MSR_SAMP                    (1U << 10)
#define CAN_MSR_RX                      (1U << 11)

/* =========================================================
 * CAN_TSR
 * ========================================================= */
#define CAN_TSR_RQCP0                   (1U << 0)
#define CAN_TSR_TXOK0                   (1U << 1)
#define CAN_TSR_ALST0                   (1U << 2)
#define CAN_TSR_TERR0                   (1U << 3)
#define CAN_TSR_ABRQ0                   (1U << 7)

#define CAN_TSR_RQCP1                   (1U << 8)
#define CAN_TSR_TXOK1                   (1U << 9)
#define CAN_TSR_ALST1                   (1U << 10)
#define CAN_TSR_TERR1                   (1U << 11)
#define CAN_TSR_ABRQ1                   (1U << 15)

#define CAN_TSR_RQCP2                   (1U << 16)
#define CAN_TSR_TXOK2                   (1U << 17)
#define CAN_TSR_ALST2                   (1U << 18)
#define CAN_TSR_TERR2                   (1U << 19)
#define CAN_TSR_ABRQ2                   (1U << 23)

#define CAN_TSR_CODE_Pos                24U
#define CAN_TSR_CODE_Msk                (3U << CAN_TSR_CODE_Pos)

#define CAN_TSR_TME0                    (1U << 26)
#define CAN_TSR_TME1                    (1U << 27)
#define CAN_TSR_TME2                    (1U << 28)

#define CAN_TSR_LOW0                    (1U << 29)
#define CAN_TSR_LOW1                    (1U << 30)
#define CAN_TSR_LOW2                    (1U << 31)

/* =========================================================
 * CAN_RF0R
 * ========================================================= */
#define CAN_RF0R_FMP0_Pos               0U
#define CAN_RF0R_FMP0               (3U << CAN_RF0R_FMP0_Pos)

#define CAN_RF0R_FULL0                  (1U << 3)
#define CAN_RF0R_FOVR0                  (1U << 4)
#define CAN_RF0R_RFOM0                  (1U << 5)

/* =========================================================
 * CAN_RF1R
 * ========================================================= */
#define CAN_RF1R_FMP1_Pos               0U
#define CAN_RF1R_FMP1               (3U << CAN_RF1R_FMP1_Pos)

#define CAN_RF1R_FULL1                  (1U << 3)
#define CAN_RF1R_FOVR1                  (1U << 4)
#define CAN_RF1R_RFOM1                  (1U << 5)

/* =========================================================
 * CAN_IER
 * ========================================================= */
#define CAN_IER_TMEIE                   (1U << 0)
#define CAN_IER_FMPIE0                  (1U << 1)
#define CAN_IER_FFIE0                   (1U << 2)
#define CAN_IER_FOVIE0                  (1U << 3)
#define CAN_IER_FMPIE1                  (1U << 4)
#define CAN_IER_FFIE1                   (1U << 5)
#define CAN_IER_FOVIE1                  (1U << 6)
#define CAN_IER_EWGIE                   (1U << 8)
#define CAN_IER_EPVIE                   (1U << 9)
#define CAN_IER_BOFIE                   (1U << 10)
#define CAN_IER_LECIE                   (1U << 11)
#define CAN_IER_ERRIE                   (1U << 15)
#define CAN_IER_WKUIE                   (1U << 16)
#define CAN_IER_SLKIE                   (1U << 17)

/* =========================================================
 * CAN_ESR
 * ========================================================= */
#define CAN_ESR_EWGF                    (1U << 0)
#define CAN_ESR_EPVF                    (1U << 1)
#define CAN_ESR_BOFF                    (1U << 2)

#define CAN_ESR_LEC_Pos                 4U
#define CAN_ESR_LEC_Msk                 (7U << CAN_ESR_LEC_Pos)

#define CAN_ESR_TEC_Pos                 16U
#define CAN_ESR_TEC_Msk                 (0xFFU << CAN_ESR_TEC_Pos)

#define CAN_ESR_REC_Pos                 24U
#define CAN_ESR_REC_Msk                 (0xFFU << CAN_ESR_REC_Pos)

/* =========================================================
 * CAN_BTR
 * ========================================================= */
#define CAN_BTR_BRP_Pos                 0U
#define CAN_BTR_BRP_Msk                 (0x3FFU << CAN_BTR_BRP_Pos)

#define CAN_BTR_TS1_Pos                 16U
#define CAN_BTR_TS1_Msk                 (0x0FU << CAN_BTR_TS1_Pos)

#define CAN_BTR_TS2_Pos                 20U
#define CAN_BTR_TS2_Msk                 (0x07U << CAN_BTR_TS2_Pos)

#define CAN_BTR_SJW_Pos                 24U
#define CAN_BTR_SJW_Msk                 (0x03U << CAN_BTR_SJW_Pos)

#define CAN_BTR_LBKM                    (1U << 30)
#define CAN_BTR_SILM                    (1U << 31)

/* =========================================================
 * CAN Tx Mailbox Identifier Register (TIR)
 * Shared by:
 * - TI0R
 * - TI1R
 * - TI2R
 * ========================================================= */
#define CAN_TIR_TXRQ                    (1U << 0)

#define CAN_TIR_RTR_Pos                 1U
#define CAN_TIR_RTR                     (1U << CAN_TIR_RTR_Pos)

#define CAN_TIR_IDE                     (1U << 2)

#define CAN_TIR_EXID_Pos                3U
#define CAN_TIR_EXID                    (0xFFFFFFF8 << CAN_TIR_EXID_Pos)

#define CAN_TIR_STID_Pos                21U
#define CAN_TIR_STID                    (0x7FFU << CAN_TIR_STID_Pos)

/* =========================================================
 * CAN Tx Mailbox Data Length Control Register (TDTR)
 * Shared by:
 * - TDT0R
 * - TDT1R
 * - TDT2R
 * ========================================================= */
#define CAN_TDTR_DLC_Pos                0U
#define CAN_TDTR_DLC                    (0x0FU << CAN_TDTR_DLC_Pos)

#define CAN_TDTR_TGT                    (1U << 8)

#define CAN_TDTR_TIME_Pos               16U
#define CAN_TDTR_TIME                    (0xFFFFU << CAN_TDTR_TIME_Pos)

/* =========================================================
 * CAN Rx Mailbox Identifier Register (RIR)
 * Shared by:
 * - RI0R
 * - RI1R
 * ========================================================= */
#define CAN_RIR_RTR                     (1U << 1)
#define CAN_RIR_IDE                     (1U << 2)

#define CAN_RIR_EXID_Pos                3U
#define CAN_RIR_EXID                    (0x3FFFFU << CAN_RIR_EXID_Pos)

#define CAN_RIR_STID_Pos                21U
#define CAN_RIR_STID                    (0x7FFU << CAN_RIR_STID_Pos)

/* =========================================================
 * CAN Rx Mailbox Data Length Control Register (RDTR)
 * Shared by:
 * - RDT0R
 * - RDT1R
 * ========================================================= */
#define CAN_RDTR_DLC_Pos                0U
#define CAN_RDTR_DLC                    (0x0FU << CAN_RDTR_DLC_Pos)

#define CAN_RDTR_FMI_Pos                8U
#define CAN_RDTR_FMI                    (0xFFU << CAN_RDTR_FMI_Pos)

#define CAN_RDTR_TIME_Pos               16U
#define CAN_RDTR_TIME                   (0xFFFFU << CAN_RDTR_TIME_Pos)

/* =========================================================
 * FILTER MASTER REGISTER
 * ========================================================= */
#define CAN_FMR_FINIT                   (1U << 0)

#define CAN_FMR_CAN2SB_Pos              8U
#define CAN_FMR_CAN2SB                    (0x3FU << CAN_FMR_CAN2SB_Pos)

/* =========================================================
 * FILTER MODE REGISTER
 * ========================================================= */
#define CAN_FM1R_FBM0                   (1U << 0)
#define CAN_FM1R_FBM1                   (1U << 1)
#define CAN_FM1R_FBM2                   (1U << 2)
#define CAN_FM1R_FBM3                   (1U << 3)
#define CAN_FM1R_FBM4                   (1U << 4)
#define CAN_FM1R_FBM5                   (1U << 5)
#define CAN_FM1R_FBM6                   (1U << 6)
#define CAN_FM1R_FBM7                   (1U << 7)
#define CAN_FM1R_FBM8                   (1U << 8)
#define CAN_FM1R_FBM9                   (1U << 9)
#define CAN_FM1R_FBM10                  (1U << 10)
#define CAN_FM1R_FBM11                  (1U << 11)
#define CAN_FM1R_FBM12                  (1U << 12)
#define CAN_FM1R_FBM13                  (1U << 13)
#define CAN_FM1R_FBM14                  (1U << 14)
#define CAN_FM1R_FBM15                  (1U << 15)
#define CAN_FM1R_FBM16                  (1U << 16)
#define CAN_FM1R_FBM17                  (1U << 17)
#define CAN_FM1R_FBM18                  (1U << 18)
#define CAN_FM1R_FBM19                  (1U << 19)
#define CAN_FM1R_FBM20                  (1U << 20)
#define CAN_FM1R_FBM21                  (1U << 21)
#define CAN_FM1R_FBM22                  (1U << 22)
#define CAN_FM1R_FBM23                  (1U << 23)
#define CAN_FM1R_FBM24                  (1U << 24)
#define CAN_FM1R_FBM25                  (1U << 25)
#define CAN_FM1R_FBM26                  (1U << 26)
#define CAN_FM1R_FBM27                  (1U << 27)

/* =========================================================
 * FILTER SCALE REGISTER
 * ========================================================= */
#define CAN_FS1R_FSC0                   (1U << 0)
#define CAN_FS1R_FSC1                   (1U << 1)
#define CAN_FS1R_FSC2                   (1U << 2)
#define CAN_FS1R_FSC3                   (1U << 3)
#define CAN_FS1R_FSC4                   (1U << 4)
#define CAN_FS1R_FSC5                   (1U << 5)
#define CAN_FS1R_FSC6                   (1U << 6)
#define CAN_FS1R_FSC7                   (1U << 7)
#define CAN_FS1R_FSC8                   (1U << 8)
#define CAN_FS1R_FSC9                   (1U << 9)
#define CAN_FS1R_FSC10                  (1U << 10)
#define CAN_FS1R_FSC11                  (1U << 11)
#define CAN_FS1R_FSC12                  (1U << 12)
#define CAN_FS1R_FSC13                  (1U << 13)
#define CAN_FS1R_FSC14                  (1U << 14)
#define CAN_FS1R_FSC15                  (1U << 15)
#define CAN_FS1R_FSC16                  (1U << 16)
#define CAN_FS1R_FSC17                  (1U << 17)
#define CAN_FS1R_FSC18                  (1U << 18)
#define CAN_FS1R_FSC19                  (1U << 19)
#define CAN_FS1R_FSC20                  (1U << 20)
#define CAN_FS1R_FSC21                  (1U << 21)
#define CAN_FS1R_FSC22                  (1U << 22)
#define CAN_FS1R_FSC23                  (1U << 23)
#define CAN_FS1R_FSC24                  (1U << 24)
#define CAN_FS1R_FSC25                  (1U << 25)
#define CAN_FS1R_FSC26                  (1U << 26)
#define CAN_FS1R_FSC27                  (1U << 27)

/* =========================================================
 * FILTER FIFO ASSIGNMENT REGISTER
 * ========================================================= */
#define CAN_FFA1R_FFA0                  (1U << 0)
#define CAN_FFA1R_FFA1                  (1U << 1)
#define CAN_FFA1R_FFA2                  (1U << 2)
#define CAN_FFA1R_FFA3                  (1U << 3)
#define CAN_FFA1R_FFA4                  (1U << 4)
#define CAN_FFA1R_FFA5                  (1U << 5)
#define CAN_FFA1R_FFA6                  (1U << 6)
#define CAN_FFA1R_FFA7                  (1U << 7)
#define CAN_FFA1R_FFA8                  (1U << 8)
#define CAN_FFA1R_FFA9                  (1U << 9)
#define CAN_FFA1R_FFA10                 (1U << 10)
#define CAN_FFA1R_FFA11                 (1U << 11)
#define CAN_FFA1R_FFA12                 (1U << 12)
#define CAN_FFA1R_FFA13                 (1U << 13)
#define CAN_FFA1R_FFA14                 (1U << 14)
#define CAN_FFA1R_FFA15                 (1U << 15)
#define CAN_FFA1R_FFA16                 (1U << 16)
#define CAN_FFA1R_FFA17                 (1U << 17)
#define CAN_FFA1R_FFA18                 (1U << 18)
#define CAN_FFA1R_FFA19                 (1U << 19)
#define CAN_FFA1R_FFA20                 (1U << 20)
#define CAN_FFA1R_FFA21                 (1U << 21)
#define CAN_FFA1R_FFA22                 (1U << 22)
#define CAN_FFA1R_FFA23                 (1U << 23)
#define CAN_FFA1R_FFA24                 (1U << 24)
#define CAN_FFA1R_FFA25                 (1U << 25)
#define CAN_FFA1R_FFA26                 (1U << 26)
#define CAN_FFA1R_FFA27                 (1U << 27)

/* =========================================================
 * FILTER ACTIVATION REGISTER
 * ========================================================= */
#define CAN_FA1R_FACT0                  (1U << 0)
#define CAN_FA1R_FACT1                  (1U << 1)
#define CAN_FA1R_FACT2                  (1U << 2)
#define CAN_FA1R_FACT3                  (1U << 3)
#define CAN_FA1R_FACT4                  (1U << 4)
#define CAN_FA1R_FACT5                  (1U << 5)
#define CAN_FA1R_FACT6                  (1U << 6)
#define CAN_FA1R_FACT7                  (1U << 7)
#define CAN_FA1R_FACT8                  (1U << 8)
#define CAN_FA1R_FACT9                  (1U << 9)
#define CAN_FA1R_FACT10                 (1U << 10)
#define CAN_FA1R_FACT11                 (1U << 11)
#define CAN_FA1R_FACT12                 (1U << 12)
#define CAN_FA1R_FACT13                 (1U << 13)
#define CAN_FA1R_FACT14                 (1U << 14)
#define CAN_FA1R_FACT15                 (1U << 15)
#define CAN_FA1R_FACT16                 (1U << 16)
#define CAN_FA1R_FACT17                 (1U << 17)
#define CAN_FA1R_FACT18                 (1U << 18)
#define CAN_FA1R_FACT19                 (1U << 19)
#define CAN_FA1R_FACT20                 (1U << 20)
#define CAN_FA1R_FACT21                 (1U << 21)
#define CAN_FA1R_FACT22                 (1U << 22)
#define CAN_FA1R_FACT23                 (1U << 23)
#define CAN_FA1R_FACT24                 (1U << 24)
#define CAN_FA1R_FACT25                 (1U << 25)
#define CAN_FA1R_FACT26                 (1U << 26)
#define CAN_FA1R_FACT27                 (1U << 27)

/*Define CAN baudrate */
#define CAN_BAUDRATE_1MBPS              1000000U
#define CAN_BAUDRATE_500KBPS            500000U
#define CAN_BAUDRATE_250KBPS            250000U
#define CAN_BAUDRATE_125KBPS            125000U
#define CAN_BAUDRATE_100KBPS            100000U
#define CAN_BAUDRATE_50KBPS             50000U
/*Define can mode */
#define CAN_MODE_NORMAL                 0U
#define CAN_MODE_LOOPBACK               1U
#define CAN_MODE_SILENT                 2U
#define CAN_MODE_SILENT_LOOPBACK        3U
/*Define CAN auto-off bus*/
#define CAN_AUTO_BUS_OFF_ENABLE          1U
#define CAN_AUTO_BUS_OFF_DISABLE         0U
/*Define CAN auto wake-up */
#define CAN_AUTO_WAKE_UP_ENABLE          1U
#define CAN_AUTO_WAKE_UP_DISABLE         0U
/*Define CAN auto retransmission */
#define CAN_AUTO_RETRANSMISSION_ENABLE   1U
#define CAN_AUTO_RETRANSMISSION_DISABLE  0U
/*Define CAN receive FIFO locked mode */
#define CAN_RECEIVE_FIFO_LOCK_ENABLE      1U
#define CAN_RECEIVE_FIFO_LOCK_DISABLE     0U

/*Define CAN identifier */
#define CAN_ID_STANDARD                 0U
#define CAN_ID_EXTENDED                 1U
/*Define CAN frame type */
#define CAN_RTR_DATA                   0U
#define CAN_RTR_REMOTE                 1U



/* Bus state errors*/
#define CAN_ERROR_WARNING               0x00010000U
#define CAN_ERROR_PASSIVE               0x00020000U
#define CAN_ERROR_BUS_OFF               0x00040000U



/*Define CAN TX mailbox number */
#define CAN_TX_MAILBOX_0                0U
#define CAN_TX_MAILBOX_1                1U
#define CAN_TX_MAILBOX_2                2U


#endif