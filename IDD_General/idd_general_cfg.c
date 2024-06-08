/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "idd_general_cfg.h"
#include "fsl_cmc.h"
#include "fsl_debug_console.h"
#include "fsl_spc.h"
  
bool g_coreldoEnabled = true;
bool g_sysldoEnabled = true;
bool g_dcdcEnabled = true;
uint32_t SPC0_EVD_CFG = 0;
uint32_t RTC0_CTRL =    0;
uint32_t RTC0_STATUS =  0;
uint32_t VBAT_LDORAMC = 0;
extern uint32_t CMC_SRAMDIS;

uint32_t SYSCON_AHBCLKCTRL0 = 0;
uint32_t SYSCON_AHBCLKCTRL1 = 0;
uint32_t SYSCON_AHBCLKCTRL2 = 0;
uint32_t SYSCON_AHBCLKCTRL3 = 0;

void CLOCK_LockAllClkConfig(void)
{
    CLOCK_LockSysOscConfig();
    CLOCK_LockFircConfig();
    CLOCK_LockSircConfig();
    CLOCK_LockRtcOscConfig();
}

void CLOCK_UnlockAllClkConfig(void)
{
    CLOCK_UnlockSysOscConfig();
    CLOCK_UnlockFircConfig();
    CLOCK_UnlockSircConfig();
    CLOCK_UnlockRtcOscConfig();
}

void PowerMode_CFG_Prepare(idd_config_t * idd_param)
{
    /* Configure the lowest power mode that you can write to PMCTRLx[LPMODE] fields. */
    CMC_Pmprot_CFG(idd_param->cmcPowerModeProtection);

    /* For static cases, debug function is disabled when core sleeps. */
    CMC_Dbgctl_CFG(idd_param->cmcDebugCtrl);  
}


void LowPower_Mode_CFG(idd_config_t * idd_param)
{
    SYSCON_LPCAC_CFG(idd_param);
    
    /* Config CMC Section 
       config PMPROT,ClockMode,PowerMode,FLASHdoze,DBGCTL, SRAM
    */
    CMC_LowPower_CFG(idd_param);
    
    /* Config SPC section 
       config Bandgapmode,coreDrive,coreVoltage,IRef,LVD,HVD,glitch detect
    */
    SPC_LowPower_CFG(idd_param);
    
    SYSCON->AUTOCLKGATEOVERRIDE &= ~0xFFFF; 
    
    /* For sleep cases, ACTIVE_CFG should be used. */
    if(idd_param->cmcPowerModeProtection == 0)
    {
        SPC0->ACTIVE_CFG = SPC0->LP_CFG;
        FMU_RWSC_CFG(idd_param);
        SPC_SRAMCTL_CFG(idd_param);
    }
    else if (idd_param->spcDcdcLevel != 0)
    {      
        SPC0->ACTIVE_CFG = (SPC0->ACTIVE_CFG & ~SPC_ACTIVE_CFG_CORELDO_VDD_LVL_MASK) | (SPC0->LP_CFG & SPC_LP_CFG_CORELDO_VDD_LVL_MASK);
        SPC0->ACTIVE_CFG = (SPC0->ACTIVE_CFG & ~SPC_ACTIVE_CFG_CORELDO_VDD_DS_MASK) | (SPC0->LP_CFG & SPC_LP_CFG_CORELDO_VDD_DS_MASK);
        SPC0->ACTIVE_CFG = (SPC0->ACTIVE_CFG & ~SPC_ACTIVE_CFG_DCDC_VDD_LVL_MASK) | (SPC0->LP_CFG & SPC_LP_CFG_DCDC_VDD_LVL_MASK);
        SPC0->ACTIVE_CFG = (SPC0->ACTIVE_CFG & ~SPC_ACTIVE_CFG_DCDC_VDD_DS_MASK) | (SPC0->LP_CFG & SPC_LP_CFG_DCDC_VDD_DS_MASK);              
    }
    
    SPC0_EVD_CFG = SPC_EVD_CFG_EVDISO(idd_param->spcEvdIso)|SPC_EVD_CFG_EVDLPISO(idd_param->spcEvdLpIso);

    /* Config FIRC,SIRC status in deep sleep mode */
    SCG_LowPower_CLK_CFG(idd_param);
}



