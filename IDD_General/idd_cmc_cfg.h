/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_CMC_CFG_H_
#define _IDD_CMC_CFG_H_

#include "fsl_common.h"
#include "idd_mode_select.h"


void CMC_Pmprot_CFG(uint32_t allowedModes);

void CMC_LowPower_CFG(idd_config_t * idd_param);

void CMC_Active_CFG(idd_config_t * idd_param);

static inline void CMC_Dbgctl_CFG(bool enable)
{
    if (!enable)
    {
        CMC0->DBGCTL &= ~CMC_DBGCTL_SOD_MASK;
    }
    else
    {
        CMC0->DBGCTL |= CMC_DBGCTL_SOD_MASK;
    }      
}

#endif 