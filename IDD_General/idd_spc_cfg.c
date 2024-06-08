/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_spc_cfg.h"
#include "fsl_spc.h"
#include "idd_mode_select.h"
#include "IDD.h"

extern uint32_t SPC0_EVD_CFG;

void delay_main(int delay, int number_time)
{
  unsigned int i, n;
  for(i=0;i<number_time;i++)
  {
    for(n=0;n<delay;n++)
    {
      asm("nop");
    }
  }
}

void SPC_LowPower_CFG(idd_config_t * idd_param)
{
    spc_lowpower_mode_regulators_config_t       SpcLowPowerConfigSource;
    SpcLowPowerConfigSource.bandgapMode = idd_param->spcBandgapMode;  
    SpcLowPowerConfigSource.CoreIVS = idd_param->spcVscalingEnable;
    SpcLowPowerConfigSource.CoreLDOOption.CoreLDODriveStrength = idd_param->spcCoreLdoDrive;    
    SpcLowPowerConfigSource.CoreLDOOption.CoreLDOVoltage = idd_param->spcCoreLdoLevel;
    SpcLowPowerConfigSource.DCDCOption.DCDCDriveStrength = idd_param->spcDcdcDrive;
    SpcLowPowerConfigSource.DCDCOption.DCDCVoltage = idd_param->spcDcdcLevel;
    SpcLowPowerConfigSource.lpBuff = idd_param->lowPowerBufferEnable;
    SpcLowPowerConfigSource.lpIREF = idd_param->lowPowerRefEnable;
    SpcLowPowerConfigSource.SysLDOOption.SysLDODriveStrength = idd_param->spcSysLdoDrive;
    SPC_SetLowPowerModeRegulatorsConfig(SPC0,&SpcLowPowerConfigSource);
    

    SPC_EnableLowPowerModeCoreLowVoltageDetect(SPC0, idd_param->spcLvdEnableCore);
    SPC_EnableLowPowerModeSystemLowVoltageDetect(SPC0, idd_param->spcLvdEnableSys);
    SPC_EnableLowPowerModeSystemHighVoltageDetect(SPC0, idd_param->spcHvdEnableSys);
    SPC_EnableLowPowerModeIOLowVoltageDetect(SPC0, idd_param->spcLvdEnableIO);
    SPC_EnableLowPowerModeCoreHighVoltageDetect(SPC0, idd_param->spcHvdEnableCore);
    SPC_EnableLowPowerModeIOHighVoltageDetect(SPC0, idd_param->spcHvdEnableIO);
    
    if (idd_param->glitchDetectDisable == 1)
    {
        SPC0->LP_CFG |= (1 << 12); //SET glitch detect
    }
    else if (idd_param->glitchDetectDisable == 0)
    {
        SPC0->LP_CFG &= ~(1 << 12); //clear glitch detect
    }
    else 
    { 
        //PRINTF("\nSPC Glitch Detect Disable bit not set!\n");
    }    
    
    //SPC0->EVD_CFG = SPC_EVD_CFG_EVDISO(0)|SPC_EVD_CFG_EVDLPISO(0);
    
}



