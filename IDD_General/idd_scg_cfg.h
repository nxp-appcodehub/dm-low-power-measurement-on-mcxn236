/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_SCG_CFG_H_
#define _IDD_SCG_CFG_H_

#include "fsl_common.h"
#include "idd_mode_select.h"

typedef struct _scg_low_power_config
{
    bool enableSysOscInSleep; /*!< Enable SOSC in sleep mode. */
    bool enableSircInSleep; /*!< Enable SIRC in sleep mode. */
    bool enableFircInSleep; /*!< Enable FIRC in sleep mode. */
} scg_low_power_config_t;

status_t SCG_LowPower_CLK_CFG(idd_config_t * idd_param);

status_t CLOCK_EnableSoscInDeepSleep(void);

status_t CLOCK_DisableSoscInDeepSleep(void);

status_t CLOCK_EnableSircInDeepSleep(void);

status_t CLOCK_DisableSircInDeepSleep(void);

status_t CLOCK_EnableFircInDeepSleep(void);

status_t CLOCK_DisableFircInDeepSleep(void);

void SCG_VBAT_FRO16k_CFG(idd_config_t * idd_param);

#endif 