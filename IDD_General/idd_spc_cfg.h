/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_SPC_CFG_H_
#define _IDD_SPC_CFG_H_

#include "idd_mode_select.h"

enum board_config
{
  /* DCDC, Power with DCDC(DCDC/LDO_SYS enabled, LDO_CORE Disabled) */
  board_config_1A,
  /* Power with DCDC(DCDC enabled, LDO_CORE/LDO_SYS disabled) */
  board_config_1B,
  /* Power with DCDC(DCDC/LDO_CORE enabled, LDO_SYS disabled) */
  board_config_1C,
  /* LDO_3p3V, Power with LDO_CORE(LDO_CORE/SYS_LDO enabled, DCDC disabled) */
  board_config_2A, 
  /* LDO_1p8V, Power with LDO_CORE(LDO_CORE enabled, SYS_LDO/DCDC disabled) */
  board_config_2B,
};

void SPC_LowPower_CFG(idd_config_t * idd_param);


void SPC_SRAMCTL_CFG(idd_config_t * idd_param);

void SPC_Active_CFG(idd_config_t * idd_param);

#endif 