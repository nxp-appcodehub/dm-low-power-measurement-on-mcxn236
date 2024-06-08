/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

enum register_values
{
  CMC0_CKCTRL_reg,
  CMC0_CKSTAT_reg,
  CMC0_PMPROT_reg,
  CMC0_GPMCTRL_reg,
  CMC0_PMCTRL0_reg,
  CMC0_PMCTRL1_reg,
  CMC0_SRS_reg,
  CMC0_SRAMDIS_reg,
  CMC0_SRAMRET_reg,
  CMC0_FLASHCR_reg,
  CMC0_DBGCTL_reg,
  CMC0_TEST_reg,

  SPC0_SC_reg,
  SPC0_CNTRL_reg,
  SPC0_LP_CFG_reg,
  SPC0_LP_CFG1_reg,
  SPC0_ACTIVE_CFG_reg,
  SPC0_ACTIVE_CFG1_reg,
  SPC0_EVD_CFG_reg,
  SPC0_WAKEUP_reg,
  SPC0_TEST_reg,
  SPC0_CORELDO_CFG_reg,
  SPC0_SYSLDO_CFG_reg,
  SPC0_DCDC_CFG_reg,
  SPC0_DCDC_VTRIM_reg,
  SPC0_DCDC_LPVTRIM_reg,
  SPC0_DCDC_TEST_reg,

  SCG0_CSR_reg,
  SCG0_RCCR_reg,
  SCG0_FIRCCFG_reg,
  SCG0_FIRCCSR_reg,
  SCG0_FIRCSTAT_reg,
  SCG0_FIRCTCFG_reg,
  SCG0_FIRCTEST_reg,
  SCG0_FIRCTRIM_reg,
  SCG0_PARAM_reg,
  SCG0_ROSCCSR_reg,
  SCG0_SIRCCSR_reg,
  SCG0_SIRCTEST_reg,
  SCG0_SIRCTRIM_reg,
  SCG0_LDOCSR_reg,
  SCG0_APLLCSR_reg,
  SCG0_APLLCTRL_reg,
  SCG0_SPLLCSR_reg,
  SCG0_SPLLCTRL_reg,  
  SCG0_SOSCCSR_reg,
  SCG0_SOSCCFG_reg,
  SCG0_TRIM_LOCK_reg,
  SCG0_VERID_reg,

  VBAT0_FROCLKE_reg,
  VBAT0_OSCCLKE_reg,  
  VBAT0_FROCTLA_reg,
  VBAT0_FROCTLB_reg,
  VBAT0_FROCFGA_reg,
  VBAT0_FROCFGB_reg,
  VBAT0_OSCCTLA_reg,
  VBAT0_OSCCTLB_reg,
  VBAT0_OSCCFGA_reg,
  VBAT0_OSCCFGB_reg,
  VBAT0_LDOCTLA_reg,
  VBAT0_LDOCTLB_reg,
  VBAT0_LDORAMC_reg,
  VBAT0_TAMPERA_reg,
  VBAT0_TAMPERB_reg,
  VBAT0_TAMCTLA_reg,
  VBAT0_TAMCTLB_reg,
  VBAT0_SWICTLA_reg,
  VBAT0_SWICTLB_reg,
  VBAT0_STATUSA_reg,
  VBAT0_STATUSB_reg,

  SYSCON_LPCAC_CTRL_reg,  
  SYSCON_AHBCLKDIV_reg,
  SYSCON_AHBCLKCTRL0_reg,
  SYSCON_AHBCLKCTRL1_reg,
  SYSCON_AHBCLKCTRL2_reg,
  SYSCON_AHBCLKCTRL3_reg,
  SYSCON_AUTOCLKGATEOVERRIDE_reg,
  SYSCON_AUTOCLKGATEOVERRIDEC_reg,
  SYSCON_PERIPHENCFG0_reg,
  SYSCON_ECC_ENABLE_CTRL_reg,
  
  RTC0_CTRL_reg,
  RTC0_STATUS_reg,

  outputMAXSIZE
};

/*Register Definitions*/
#define GPIO_PIN_MASK            0x1Fu
#define GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))
#define CMC_PTR  CMC
#define SPC_PTR  SPC0
#define RTC_PTR  RTC0
#define WUU_PTR  WUU0
/*******************************************************************************
* Functions Delaration
******************************************************************************/
void low_power_mode_config(void);
void active_power_mode_config(void);
void spc_active_config(void);
void ConfigureClocks(void);
void DisablePeripheralsClock(void);
void EnablePeripheralsClock(void);
void DisablePeripheralsAutomaticClock(void);
void EnablePeripheralsAutomaticClock(void);
void RAMx_CG_OVERRIDE(void);
void RAMx_Execute_Per_Dis(void);
void RAMx_Execute_Per_DP_Dis(void);
void FIRC_PERIPH_EN(void);
void Peripherals_Clock_CFG(void);
void Peripherals_AutomaticClock_CFG(void);


uint32_t SramTranslate(int option);
void Core1_configure(void);
void TestMode_Enable();
//void LOWPOWER_CODE();
void cmc_low_power_config(void);
void spc_low_power_config(void);
void spc_config_lvd_hvd(void);
void rf_low_power_config(void);
void scg_low_power_clk_config(void);
void PowerWakeup_config(void);
void read_ADC(void);
void converted_output_registers(unsigned int bytes);
void converted_ADC_values(unsigned int bytes);
void EnableClkout(void);
void DisablePorts(void);
//void read_registers(void);
void Configure_DCDC(void);
void setup_LPREQwakeup_signal(void);
void setup_IRQwakeup_signal(void);
void config_core_dcdc_freq(int core_V, int dcdc_V, int dcdc_DS, int cpu_freq);
void SelectEVB(unsigned char MuxSel);
//void VBAT_Misc(void);
void POWER_Init(void);
void loadReg2Memory(void);
//void POWER_Configure(const power_config_t* config);
void POWER_Exit(void);
void POWER_ResetExit(void);
void Gpio5WakeupConfig(void);
void Gpio3WakeupConfig(void);
void WuuPinWakeupConfig(void);
void WUU_IRQHandler(void);
void GPIO30_IRQHandler(void);
void GPIO50_IRQHandler(void);