void LowPower_Entry(idd_config_t * idd_param)
{
#if (defined(WAKEUP_EN) && (WAKEUP_EN))
    WUU_Config();
  
    CLOCK_EnableClock(kCLOCK_Gpio3);
  
    if(idd_param->caseSelect == Symbol_IDD_SLEEP)
    /* Sleep mode for quick wake up */  
      SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    else
      SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    /* Added initiate event in order to run WFE twice all time. */
    __SEV();                             
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;
    /* Toggle P3_11 for measure wake-up time */
    GPIO3->PTOR = 0x00000800; 
    __DSB();
    /* clear event */
    __WFE();
    /* enter low power mode*/
    __WFE(); 
    /* Toggle P3_11 for measure wake-up time */
    GPIO3->PTOR = 0x00000800; 
  
#else  
    /* Set the SLEEPDEEP bit to enable deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    __DSB();
    __WFI();
    __ISB();
#endif
}

void WUU_Config(void)
{
    wuu_external_wakeup_pin_config_t wakeupButtonConfig;
  
    wakeupButtonConfig.edge  = kWUU_ExternalPinFallingEdge;
    wakeupButtonConfig.event = kWUU_ExternalPinInterrupt;
    wakeupButtonConfig.mode  = kWUU_ExternalPinActiveAlways;
    WUU_SetExternalWakeUpPinsConfig(WUU0, 4, &wakeupButtonConfig);
}

void Active_Mode_CFG(idd_config_t * idd_param)
{
    /* Configure Glitch detect, HVD, LVD, bandgap, coreVoltage, coreDrivestrength, EVD */
    SPC_Active_CFG(idd_param);
    
    /* Disable ECC function of RAMD, RAMC, RAMB, RAMX, RAMA */    
    SYSCON->ECC_ENABLE_CTRL &= ~0xF;
    /* Auto clock gating is enabled for RAME, RAMD, RAMC, RAMB */
    SYSCON->AUTOCLKGATEOVERRIDE &= ~0xFFFF; 
    SYSCON->AUTOCLKGATEOVERRIDE |= 0xFE03; 
    SYSCON->LPCAC_CTRL = (SYSCON->LPCAC_CTRL & ~SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK) | SYSCON_LPCAC_CTRL_DIS_LPCAC(idd_param->disableLPCAC);
        
    FMU_RWSC_CFG(idd_param);
    SPC_SRAMCTL_CFG(idd_param);
    
    SYSCON->NVM_CTRL &= ~SYSCON_NVM_CTRL_DIS_MBECC_ERR_DATA_MASK;
    SYSCON_Active_CFG(idd_param);
    /* Configure Flash mode */
    CMC_Active_CFG(idd_param);
}

void Core_Clk_CFG(idd_config_t * idd_param)
{
    if(idd_param->clockSrc == kClock_SRC_SIRC)
    {
        /* select SIRC */
        BOARD_BootClockFRO12M(); 
    }
    else if(idd_param->clockSrc == kClock_SRC_FIRC)
    { 
      /* select FIRC */
      if(idd_param->coreFreq == kClock_Freq_FIRC_144M)
      {
          BOARD_BootClockFROHF144M();
      }
      else if(idd_param->coreFreq == kClock_Freq_FIRC_48M)
      {
          BOARD_BootClockFROHF48M();
      }
    }
     else if(idd_param->clockSrc == kClock_SRC_PLL)
     {
         BOARD_BootClockPLL150M();
     }
}

