/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_SYSCON_CFG_H_
#define _IDD_SYSCON_CFG_H_

#include "idd_mode_select.h"

void SYSCON_Active_CFG(idd_config_t * idd_param);
void SYSCON_LPCAC_CFG(idd_config_t * idd_param);
void SYSCON_Flash_Speculation_CFG(void);

#endif 