/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_mode_select.h"
#include "fsl_debug_console.h"
#include "fsl_cmc.h"
#include "fsl_spc.h"


/*******************************************************************************
Function Name  : IDD_paramConfig(char)
Parameters     : idd parameter structure
Returns	       : NONE
Notes          : Selects power pattern.
*******************************************************************************/

void IDD_paramConfig(idd_config_t * idd_param)
{
    switch(idd_param->caseSelect)
    {
    case Symbol_IDD_ACT_OD_1:
        /* case 0 */ 
        PRINTF("IDD_ACT_OD_1\n\r");
        idd_param->coreTask              = kIDD_While1;  
        idd_param->clockSrc              = kClock_SRC_PLL;  
        idd_param->coreFreq              = 150;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Enable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Over_Vlot_1V2;  
        idd_param->cmcPowerModeMain      = kCMC_ActiveOrSleepMode;  
        idd_param->cmcPowerModeWake      = kCMC_ActiveOrSleepMode;  
        idd_param->cmcClockMode          = kCMC_GateNoneClock;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 0;  
        idd_param->flashDoze             = kCMC_Flash_No_Effect;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 0;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Enable;  
        idd_param->scgFircEn             = kSCG_FIRC_Disable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 1;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_NormalDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_OverDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_NormalDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_NormalDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_OverdriveVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Disable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapEnabledBufferDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Dynamic_Active;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 3;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

    case Symbol_IDD_CM_OD_1:
        /* case 5 */
        PRINTF("IDD_CM_OD_1\n\r");
        idd_param->coreTask              = kIDD_CoreMark;  
        idd_param->clockSrc              = kClock_SRC_PLL;  
        idd_param->coreFreq              = 150;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Enable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Over_Vlot_1V2;  
        idd_param->cmcPowerModeMain      = kCMC_ActiveOrSleepMode;  
        idd_param->cmcPowerModeWake      = kCMC_ActiveOrSleepMode;  
        idd_param->cmcClockMode          = kCMC_GateNoneClock;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 0;  
        idd_param->flashDoze             = kCMC_Flash_No_Effect;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 0;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Enable;  
        idd_param->scgFircEn             = kSCG_FIRC_Disable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 1;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_NormalDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_OverDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_NormalDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_NormalDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_OverdriveVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Disable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapEnabledBufferDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Dynamic_Active;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

    case Symbol_IDD_SLEEP:
        /* case 61 */
        PRINTF("IDD_SLEEP\n\r");
        idd_param->coreTask              = kIDD_WFI;  
        idd_param->clockSrc              = kClock_SRC_FIRC;  
        idd_param->coreFreq              = 48;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Disable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Mid_Vlot_1V0;  
        idd_param->cmcPowerModeMain      = kCMC_ActiveOrSleepMode;  
        idd_param->cmcPowerModeWake      = kCMC_ActiveOrSleepMode;  
#if (defined(WAKEUP_EN) && (WAKEUP_EN))
        idd_param->cmcClockMode          = kCMC_GateNoneClock;
#else 
        idd_param->cmcClockMode          = kCMC_GateCoreClock;
#endif 
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 0;  
        idd_param->flashDoze             = kCMC_Flash_Disable_In_LpMode;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 0;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Disable;  
        idd_param->scgFircEn             = kSCG_FIRC_Enable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 0;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_NormalDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_MidDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_NormalDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_NormalDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_MidVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Disable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapEnabledBufferDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Enable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Enable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Static_Sleep;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

    case Symbol_IDD_DSLEEP_LP:
        /* case 69 */
        PRINTF("IDD_DSLEEP_LP\n\r");
        idd_param->coreTask              = kIDD_WFI;  
        idd_param->clockSrc              = kClock_SRC_FIRC;  
        idd_param->coreFreq              = 48;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Disable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Mid_Vlot_1V0;  
        idd_param->cmcPowerModeMain      = kCMC_DeepSleepMode;  
        idd_param->cmcPowerModeWake      = kCMC_DeepSleepMode;  
        idd_param->cmcClockMode          = kCMC_GateAllSystemClocksEnterLowPowerMode;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 0;  
        idd_param->flashDoze             = kCMC_Flash_Disable_In_LpMode;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 1;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Disable;  
        idd_param->scgFircEn             = kSCG_FIRC_Enable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 0;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_LowDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_MidDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_LowDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_LowDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_MidVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Enable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Static_Sleep;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

    case Symbol_IDD_PDOWN_LP:
        /* case 86 */
        PRINTF("IDD_PDOWN_LP\n\r");
        idd_param->coreTask              = kIDD_WFI;  
        idd_param->clockSrc              = kClock_SRC_FIRC;  
        idd_param->coreFreq              = 48;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Disable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Mid_Vlot_1V0;  
        idd_param->cmcPowerModeMain      = kCMC_PowerDownMode;  
        idd_param->cmcPowerModeWake      = kCMC_PowerDownMode;  
        idd_param->cmcClockMode          = kCMC_GateAllSystemClocksEnterLowPowerMode;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 4;  
        idd_param->flashDoze             = kCMC_Flash_Disable_In_LpMode;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 3;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Disable;  
        idd_param->scgFircEn             = kSCG_FIRC_Enable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 0;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_LowDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_MidDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_LowDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_LowDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_MidVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Enable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain4;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Static_Sleep;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

    case Symbol_IDD_PDOWN_RET_0V7:
        /* case 103 */
        PRINTF("IDD_PDOWN_RET_0V7\n\r");
        idd_param->coreTask              = kIDD_WFI;  
        idd_param->clockSrc              = kClock_SRC_FIRC;  
        idd_param->coreFreq              = 48;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Disable;  
        idd_param->coreVoltage           = kSPC_Core_LDO_Level_Mid_Vlot_0V7;  
        idd_param->cmcPowerModeMain      = kCMC_PowerDownMode;  
        idd_param->cmcPowerModeWake      = kCMC_PowerDownMode;  
        idd_param->cmcClockMode          = kCMC_GateAllSystemClocksEnterLowPowerMode;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 0;  
        idd_param->flashDoze             = kCMC_Flash_Disable_In_LpMode;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 3;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Disable;  
        idd_param->scgFircEn             = kSCG_FIRC_Enable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 0;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_LowDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_MidDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_LowDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_LowDriveStrength;  
        idd_param->spcDcdcLevel          = 00;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Disable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 0;  
        idd_param->vBatLDOCTLA           = 0x0;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Static_Sleep;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;
        
    case Symbol_IDD_DPOWN_32K:
        /* case 109 */
        PRINTF("IDD_DPOWN_32K\n\r");
        idd_param->coreTask              = kIDD_WFI;  
        idd_param->clockSrc              = kClock_SRC_FIRC;  
        idd_param->coreFreq              = 48;  
        idd_param->codeExeRegion         = kCode_Exe_Region_Flash;  
        idd_param->disableLPCAC          = kLPCAC_Disable;  
        idd_param->coreVoltage           = kVBAT;  
        idd_param->cmcPowerModeMain      = kCMC_DeepPowerDown;  
        idd_param->cmcPowerModeWake      = kCMC_DeepPowerDown;  
        idd_param->cmcClockMode          = kCMC_GateAllSystemClocksEnterLowPowerMode;  
        idd_param->cmcSramDisable        = 0;  
        idd_param->cmcSramRetain         = 4;  
        idd_param->flashDoze             = kCMC_Flash_Disable_In_LpMode;  
        idd_param->flashDis              = 0x0;  
        idd_param->flashWake             = 0x0;  
        idd_param->cmcPowerModeProtection = 15;  
        idd_param->cmcDebugCtrl          = kCMC_Debug_Ctrl_Disable;  
        idd_param->scgFircEn             = kSCG_FIRC_Enable;  
        idd_param->scgSircBypassTrimPeriEn = 0;  
        idd_param->scgSoscEn             = 0;  
        idd_param->sysconAHBClkCtrlx     = 0;  
        idd_param->sysconAHBClkDiv       = 0x0;  
        idd_param->spcCoreLdoDrive       = kSPC_CoreLDO_LowDriveStrength;  
        idd_param->spcCoreLdoLevel       = kSPC_CoreLDO_MidDriveVoltage;  
        idd_param->spcSysLdoDrive        = kSPC_SysLDO_LowDriveStrength;  
        idd_param->spcDcdcDrive          = kSPC_DCDC_LowDriveStrength;  
        idd_param->spcDcdcLevel          = kSPC_DCDC_MidVoltage;  
        idd_param->glitchDetectDisable   = kSPC_Glitch_Detect_Enable;  
        idd_param->spcVscalingEnable     = kCore_VDD_IVS_Disable;  
        idd_param->lowPowerBufferEnable  = 0;  
        idd_param->spcBandgapMode        = kSPC_BandgapDisabled;  
        idd_param->lowPowerRefEnable     = 0;  
        idd_param->spcLvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcLvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableCore      = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableSys       = kVoltage_Monitor_Disable;  
        idd_param->spcHvdEnableIO        = kVoltage_Monitor_Disable;  
        idd_param->spcEvdIso             = 0;  
        idd_param->spcEvdLpIso           = 0;  
        idd_param->vBatFro16KEn          = 1;  
        idd_param->vBatLDOCTLA           = 0x7;  
        idd_param->vBatOsc32K            = 0;  
        idd_param->vBatLDORamRET         = kVbat_RAM_Retain0;  
        idd_param->vBatLDORamSwiIso      = 3;
        idd_param->rtcClkODis            = 0;  
        idd_param->rtcClkSel             = kRTC_Clk_16K;  
        idd_param->lowPowerLevel         = kPower_Mode_Static_Sleep;  
        idd_param->bleedEnable           = 0;  
        idd_param->fmuRwsc               = 2;  
        idd_param->check1                = 85;  
        idd_param->check2                = 170;  
        break;

  default: 
    PRINTF("No Case selected\n\r");
    break;
  }
}