void CLK_config(idd_config_t * idd_param)
{
    /* Unlock the clock source registers in case modifying setting */
    CLOCK_UnlockAllClkConfig(); 
    SCG0->LDOCSR &= ~SCG_LDOCSR_LDOEN_MASK;
    SCG0->FIRCCFG &= ~SCG_FIRCCFG_RANGE_MASK; //clears FIRCCFG if not already
    SCG0->FIRCCSR &= ~(SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK|SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK);
    
    if(idd_param->clockSrc == kClock_SRC_SIRC)
    {
        /* select SIRC */
        BOARD_BootClockFRO12M(); 
    }
    else if(idd_param->clockSrc == kClock_SRC_FIRC)
    { 
      /* select FIRC */
      if(idd_param->coreFreq == kClock_Freq_FIRC_144M)
      {
          BOARD_BootClockFROHF144M();
          SCG0->FIRCCSR &= ~SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK;
          SCG0->FIRCCSR &= ~SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;
      }
      else if(idd_param->coreFreq == kClock_Freq_FIRC_48M)
      {
          BOARD_BootClockFROHF48M();
          SCG0->FIRCCSR &= ~SCG_FIRCCSR_FIRC_FCLK_PERIPH_EN_MASK;
          SCG0->FIRCCSR &= ~SCG_FIRCCSR_FIRC_SCLK_PERIPH_EN_MASK;
      }
    }
    else if(idd_param->clockSrc == kClock_SRC_PLL)
    {
        if(idd_param->coreFreq == kClock_Freq_PLL_96M)
         {
             //BOARD_BootClockPLL96M();
         }
         else if(idd_param->coreFreq == kClock_Freq_PLL_100M)
         {
             BOARD_BootClockPLL100M();
         }
         else if(idd_param->coreFreq == kClock_Freq_PLL_150M)
         {
             BOARD_BootClockPLL150M();
         }
     }
    
    /* RTC is enabled, but the selelcted clk (FRO16K or OSC32K) is disabled for other peripherals */
    if(idd_param->rtcClkODis == 1) 
    {   
        VBAT0->FROCLKE |= 0xF;
        /* bit 6 - RTC , access RTC */
        SYSCON->AHBCLKCTRL1 |= 0x40;
        /* The selected clock is not output to other peripherals */
        RTC0->CTRL |= RTC_CTRL_CLKO_DIS_MASK;
        /* set up RTC->CTRL to select clock source - 16 kHz or 32 kHz */
        RTC0->CTRL = (RTC0->CTRL & ~RTC_CTRL_CLK_SEL_MASK) | RTC_CTRL_CLK_SEL(idd_param->rtcClkSel); 
        RTC0_CTRL = RTC0->CTRL;
        RTC0_STATUS = RTC0->STATUS;
      
    }  
    /* RTC is disabled, but the selected clk (lp_osc) is enabled for other peripherals */
    else
    { 
        VBAT0->FROCLKE |= 0xF;
        /* bit 6 - RTC , access RTC */
        SYSCON->AHBCLKCTRL1 |= 0x40;
        /* CLKO bit of control register - enable RTC output to perifs */
        RTC0->CTRL &= ~RTC_CTRL_CLKO_DIS_MASK;
        RTC0_CTRL = RTC0->CTRL;
        RTC0_STATUS = RTC0->STATUS;
        SYSCON->AHBCLKCTRL1 &= ~0x40;
        VBAT0->FROCLKE &= ~0xF;
    } 
    
     /* Disable SIRC*/
    if (idd_param->scgSircBypassTrimPeriEn == 0)
    {
        SCG0->SIRCCSR &= ~SCG_SIRCCSR_SIRCSTEN_MASK;   
        SCG0->SIRCCSR &= ~(SCG_SIRCCSR_SIRC_CLK_PERIPH_EN_MASK);
        /* SIRCVLD is 1 by default */
        SCG0->SIRCCSR &= ~(SCG_SIRCCSR_SIRCVLD_MASK);
    } 
    else if (idd_param->scgSircBypassTrimPeriEn == 1) 
    {
        SCG0->SIRCCSR |= 0x1800822;
    }
      /* Disable SysOsc*/
    if (idd_param->scgSoscEn == 0)
    {
      SCG0->SOSCCSR &= ~SCG_SOSCCSR_SOSCEN_MASK;    
    }
    else if (idd_param->scgSoscEn == 1)
    {
      SCG0->SOSCCSR |= (SCG_SOSCCSR_SOSCCM_MASK|SCG_SOSCCSR_SOSCEN_MASK);
    }
     /* Disable FIRC*/
    if (idd_param->scgFircEn == 0)
    {
      SCG0->FIRCCSR &= ~(SCG_FIRCCSR_FIRCEN_MASK);
    }
    
    /* config FRO16K */
    VBAT0->FROCTLA &= ~VBAT_FROCTLA_FRO_EN_MASK;
    VBAT0->FROCTLA |= idd_param->vBatFro16KEn;
    VBAT0->FROCTLB = ~idd_param->vBatFro16KEn; 
    
    /* Config OSC32K */
    if (idd_param->vBatOsc32K == 1) 
    {
        VBAT0->OSCCFGA |= (7 << 9) & 0xE00;            //set starup time of OSC_32K = 0.5 ms 
        VBAT0->OSCCFGB |= VBAT_OSCCFGB_INVERSE_MASK;
        VBAT0->OSCCFGB &= ~((7 << 9) & 0xE00);
      
        /* below steps from security RM rev 1 */
        //PRINTF("\nOSC32K Switched mode\n");
        VBAT0->OSCCTLA |= (VBAT_OSCCTLA_MODE_EN(2) | VBAT_OSCCTLA_CAP_SEL_EN_MASK
                           | VBAT_OSCCTLA_OSC_EN_MASK);
        VBAT0->OSCCTLB &= ~0xFFFFF;
        VBAT0->OSCCTLB |= 0xDFF7E;

        while ((VBAT0->STATUSA & VBAT_STATUSA_OSC_RDY_MASK) == 0) {}
        VBAT0->OSCLCKA |= 0x1;
        VBAT0->OSCLCKB |= 0x0;
    }   
    
    VBAT0->OSCCTLA &= ~VBAT_OSCCTLB_INVERSE_MASK;
    VBAT0->OSCCTLA |= idd_param->vBatOsc32K;
    
    VBAT0->OSCCTLB = (VBAT0->OSCCTLB & ~VBAT_OSCCTLB_INVERSE_MASK) | VBAT_OSCCTLB_INVERSE(~idd_param->vBatOsc32K);
    
    /* RTC is enabled. */
    if(idd_param->rtcClkODis == 1)      
    {
        /* connect OSC32K to VBAT domain */
        if(idd_param->rtcClkSel == kRTC_Clk_32K)
        {
            VBAT0->OSCCLKE |= 0x1; 
            VBAT0->FROCLKE = 0X0;
        }
        else
        {
            /* connect FRO16K to VBAT domain */
            VBAT0->FROCLKE = 0x1;
        }
    }
    
    /* Lock the clock source registers, no change is allowed */
    CLOCK_LockAllClkConfig();
}

