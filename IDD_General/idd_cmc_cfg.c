/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_cmc_cfg.h"
#include "fsl_cmc.h"
#include "idd_mode_select.h"

uint32_t CMC_SRAMDIS = 0;

/* Power mode protection */
void CMC_Pmprot_CFG(uint32_t allowedModes)
{
    uint32_t reg;

    reg = CMC0->PMPROT;
    reg &= ~0xFUL;
    reg |= allowedModes;

    CMC0->PMPROT = reg;
}

void CMC_LowPower_CFG(idd_config_t * idd_param)
{
    cmc_power_domain_config_t                   CmcLowpowerConfigSource;
  
    CMC_SetPowerModeProtection(CMC0,idd_param->cmcPowerModeProtection);
    CmcLowpowerConfigSource.clock_mode = idd_param->cmcClockMode;
    CmcLowpowerConfigSource.main_domain = idd_param->cmcPowerModeMain;
    CmcLowpowerConfigSource.wake_domain = idd_param->cmcPowerModeWake;
    
    /* add a routine for register translation */
    if (idd_param->cmcSramRetain == 0)
    {
        CMC_PowerOffSRAMLowPowerOnly(CMC0, 0x0);
    }
    else if (idd_param->cmcSramRetain == 1)
    {
        /* 128K RAM retained. RAMC 64K + RAMD 64K */
        CMC_PowerOffSRAMLowPowerOnly(CMC0, 0xFFFFFF0F);
    }
    else if (idd_param->cmcSramRetain == 2)
    {
        /* 64K RAM retained. RAMC */
        CMC_PowerOffSRAMLowPowerOnly(CMC0, 0xFFFFFFCF);
    }
    else if (idd_param->cmcSramRetain == 3)
    {
        /* 32K RAM retained. RAMB */
        CMC_PowerOffSRAMLowPowerOnly(CMC0, 0xFFFFFFF7);;
    }
    else if (idd_param->cmcSramRetain == 4)
    {
        /* NO RAM retained */
        CMC_PowerOffSRAMLowPowerOnly(CMC0, 0xFFFFFFFF);
    }
    else 
    {
        //PRINTF("\nSRAM Retain param not set!\n");
    }
       
    /* add a routine for register translation */
    if (idd_param->cmcSramDisable == 0)
    {
        CMC_PowerOffSRAMAllMode(CMC0, 0x0);
    }
    else if (idd_param->cmcSramDisable == 1)
    {
        CMC_PowerOffSRAMAllMode(CMC0, 0xFFFFFF0F);
    }
    else if (idd_param->cmcSramDisable == 2)
    {
        CMC_PowerOffSRAMAllMode(CMC0, 0xFFFFFFCF);
    }
    else if (idd_param->cmcSramDisable == 3)
    {
        CMC_PowerOffSRAMAllMode(CMC0, 0xFFFFFFF7);
    }
    else if (idd_param->cmcSramDisable == 4)
    {
        CMC_PowerOffSRAMAllMode(CMC0, 0xFFFFFFFF);
    }
    else 
    {
        //PRINTF("\nSRAM Disable param not set!\n"); 
    }
    
    
    CMC_ConfigFlashMode(CMC0,idd_param->flashDoze,false);    
    CMC0->DBGCTL|=CMC_DBGCTL_SOD_MASK;
    
    CMC_SetClockMode(CMC0,CmcLowpowerConfigSource.clock_mode);       
    CMC_SetMAINPowerMode(CMC0,CmcLowpowerConfigSource.main_domain);
    CMC_SetWAKEPowerMode(CMC0,CmcLowpowerConfigSource.wake_domain);
}

void CMC_Active_CFG(idd_config_t * idd_param)
{
    CMC_ConfigFlashMode(CMC0,idd_param->flashDoze, idd_param->flashDis);
}