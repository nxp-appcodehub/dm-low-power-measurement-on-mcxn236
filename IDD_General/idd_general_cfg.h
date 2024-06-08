/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_GENERAL_CFG_H_
#define _IDD_GENERAL_CFG_H_

#include "stdio.h"
#include "stdlib.h"
#include "fsl_common.h"
#include "fsl_wuu.h"
#include "idd_cmc_cfg.h"
#include "idd_mode_select.h"
#include "idd_spc_cfg.h"
#include "idd_syscon_cfg.h"
#include "idd_scg_cfg.h"
#include "board.h"
   
/*!
 * @brief Regulator configuration (based on board-level power configuration)
 */
typedef struct _spc_regulator_config
{
    bool coreldoEnable; /*!< CORELDO enable. */
    bool sysldoEnable; /*!< SYSLDO enable. */
    bool dcdcEnable; /*!< DCDC enable. */
} spc_regulator_config_t;


/*!
 * @brief Unlock all clock configuration registers.
 *
 * This function will unlock the SOSC, FIRC, SIRC, and ROSC
 * configuration registers.
 */
void CLOCK_UnlockAllClkConfig(void);

/*!
 * @brief Lock all clock configuration registers.
 *
 * This function will lock the SOSC, FIRC, SIRC, and ROSC
 * configuration registers.
 */
void CLOCK_LockAllClkConfig(void);

void PowerMode_CFG_Prepare(idd_config_t * idd_param);

void LowPower_Mode_CFG_PRE(idd_config_t * idd_param);

void LowPower_Mode_CFG(idd_config_t * idd_param);

void LowPower_Entry(idd_config_t * idd_param);

void Active_Mode_CFG(idd_config_t * idd_param);

void CLK_config(idd_config_t * idd_param);

void SYSCON_RAMx_CFG(void);

void TestMode_Enable(idd_config_t * idd_param);

void FMU_RWSC_CFG(idd_config_t * idd_param);

void Core_Clk_CFG(idd_config_t * idd_param);

void read_registers(idd_config_t * idd_param);

void sram_xen_dp_clear(void);

void WUU_Config(void);

void Select_Board_Configuration(unsigned char MuxSel);

void SYSTEM_SetupPowerConfig1A_PoweredWithDCDC(void);
void SYSTEM_SetupPowerConfig1B_PoweredWithDCDC(void);
void SYSTEM_SetupPowerConfig1C_PoweredWithDCDC(void);
void SYSTEM_SetupPowerConfig2A_PoweredWithLDO(void);
void SYSTEM_SetupPowerConfig2B_PoweredWithLDO(void);

void DisableMiscPeripherals(void);
void EnableMiscPeripherals(void);
void VBAT_Misc(idd_config_t * idd_param);
/*!
 * @brief Lock the SOSC configuration register.
 */
static inline void CLOCK_LockSysOscConfig(void)
{
    SCG0->SOSCCSR |= SCG_SOSCCSR_LK_MASK;
}

/*!
 * @brief Lock the FIRC configuration register.
 */
static inline void CLOCK_LockFircConfig(void)
{
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK;
}

/*!
 * @brief Lock the SIRC configuration register.
 */
static inline void CLOCK_LockSircConfig(void)
{
    SCG0->SIRCCSR |= SCG_SIRCCSR_LK_MASK;
}

/*!
 * @brief Lock the ROSC configuration register.
 */
static inline void CLOCK_LockRtcOscConfig(void)
{
    SCG0->ROSCCSR |= SCG_ROSCCSR_LK_MASK;
}

/*!
 * @brief Unlock the SOSC configuration register.
 */
static inline void CLOCK_UnlockSysOscConfig(void)
{
    SCG0->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;
}

/*!
 * @brief Unlock the FIRC configuration register.
 */
static inline void CLOCK_UnlockFircConfig(void)
{
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;
}

/*!
 * @brief Unlock the SIRC configuration register.
 */
static inline void CLOCK_UnlockSircConfig(void)
{
    SCG0->SIRCCSR &= ~SCG_SIRCCSR_LK_MASK;
}

/*!
 * @brief Unlock the ROSC configuration register.
 */
static inline void CLOCK_UnlockRtcOscConfig(void)
{
    SCG0->ROSCCSR &= ~SCG_ROSCCSR_LK_MASK;
}

#endif 