void VBAT_Misc(idd_config_t * idd_param)
{     
  if(idd_param->vBatTamper == 1)
  {
    VBAT0->TAMPERA &= ~VBAT_TAMPERA_POR_DET_MASK;
    VBAT0->TAMPERA |= 0x13C1;
    
    VBAT0->TAMPERB &= ~0xFFFF;
    VBAT0->TAMPERB |= 0xEC00; //0xEC3E;  
  }
  else 
  {
    VBAT0->TAMPERA |= VBAT_TAMPERA_POR_DET_MASK;
    VBAT0->TAMPERB = 0xEFC0; //0xFFC0; //0xFFFE; 
    //PRINTF("\nKeeping VBAT_TAMPERA and VBAT_TAMPERB as defaults.\n");
  }

  VBAT0->TAMCTLB |= 0xF;
  
  VBAT0->LDOCTLA = idd_param->vBatLDOCTLA;
  VBAT0->LDOCTLB = 7 - idd_param->vBatLDOCTLA; 

  /* Manually switch VBAT to power SRAMA */
  if(idd_param->vBatLDORamSwiIso > 0)
  {
      /* Isolate the SRAM array */
      VBAT0->LDORAMC |= (idd_param->vBatLDORamSwiIso & 0x1);
      /* Switch the supply from VDD_CORE to the VBAT retention LDO */
      VBAT0->LDORAMC |= (idd_param->vBatLDORamSwiIso & 0x2);
  }
  
  int VBAT_LDORAM_RET = idd_param->vBatLDORamRET;  
  while(VBAT_LDORAM_RET > 0)///fix this
  {
    VBAT_LDORAM_RET--;
    VBAT0->LDORAMC |= ((1<<(3-VBAT_LDORAM_RET)) << 8 ) & 0xF00;
    VBAT_LDORAMC |= ((1<<(3-VBAT_LDORAM_RET)) << 8 ) & 0xF00;
  } 
  VBAT_LDORAMC |= idd_param->vBatLDORamSwiIso;
}

