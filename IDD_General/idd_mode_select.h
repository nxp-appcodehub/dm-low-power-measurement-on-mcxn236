/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IDD_MODE_SELECT_H_
#define _IDD_MODE_SELECT_H_

#include "stdint.h"
  
typedef struct _idd_config
{
    uint8_t coreTask;   
    uint8_t caseSelect;    
    uint8_t clockSrc;
    uint8_t coreFreq;
    uint8_t disableLPCAC;
    uint8_t selectBoard;

    uint8_t codeExeRegion;
    uint8_t coreVoltage;
    uint8_t cmcPowerModeMain;
    uint8_t cmcPowerModeWake;
    uint8_t cmcClockMode;
    uint8_t cmcSramDisable;
    /* 0 - ALL RAM retained, 1 - 128K RAM retained: RAMC 64K, RAMD 64K, 2 - RAMC 64K, 3 - RAMB 32K, 4 - No RAM retained */
    uint8_t cmcSramRetain;
    uint8_t flashDoze;
    uint8_t flashDis;
    uint8_t flashWake;
    
    /* cmcPowerModeProtection£º Configures the lowest power mode that you can write to PMCTRLx[LPMODE] fields.  
       LPMODE: 0000b - Active/Sleep
               0001b - Deep Sleep
               0011b - Power Down
               1111b - Deep-Power Down
    */
    uint8_t cmcPowerModeProtection; 
    uint8_t cmcDebugCtrl;
    
    uint8_t scgFircEn;
    uint8_t scgSircBypassTrimPeriEn;
    uint8_t scgSoscEn;
    
    uint8_t sysconAHBClkCtrlx;
    uint8_t sysconAHBClkDiv;
    
    uint8_t spcCoreLdoDrive;
    uint8_t spcCoreLdoLevel;
    uint8_t spcSysLdoDrive;
    uint8_t spcDcdcDrive;
    uint8_t spcDcdcLevel;
    uint8_t glitchDetectDisable;   
    uint8_t spcVscalingEnable;
    uint8_t lowPowerBufferEnable;
    uint8_t spcBandgapMode;
    uint8_t lowPowerRefEnable;
    
    uint8_t spcLvdEnableCore;
    uint8_t spcLvdEnableSys;
    uint8_t spcLvdEnableIO;
    uint8_t spcHvdEnableCore;
    uint8_t spcHvdEnableSys;    
    uint8_t spcHvdEnableIO;
    
    uint8_t spcEvdIso;
    uint8_t spcEvdLpIso;
    
    uint8_t vBatFro16KEn;
    uint8_t vBatLDOCTLA;
    uint8_t vBatOsc32K;
    uint8_t vBatTamper;  
    uint8_t vBatLDORamRET;
    uint8_t vBatLDORamSwiIso;
    
    uint8_t rtcClkODis;
    uint8_t rtcClkSel;    
    uint8_t lowPowerLevel;
    uint8_t bleedEnable;
                 
    uint8_t fmuRwsc;
    
    uint8_t check1;
    uint8_t check2;
     
} idd_config_t;

enum core_task
{
   kIDD_While1 = 0,
   kIDD_CoreMark = 1,
   kIDD_While1_All_Peripherals,
   kIDD_CoreMark_All_Peripherals,
   kIDD_While1_OR_CoreMark,
   kIDD_WFI,
};



enum clock_src
{
    kClock_SRC_SIRC   = 0,
    kClock_SRC_FIRC   = 1,
    /* External OSC as PLL source */
    kClock_SRC_PLL    = 2,
    /* FIRC as PLL source */
    kClock_SRC_FIRC_PLL    = 3,
};

enum clock_freq
{
    kClock_Freq_SIRC_12M      = 12,
    kClock_Freq_FIRC_48M      = 48,
    kClock_Freq_FIRC_144M     = 144,
    kClock_Freq_PLL_96M       = 96,
    kClock_Freq_PLL_100M      = 100,
    kClock_Freq_PLL_150M      = 150,
};

enum LPCAC_state
{
    kLPCAC_Enable     = 0,
    kLPCAC_Disable     = 1,
};

enum peripheral_state
{
    kPeripheral_CLK_Disable    = 0,
    kPeripheral_CLK_Enable     = 1,
};

enum code_execute_region
{
    kCode_Exe_Region_Flash   = 0,
    kCode_Exe_Region_RAM    = 1,
};

enum flash_doze
{
    kCMC_Flash_No_Effect   = 0,
    kCMC_Flash_Disable_In_LpMode    = 1,
};

enum scg_firc_en
{
    kSCG_FIRC_Disable   = 0,
    kSCG_FIRC_Enable   = 1,
};

enum low_power_mode
{
    kLow_Power_Mode_ActiveSleep     = 0,
    kLow_Power_Mode_DeepSleep       = 1,
    kLow_Power_Mode_PowerDown       = 3,
    kLow_Power_Mode_DeepPowerDown   = 15,
};

enum low_power_level
{
    kPower_Mode_Static_Sleep        = 0,
    kPower_Mode_Dynamic_Active      = 1,
};

enum power_mode_protection
{
    kNot_Allowed                    = 0,
    kAllow_Deep_Sleep_Mode          = 1,
    kAllow_Power_Down_Mode          = 3,
    kAllow_Deep_Power_Down_Mode     = 15,
};

enum debug_ctrl
{
    kCMC_Debug_Ctrl_Enable       = 0,
    kCMC_Debug_Ctrl_Disable      = 1,
};

enum glitch_detect
{
    kSPC_Glitch_Detect_Enable    = 0,
    kSPC_Glitch_Detect_Disable   = 1,
};



enum spc_core_ldo_level
{
    kSPC_Core_LDO_Level_Mid_Vlot_1V0       = 1,
    kSPC_Core_LDO_Level_Normal_Vlot_1V1    = 2,
    kSPC_Core_LDO_Level_Over_Vlot_1V2    = 3,
    kSPC_Core_LDO_Level_Mid_Vlot_0V7     = 4,
    kVBAT                                = 5,
};

enum voltage_monitor_mode
{
    kVoltage_Monitor_Disable       = 0,
    kVoltage_Monitor_Enable        = 1,
};
    
enum vbat_ram_retain
{
    /* 8KB RAM is not retained in low-power modes */
    kVbat_RAM_Retain0       = 0,   
    kVbat_RAM_Retain1       = 1,
    kVbat_RAM_Retain2       = 2,
    kVbat_RAM_Retain3       = 3,
    kVbat_RAM_Retain4       = 4,
};

enum rtc_clk_select
{
    kRTC_Clk_16K       = 0,
    kRTC_Clk_32K       = 1,
};

enum core_vdd_ivs_enable
{
    kCore_VDD_IVS_Disable          = 0,
    kCore_VDD_IVS_Enable           = 1,
};


enum case_selection
{
    Symbol_IDD_ACT_OD_1          = 0,
    Symbol_IDD_CM_OD_1           = 5,
    Symbol_IDD_SLEEP             = 61,
    Symbol_IDD_DSLEEP_LP         = 69,
    Symbol_IDD_PDOWN_LP          = 86,
    Symbol_IDD_PDOWN_RET_0V7     = 103,
    Symbol_IDD_DPOWN_32K         = 109,
};


void IDD_paramConfig(idd_config_t * idd_param);

#endif /* _IDD_MODE_SELECT_H_ */