void SPC_Active_CFG(idd_config_t * idd_param)
{
    spc_active_mode_regulators_config_t         SpcActiveConfigSource;
    spc_system_voltage_detect_config_t          vd_sys_config;
    spc_core_voltage_detect_config_t            vd_core_config;
    spc_io_voltage_detect_config_t              vd_io_config;
  
    /* Enable GLITCH_DETECT */ 
    if(idd_param->glitchDetectDisable == 0)
    {
        SPC0->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_GLITCH_DETECT_DISABLE_MASK;
    }
    /* Disable GLITCH_DETECT */
    else 
    {
        SPC0->ACTIVE_CFG |= SPC_ACTIVE_CFG_GLITCH_DETECT_DISABLE_MASK;          
    }
    
    /* HVD/LVD on vdd_core */
    vd_core_config.option.HVDInterruptEnable = false;
    vd_core_config.option.HVDResetEnable = false;
    vd_core_config.option.LVDInterruptEnable = false;
    vd_core_config.option.LVDResetEnable = false; 
    SPC_SetCoreVoltageDetectConfig(SPC0,&vd_core_config);

    /* HVD/VLD on vdd_sys */
    vd_sys_config.option.HVDInterruptEnable = false;
    vd_sys_config.option.HVDResetEnable = false;  
    vd_sys_config.option.LVDInterruptEnable = false;
    vd_sys_config.option.LVDResetEnable = false;
    vd_sys_config.level = kSPC_LowVoltageNormalLevel;    
    SPC_SetSystemVoltageDetectConfig(SPC0,&vd_sys_config);
    
    /* HVD/VLD on vdd_io */
    vd_io_config.option.HVDInterruptEnable = false;
    vd_io_config.option.HVDResetEnable = false;
    vd_io_config.option.LVDInterruptEnable = false;
    vd_io_config.option.LVDResetEnable = false;
    /* LDO3.3V, VDD_IO LVD should use normal mode (high range) */
    if(idd_param->selectBoard == board_config_2A)
    {
        vd_io_config.level = kSPC_LowVoltageNormalLevel;
    }
    else
    {
        /* VDD_IO LVD use safe mode (low range) */
        vd_io_config.level = kSPC_LowVoltageSafeLevel;
    }
    SPC_SetIOVoltageDetectConfig(SPC0,&vd_io_config);
  
    SPC_EnableActiveModeCoreLowVoltageDetect(SPC0, idd_param->spcLvdEnableCore);
    SPC_EnableActiveModeSystemLowVoltageDetect(SPC0, idd_param->spcLvdEnableSys);
    SPC_EnableActiveModeSystemHighVoltageDetect(SPC0, idd_param->spcHvdEnableSys);
    SPC_EnableActiveModeIOLowVoltageDetect(SPC0, idd_param->spcLvdEnableIO);
    SPC_EnableActiveModeCoreHighVoltageDetect(SPC0, idd_param->spcHvdEnableCore);
    SPC_EnableActiveModeIOHighVoltageDetect(SPC0, idd_param->spcHvdEnableIO);
    
    //SPC0->ACTIVE_CFG1 &= ~SPC_ACTIVE_CFG1_SOC_CNTRL_MASK;
                
    SpcActiveConfigSource.bandgapMode = idd_param->spcBandgapMode; 
    SpcActiveConfigSource.lpBuff = idd_param->lowPowerBufferEnable;
    SpcActiveConfigSource.CoreLDOOption.CoreLDODriveStrength = idd_param->spcCoreLdoDrive;         
    SpcActiveConfigSource.CoreLDOOption.CoreLDOVoltage = kSPC_CoreLDO_MidDriveVoltage;  
    
    SpcActiveConfigSource.SysLDOOption.SysLDODriveStrength = idd_param->spcSysLdoDrive;     

    SpcActiveConfigSource.SysLDOOption.SysLDOVoltage = kSPC_SysLDO_NormalVoltage;
   
    SpcActiveConfigSource.DCDCOption.DCDCDriveStrength = idd_param->spcDcdcDrive;
    
    SpcActiveConfigSource.DCDCOption.DCDCVoltage = idd_param->spcDcdcLevel;    
    
    SPC_SetActiveModeRegulatorsConfig(SPC0,&SpcActiveConfigSource);  
    
    delay_main(100,100);
    
    SpcActiveConfigSource.CoreLDOOption.CoreLDOVoltage = idd_param->spcCoreLdoLevel; 
    
    SPC_SetActiveModeRegulatorsConfig(SPC0,&SpcActiveConfigSource);     
    
    SPC0_EVD_CFG = SPC_EVD_CFG_EVDISO(idd_param->spcEvdIso)|SPC_EVD_CFG_EVDLPISO(idd_param->spcEvdLpIso);
    
}

void SPC_SRAMCTL_CFG(idd_config_t * idd_param)
{    
    if(idd_param->spcDcdcLevel == kSPC_DCDC_OverdriveVoltage)
    {
       /* SRAM configured for 1.2V operation */
       spc_sram_voltage_config_t sramOption;
       sramOption.operateVoltage = kSPC_sramOperateAt1P2V;
       sramOption.requestVoltageUpdate =  true;
       (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption); 
    }
    if(idd_param->spcDcdcLevel == kSPC_DCDC_NormalVoltage)
    {
       /* SRAM configured for 1.1V operation */
       spc_sram_voltage_config_t sramOption;
       sramOption.operateVoltage = kSPC_sramOperateAt1P1V;
       sramOption.requestVoltageUpdate =  true;
       (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }
    if(idd_param->spcDcdcLevel == kSPC_DCDC_MidVoltage)
    {
       /* SRAM configured for 1.0V operation */
       spc_sram_voltage_config_t sramOption;
       sramOption.operateVoltage = kSPC_sramOperateAt1P0V;
       sramOption.requestVoltageUpdate =  true;
       (void)SPC_SetSRAMOperateVoltage(SPC0, &sramOption);
    }   
}