void DisableMiscPeripherals(void) //AHBCLKCTRLCLR
{  
    /* Bit 8, Bit 7, Bit 6 are 1 by default, need to clear them. */
    /* bit 10: FMC, bit 9: FMU, bit 1: ROM, bit 5- bit 2: RAME-RAMB. ROM is disabled. FMC, FMU, RAMx keep enabled. bit 14: PORT1, used for UART4 */
    SYSCON->AHBCLKCTRLCLR[0] = 0x3EFBB1C2U;
    /* RTC bit 6, bit 15: FC4 not disabled yet, as it is used as UART4. These two bits will be disabled later. */
    SYSCON->AHBCLKCTRLCLR[1] = 0xAC677C1BU;   // 
    /* bit 27: reserved, default value = 1, SCG: bit 26, not disable. */
    SYSCON->AHBCLKCTRLCLR[2] = 0x23E7C1F2U;
    SYSCON->AHBCLKCTRLCLR[3] = 0x078807F3U;
}

/* AHBCLKCTRLSET */
void EnableMiscPeripherals(void)
{
#if (defined(ENABLE_MISCPERIFS) && (ENABLE_MISCPERIFS)) 
    /* 2 corresponds to ROM bit - gate this */
    SYSCON->AHBCLKCTRLCLR[0] = 0xFEFBF802U; 
    SYSCON->AHBCLKCTRLCLR[1] = 0xAFFFFF3FU;
    SYSCON->AHBCLKCTRLCLR[2] = 0x67FFE1FFU;
    SYSCON->AHBCLKCTRLCLR[3] = 0xFFCFFFFU;
    SYSCON->AHBCLKCTRLSET[3] = 0b1000;
#else  
    SYSCON->AHBCLKCTRLSET[0] = 0x3EFBF63EU; 
    SYSCON->AHBCLKCTRLSET[1] = 0xAC67FC5BU; 
    SYSCON->AHBCLKCTRLSET[2] = 0x27E7C1F2U; 
    SYSCON->AHBCLKCTRLSET[3] = 0x078807F3;  
#endif
}



void FMU_RWSC_CFG(idd_config_t * idd_param)
{
   if(idd_param->coreFreq > 100)
   {
      FMU0->FCTRL &= ~FMUTEST_FCTRL_RWSC_MASK; 
      FMU0->FCTRL |= FMUTEST_FCTRL_RWSC(3);
   }
   if(idd_param->coreFreq == 100)
   {
      FMU0->FCTRL &= ~FMUTEST_FCTRL_RWSC_MASK; 
      FMU0->FCTRL |= FMUTEST_FCTRL_RWSC(2);
   }
   if(idd_param->coreFreq == 48)
   {
      FMU0->FCTRL &= ~FMUTEST_FCTRL_RWSC_MASK; 
      FMU0->FCTRL |= FMUTEST_FCTRL_RWSC(1);
   }
   if(idd_param->coreFreq == 12)
   {
      FMU0->FCTRL &= ~FMUTEST_FCTRL_RWSC_MASK; 
      FMU0->FCTRL |= FMUTEST_FCTRL_RWSC(0);
   } 
}

