/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_device_registers.h"

#include "pin_mux.h"
#include "board.h"

#include "fsl_clock.h"
#include "fsl_reset.h"
#include <stdbool.h>
#include <stdio.h>

#include "IDD.h"
#include "fsl_spc.h"
#include "fsl_cmc.h"

#include "idd_general_cfg.h"
//#include "coremark.h"
//#include "coremark_helper.h"
#include "fsl_debug_console.h"
#include "idd_mode_select.h"
   
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DCDC_EN
//#define LDO_EN_a      //LDO_3p3V
//#define LDO_EN_b      //LDO_1p8V

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
//extern void coremark_main(void);

/* Give the while(1) function a definite address */
void while1_func(void)@".while1_func"
{
    while(1)
    {
    }
}

/*******************************************************************************
 * Variables
 ******************************************************************************/
   
idd_config_t g_iddConfig;
extern uint32_t VBAT_LDORAMC;

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    unsigned int select_case = 0;
    
    /* FRO 12M */
    BOARD_InitBootClocks();     
   
    /* Init board hardware. */   
    SYSCON->FLEXCOMMCLKDIV[4] &= ~SYSCON_FLEXCOMMXCLKDIV_FLEXCOMMCLKDIV_HALT_MASK; // enable fc4 clock, div1
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK;
    SYSCON->AHBCLKCTRL1 |= SYSCON_AHBCLKCTRL1_RTC_MASK; 
       
    BOARD_InitPins();   
    BOARD_InitDebugConsole();    
    
    PRINTF("\n****************************************************************\n\r");       
    PRINTF("*          Starting low power measurement on mcxn236           *\n\r");
    PRINTF("****************************************************************\n\r");     
        
    PRINTF("\nSelect power mode: \n\r");           
    PRINTF("0.      Symbol_IDD_ACT_OD_1.\n\r");
    PRINTF("5.      Symbol_IDD_CM_OD_1.\n\r");
    PRINTF("61.     Symbol_IDD_SLEEP.\n\r");
    PRINTF("69.     Symbol_IDD_DSLEEP_LP.\n\r");
    PRINTF("86.     Symbol_IDD_PDOWN_LP.\n\r");
    PRINTF("103.    Symbol_IDD_PDOWN_RET_0V7.\n\r");
    PRINTF("109.    Symbol_IDD_DPOWN_32K.\n\r");
    PRINTF("*     Please input Number and end with carriage return.     *\n\r");
    SCANF("%d", &select_case);
    PRINTF("select_case = %d\n\r", select_case);    
    
    g_iddConfig.caseSelect = select_case;
    /* Configure the corresponding parameters according to the selected case */
    IDD_paramConfig(&g_iddConfig);
    
    /* Configure SoC power */
#if (defined(DCDC_EN))
    g_iddConfig.selectBoard = board_config_1A;
#elif (defined(LDO_EN_a))               //LDO_3p3V
    g_iddConfig.selectBoard = board_config_2A;
#elif (defined(LDO_EN_b))               //LDO_1p8V
    g_iddConfig.selectBoard = board_config_2B;
#endif    
    Select_Board_Configuration(g_iddConfig.selectBoard);
    
    /* Configure Power mode protection level and debug function */
    PowerMode_CFG_Prepare(&g_iddConfig);    
      
    if(g_iddConfig.lowPowerLevel == kPower_Mode_Dynamic_Active)
    {
        PRINTF("Active Mode Selected\n\r");
        /* configure Active mode SPC, SYSCON(RAM, LPCAC), Flash */
        Active_Mode_CFG(&g_iddConfig);
    }
    else
    {
        PRINTF("Low Power Mode Selected\n\r");
        /* configure Low Power mode CMC, SPC, CLK */
        LowPower_Mode_CFG(&g_iddConfig);
    }
    
    if(g_iddConfig.bleedEnable == 1)
    {
        SPC0->DCDC_CFG |= SPC_DCDC_CFG_BLEED_EN_MASK;   
    }
    
    /* Clock related configuration */
    CLK_config(&g_iddConfig);
    
    /* VBAT related configuration */
    VBAT_Misc(&g_iddConfig);     
    
    if(g_iddConfig.lowPowerLevel == 0)    
    {        
        /* Clear ACTIVE_CFG1 and LP_CFG1 */
        SPC0->LP_CFG1     &= ~(SPC_LP_CFG1_SOC_CNTRL_MASK);
        SPC0->ACTIVE_CFG1 &= ~(SPC_ACTIVE_CFG1_SOC_CNTRL_MASK);
                      
        /* Disable misc peripheral clock */
        DisableMiscPeripherals();
        //VBAT0->LDORAMC |= g_iddConfig.vBatLDORamSwiIso;

        /* Read Registers, for low power cases*/
        read_registers(&g_iddConfig);
        
        /* Disable PORT1, FC4, SCG, RTC */
        /* clear Port1 for UART4, bit 14: PORT1*/
        SYSCON->AHBCLKCTRLCLR[0] |=  (1<<14);
        
        /* bit 15: FC4, bit 6: RTC */
        SYSCON->AHBCLKCTRLCLR[1] |= (1<<15) | (1<<6);

        /* Bit 26: SCG */
        SYSCON->AHBCLKCTRLCLR[2] |= (1<<26);
        
        LowPower_Entry(&g_iddConfig);  
    } 

    if(g_iddConfig.sysconAHBClkCtrlx == 0)
    {
        /* Disable misc periipheral clock */
        DisableMiscPeripherals();
    }
    else if (g_iddConfig.sysconAHBClkCtrlx == 1)
    { 
        /* Enable misc periipheral clock */
        EnableMiscPeripherals(); 
    }

    /* Read Registers, for active cases */
    read_registers(&g_iddConfig);
    
    if(g_iddConfig.sysconAHBClkCtrlx == 0)
    {
        /* Disable PORT1, FC4, SCG, RTC */
        /* clear Port1 for UART4, bit 14: PORT1*/
        SYSCON->AHBCLKCTRLCLR[0] |=  (1<<14);
        
        /* bit 15: FC4, bit 6: RTC */
        SYSCON->AHBCLKCTRLCLR[1] |= (1<<15) | (1<<6);

        /* Bit 26: SCG */
        SYSCON->AHBCLKCTRLCLR[2] |= (1<<26);
    }
    
    /* while(1) */
    if(g_iddConfig.coreTask == kIDD_While1 || g_iddConfig.coreTask == kIDD_While1_All_Peripherals || g_iddConfig.coreTask == kIDD_While1_OR_CoreMark)
    {
        while1_func(); 
    }
    /* CoreMark */
    else if(g_iddConfig.coreTask == kIDD_CoreMark || g_iddConfig.coreTask == kIDD_CoreMark_All_Peripherals)
    {
        while(1)
        {
        /* Call coremark_main here */
//            coremark_main();
        }
    }
}
