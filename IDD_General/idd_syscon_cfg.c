/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_syscon_cfg.h"
#include "idd_mode_select.h"
#include "fsl_common.h"

void SYSCON_Active_CFG(idd_config_t * idd_param)
{
    SYSCON_LPCAC_CFG(idd_param);
//    SYSCON_Flash_Speculation_CFG();
}

void SYSCON_LPCAC_CFG(idd_config_t * idd_param)
{       
    if(idd_param->disableLPCAC == kLPCAC_Enable)
    {
      SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK;
    }
}

void SYSCON_Flash_Speculation_CFG(void)
{
    SYSCON->NVM_CTRL &= ~SYSCON_NVM_CTRL_DIS_MBECC_ERR_INST_MASK;
    SYSCON->NVM_CTRL &= ~SYSCON_NVM_CTRL_DIS_MBECC_ERR_DATA_MASK;
    SYSCON->NVM_CTRL &= ~SYSCON_NVM_CTRL_DIS_DATA_SPEC_MASK;
}