status_t SPC_SetRegulatorConfig(SPC_Type *base, const spc_regulator_config_t *config)
{
    assert(config);
    uint32_t reg = SPC_CNTRL_CORELDO_EN(config->coreldoEnable) | SPC_CNTRL_SYSLDO_EN(config->sysldoEnable) | SPC_CNTRL_DCDC_EN(config->dcdcEnable);

    base->CNTRL = reg;
    if (base->CNTRL != reg)
    {
        return kStatus_Fail;
    }
    g_coreldoEnabled = config->coreldoEnable;
    g_sysldoEnabled = config->sysldoEnable;
    g_dcdcEnabled = config->dcdcEnable;
    return kStatus_Success;
}

/*******************************************************************************
Function Name	: Select_Board_Configuration(void)
Parameters	: NONE
Returns	        : NONE
Notes           : Selects Board Setup
Default         : 1
*******************************************************************************/
void Select_Board_Configuration(unsigned char MuxSel)
{
  
  switch ( MuxSel) {  //pick a mode 
    case board_config_1A:
      PRINTF("\r\nConfigure 1A.\r\n");
      SYSTEM_SetupPowerConfig1A_PoweredWithDCDC();
    break;
    case board_config_1B:
      PRINTF("\r\nConfigure 1B.\r\n");
      SYSTEM_SetupPowerConfig1B_PoweredWithDCDC();
    break;    
    case board_config_1C: 
      PRINTF("\r\nConfigure 1C.\r\n");
      SYSTEM_SetupPowerConfig1C_PoweredWithDCDC();
    break;    
    case board_config_2A: 
      PRINTF("\r\nConfigure 2A.\r\n");
      SYSTEM_SetupPowerConfig2A_PoweredWithLDO();
    break;    
    case board_config_2B:
      PRINTF("\r\nConfigure 2B.\r\n");
      SYSTEM_SetupPowerConfig2B_PoweredWithLDO();
    break;      
    default:
      PRINTF("\r\nNo configuration selected!\r\n");
    break;
    }
}



void SYSTEM_SetupPowerConfig1A_PoweredWithDCDC(void)
{
    const spc_regulator_config_t config = {
        .coreldoEnable = false,
        .sysldoEnable = true,
        .dcdcEnable = true
    };
    if (SPC_SetRegulatorConfig(SPC0, &config) != kStatus_Success)
        PRINTF("Failed to configure system for power configuration 1A (powered with DCDC), please check!!!\n");
}

void SYSTEM_SetupPowerConfig1B_PoweredWithDCDC(void)
{
    const spc_regulator_config_t config = {
      .coreldoEnable = false,
      .sysldoEnable = false,
      .dcdcEnable = true
    };
    if (SPC_SetRegulatorConfig(SPC0, &config) != kStatus_Success)
    PRINTF("Failed to configure system for power configuration 1B (powered with DCDC, Bypass SYSLDO), please check!!!\n");
}

void SYSTEM_SetupPowerConfig1C_PoweredWithDCDC(void)
{
    const spc_regulator_config_t config = {
      .coreldoEnable = true,
      .sysldoEnable = false,
      .dcdcEnable = true
    };
    if (SPC_SetRegulatorConfig(SPC0, &config) != kStatus_Success)
    PRINTF("Failed to configure system for power configuration 1C (powered with DCDC, Bypass SYSLDO, CORELDO ENABLED), please check!!!\n");
}

