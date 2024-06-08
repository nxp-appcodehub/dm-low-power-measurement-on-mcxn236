/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_scg_cfg.h"
#include "idd_mode_select.h"

status_t SCG_LowPower_CLK_CFG(idd_config_t * idd_param)
{
    /* SCG section */
    scg_low_power_config_t config_scg_low_power_clk;
    status_t status;
    
    /* params[pSCG_SOSCSTEN] */
    config_scg_low_power_clk.enableSysOscInSleep = false;
    config_scg_low_power_clk.enableFircInSleep  = false;
    config_scg_low_power_clk.enableSircInSleep = false;
    
  
    if (config_scg_low_power_clk.enableSysOscInSleep)
    {
        status = CLOCK_EnableSoscInDeepSleep();
    }
    else
    {
        status = CLOCK_DisableSoscInDeepSleep();
    }
    
    if (kStatus_Success != status)
    {
        return status;
    }   
    if (config_scg_low_power_clk.enableSircInSleep)
    {
        status = CLOCK_EnableSircInDeepSleep();
    }
    else
    {
        status = CLOCK_DisableSircInDeepSleep();
    }
    
    if (kStatus_Success != status)
    {
        return status;
    }
    if (config_scg_low_power_clk.enableFircInSleep)
    {
        status = CLOCK_EnableFircInDeepSleep();
    }
    else
    {
        status = CLOCK_DisableFircInDeepSleep();
    }
    if (kStatus_Success != status)
    {
        return status;
    }
    return status;
  
}

status_t CLOCK_EnableSoscInDeepSleep(void)
{
    SCG0->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;
    
    uint32_t reg = SCG0->SOSCCSR;    

    /* If configure register is locked, return error. */
    if (reg & SCG_SOSCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->SOSCCSR |= SCG_SOSCCSR_SOSCSTEN_MASK;
    
    SCG0->SOSCCSR |= SCG_SOSCCSR_LK_MASK;

    return kStatus_Success;
}

status_t CLOCK_DisableSoscInDeepSleep(void)
{
    SCG0->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;
  
    uint32_t reg = SCG0->SOSCCSR;

    /* If configure register is locked, return error. */
    if (reg & SCG_SOSCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->SOSCCSR &= ~SCG_SOSCCSR_SOSCSTEN_MASK;
    
    SCG0->SOSCCSR |= SCG_SOSCCSR_LK_MASK;

    return kStatus_Success;
}

status_t CLOCK_EnableFircInDeepSleep(void)
{
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;
    uint32_t reg = SCG0->FIRCCSR;

    /* If configure register is locked, return error. */
    if (reg & SCG_FIRCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->FIRCCSR |= SCG_FIRCCSR_FIRCSTEN_MASK;
    
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK;

    return kStatus_Success;
}

status_t CLOCK_DisableFircInDeepSleep(void)
{
    SCG0->FIRCCSR &= ~SCG_FIRCCSR_LK_MASK;  
    uint32_t reg = SCG0->FIRCCSR;

    /* If configure register is locked, return error. */
    if (reg & SCG_FIRCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->FIRCCSR &= ~SCG_FIRCCSR_FIRCSTEN_MASK;
    
    SCG0->FIRCCSR |= SCG_FIRCCSR_LK_MASK; 

    return kStatus_Success;
}

status_t CLOCK_EnableSircInDeepSleep(void)
{
    SCG0->SIRCCSR &= ~SCG_SIRCCSR_LK_MASK;
    uint32_t reg = SCG0->SIRCCSR;

    /* If configure register is locked, return error. */
    if (reg & SCG_SIRCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->SIRCCSR |= SCG_SIRCCSR_SIRCSTEN_MASK;
    
//    SCG0->SIRCCSR |= SCG_SIRCCSR_LK_MASK;

    return kStatus_Success;
}

status_t CLOCK_DisableSircInDeepSleep(void)
{
    SCG0->SIRCCSR &= ~SCG_SIRCCSR_LK_MASK;
    uint32_t reg = SCG0->SIRCCSR;

    /* If configure register is locked, return error. */
    if (reg & SCG_SIRCCSR_LK_MASK)
    {
        return kStatus_ReadOnly;
    }

    SCG0->SIRCCSR &= ~SCG_SIRCCSR_SIRCSTEN_MASK;
    
//    SCG0->SIRCCSR |= SCG_SIRCCSR_LK_MASK;

    return kStatus_Success;
}

void SCG_VBAT_FRO16k_CFG(idd_config_t * idd_param)
{
    if(idd_param->vBatFro16KEn == 0)
    {
      VBAT0->FROCTLA &= ~VBAT_FROCTLA_FRO_EN_MASK;
    }
    else
    {
      VBAT0->FROCTLA |= VBAT_FROCTLA_FRO_EN_MASK;
    }
    
    if(idd_param->vBatFro16KEn == 0)
    {
      VBAT0->FROCLKE &= ~0x1;
    }
    else
    {
      VBAT0->FROCLKE |= 0x1;
    }
}