void SYSTEM_SetupPowerConfig2A_PoweredWithLDO(void)
{
    const spc_regulator_config_t config = {
        .coreldoEnable = true,
        .sysldoEnable = true,
        .dcdcEnable = false
    };
    if (SPC_SetRegulatorConfig(SPC0, &config) != kStatus_Success)
        PRINTF("Failed to configure system for power configuration 2A (powered with LDO), please check!!!\n");
}
void SYSTEM_SetupPowerConfig2B_PoweredWithLDO(void)
{
    const spc_regulator_config_t config = {
        .coreldoEnable = true,
        .sysldoEnable = false,
        .dcdcEnable = false
    };
    if (SPC_SetRegulatorConfig(SPC0, &config) != kStatus_Success)
        PRINTF("Failed to configure system for power configuration 2B (powered with LDO), please check!!!\n");
}

/*******************************************************************************
Function Name	: read_registers(void)
Parameters	: NONE
Returns	        : NONE
Notes           : configures SysOSC (for uart), prints important regsisters, configures SysoSC back per test case
Example         : read_registers();
*******************************************************************************/
void read_registers(idd_config_t * idd_param)
{   
  PRINTF("Read registers:\n\r");
  PRINTF("CMC CKCTRL                  :0x%x\n\r", CMC0->CKCTRL);
  PRINTF("CMC PMPROT                  :0x%x\n\r", CMC0->PMPROT);
  PRINTF("CMC GPMCTRL                 :0x%x\n\r", CMC0->GPMCTRL);
  PRINTF("CMC PMCTRLMAIN              :0x%x\n\r", CMC0->PMCTRL[0]);
  PRINTF("CMC PMCTRLWAKE              :0x%x\n\r", CMC0->PMCTRL[1]);
  PRINTF("CMC SRAMDIS0                :0x%x\n\r", CMC_SRAMDIS);
  PRINTF("CMC SRAMRET0                :0x%x\n\r", CMC0->SRAMRET[0]);
  PRINTF("CMC FLASHCR                 :0x%x\n\r", CMC0->FLASHCR);
  PRINTF("CMC DBGCTL                  :0x%x\n\r", CMC0->DBGCTL);
  
  PRINTF("SCG RCCR                    :0x%x\n\r", SCG0->RCCR);
  PRINTF("SCG SOSCCSR                 :0x%x\n\r", SCG0->SOSCCSR);
  PRINTF("SCG_SOSCCFG                 :0x%x\n\r", SCG0->SOSCCFG);
  PRINTF("SCG SIRCCSR                 :0x%x\n\r", SCG0->SIRCCSR);
  PRINTF("SCG FIRCCSR                 :0x%x\n\r", SCG0->FIRCCSR);
  PRINTF("SCG FIRCCFG                 :0x%x\n\r", SCG0->FIRCCFG);
  PRINTF("SCG LDOCSR                  :0x%x\n\r", SCG0->LDOCSR);
  PRINTF("SCG APLLCSR                 :0x%x\n\r", SCG0->APLLCSR);
  PRINTF("SCG APLLCTRL                :0x%x\n\r", SCG0->APLLCTRL);

  PRINTF("SYSCON LPCAC_CTRL           :0x%x\n\r", SYSCON->LPCAC_CTRL);

  if(idd_param->sysconAHBClkCtrlx == 0)
  {
      /* Need to clear Port1 for UART4, bit 14: PORT1*/
      SYSCON_AHBCLKCTRL0 = SYSCON->AHBCLKCTRL0 & (~(1<<14));
      /* bit 15: FC4, bit 6: RTC */
      SYSCON_AHBCLKCTRL1 = SYSCON->AHBCLKCTRL1 & (~(1<<15)) & (~(1<<6));
      /* Bit 26: SCG */
      SYSCON_AHBCLKCTRL2 = SYSCON->AHBCLKCTRL2 & (~(1<<26));
      SYSCON_AHBCLKCTRL3 = SYSCON->AHBCLKCTRL3;
      
      PRINTF("SYSCON AHBCLKCTRL0          :0x%x\n\r", SYSCON_AHBCLKCTRL0);
      PRINTF("SYSCON AHBCLKCTRL1          :0x%x\n\r", SYSCON_AHBCLKCTRL1);
      PRINTF("SYSCON AHBCLKCTRL2          :0x%x\n\r", SYSCON_AHBCLKCTRL2);
      PRINTF("SYSCON AHBCLKCTRL3          :0x%x\n\r", SYSCON_AHBCLKCTRL3); 
  }
  else if (idd_param->sysconAHBClkCtrlx == 1)
  {
      PRINTF("SYSCON AHBCLKCTRL0          :0x%x\n\r", SYSCON->AHBCLKCTRL0);
      PRINTF("SYSCON AHBCLKCTRL1          :0x%x\n\r", SYSCON->AHBCLKCTRL1);
      PRINTF("SYSCON AHBCLKCTRL2          :0x%x\n\r", SYSCON->AHBCLKCTRL2);
      PRINTF("SYSCON AHBCLKCTRL3          :0x%x\n\r", SYSCON->AHBCLKCTRL3);
  }
  
  PRINTF("SYSCON AUTOCLKGATEOVERRIDE  :0x%x\n\r", SYSCON->AUTOCLKGATEOVERRIDE);
  PRINTF("SYSCON ECC_ENABLE_CTRL      :0x%x\n\r", SYSCON->ECC_ENABLE_CTRL);
  
  PRINTF("SPC CNTRL                   :0x%x\n\r", SPC0->CNTRL);
  PRINTF("SPC LP_CFG                  :0x%x\n\r", SPC0->LP_CFG);
  PRINTF("SPC LP_CFG1                 :0x%x\n\r", SPC0->LP_CFG1);
  PRINTF("SPC ACTIVE_CFG              :0x%x\n\r", SPC0->ACTIVE_CFG);
  PRINTF("SPC ACTIVE_CFG1             :0x%x\n\r", SPC0->ACTIVE_CFG1);
  PRINTF("SPC DCDC_CFG                :0x%x\n\r", SPC0->DCDC_CFG);
  PRINTF("SPC EVD_CFG                 :0x%x\n\r", SPC0_EVD_CFG);
  PRINTF("SPC DCDC_BURST_CFG          :0x%x\n\r", SPC0->DCDC_BURST_CFG);  
 
  PRINTF("VBAT0 OSCCTLA               :0x%x\n\r", VBAT0->OSCCTLA);
  PRINTF("VBAT0 OSCCTLB               :0x%x\n\r", VBAT0->OSCCTLB);
  PRINTF("VBAT0 LDORAMC               :0x%x\n\r", VBAT_LDORAMC);
  PRINTF("VBAT0 LDOCTLA               :0x%x\n\r", VBAT0->LDOCTLA);
  PRINTF("VBAT0 FROCTLA               :0x%x\n\r", VBAT0->FROCTLA);
  PRINTF("VBAT0 FROCTLB               :0x%x\n\r", VBAT0->FROCTLB);
  PRINTF("VBAT0 TAMPERA               :0x%x\n\r", VBAT0->TAMPERA);
  PRINTF("VBAT0 TAMPERB               :0x%x\n\r", VBAT0->TAMPERB);
  PRINTF("VBAT0 TAMCTLA               :0x%x\n\r", VBAT0->TAMCTLA);
  PRINTF("VBAT0 TAMCTLB               :0x%x\n\r", VBAT0->TAMCTLB);
  PRINTF("VBAT0 FROCLKE               :0x%x\n\r", VBAT0->FROCLKE);
  PRINTF("VBAT0 OSCCLKE               :0x%x\n\r", VBAT0->OSCCLKE);

  PRINTF("RTC0 CTRL                   :0x%x\n\r", RTC0_CTRL);
  PRINTF("Read registers end.\n\r");
}