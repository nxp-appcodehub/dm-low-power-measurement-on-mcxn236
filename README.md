# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## low power measurement on mcxn236
The low power measurement demo is used to reproduce the power consumption and wake-up time in the datasheet on the FRDM-MCXN236 board.

#### Boards: FRDM-MCXN236
#### Categories: Low Power
#### Peripherals: CLOCKS, UART
#### Toolchains: IAR

## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>
- [IAR 9.50.1](https://www.iar.com/)
- [SDK_2.14.0_FRDM-MCXN236](https://mcuxpresso.nxp.com/en/welcome)

## 2. Hardware<a name="step2"></a>
- FRDM-MCXN236 Rev C board.

- One Type-C USB cable.

> If you want to measure wake-up time, prepare an oscilloscope or logic analyzer.

> If you want to measure power consumption, prepare an [MCU-Link Pro](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcu-link-pro-debug-probe:MCU-LINK-PRO) or multimeter.

## 3. Setup<a name="step3"></a>

### 3.1 Hardware setup and connection
- Remove R71, solder header at JP2 and use jumper to connect.
- Use a Type-C USB cable to connect J10 of FRDM-MCXN236 and the USB port of the PC.

### 3.2 Configure and Download Project
- The default configuration for this project is WAKEUP_EN=0, which is used to reproduce the power consumption data in the datasheet. If you want to reproduce the wake-up time in the datasheet, need to update it to WAKEUP_EN=1.

![WAKEUP_EN_Configure](image/WAKEUP_EN_Configure.png)

- Make and Download the project to FRDM-MCXN236, then reset the MCU. 

![Make_Download_IAR](image/Make_Download_IAR.png)

### 3.3 Select power mode
- Open a serial terminal with 57600 baud rate.
- Follow the prompts and input number to enter different power mode.

![Select_Power_Mode](image/Select_Power_Mode.png)

- After inputting the case number, the symbol and registers value will be printed.

![Symbol_Registers](image/Symbol_Registers.png)

### 3.4 Measure power consumption
- Use an multimeter to measure the current at JP2 of the FRDM-MCXN236 board.

![Multimeter_current_measurement](image/Multimeter_current_measurement.png)

- Use MCU-Link Pro and MCUXpresso IDE to measure power consumption:
  - Configure the MCU-Link Pro current measurement range from 350mA to 50mA by changing the 3 jumpers J16/J17/J18 to short pins 2-3.
  - Connect MCU-Link Pro board to FRDM-MCXN236 board.

  |MCU-Link Pro|FRDM-MCXN236|
  |--|--|
  |J9-1|JP2-2|
  |J9-3|JP2-1|
  |J9-2|J3-14|

  - Follow below steps to measure current with MCUXpresso IDE.

![MCUXpresso_energy_measurement](image/MCUXpresso_energy_measurement.png)

### 3.5 Measure wake-up time
- Get the wake-up time by measuring the delay between the falling edges of J8-13 (P0_20) and J8-28 (P3_11) using an oscilloscope.
  - You need to press SW2(WAKEUP button) to wake up the MCU. 

![measure_wake_up_time](image/measure_wake_up_time.png)


## 4. Results<a name="step4"></a>
The following power consumption and wake-up time are provided as a reference:

> Different samples, temperature and measuring instrument etc. will affect test results.

> Before measuring each data, POR is required.

> If you want to measure power consumption of IDD_CM_OD_1, please porting **CoreMark** to     this project.

> The wake-up time of Deep Power Down needs to be configured as 144MHz boot, and all other measurement data uses the default 48MHz boot.

> If you want to measure the wake-up time of other configurations, please refer to table 228.         LPWKUP_DELAY configuration in Reference Manual to configure LPWKUP_DELAY.

> “Table 18. Power mode transition operating behaviors” in datasheet lists wake-up time, “3.2.6   Power consumption operating behaviors” in datasheet lists different power consumption data.

|Symbol|Power consumption in datasheet|Tested Power consumption|Wake-up time in datasheet|Tested wake-up time|
|--|--|--|--|--|
|IDD_ACT_OD_1|7.43mA|7.68mA|N/A|N/A|
|IDD_CM_OD_1|8.93mA|8.76mA|N/A|N/A|
|IDD_SLEEP|1.48mA|1.45mA|0.22us|0.22us|
|IDD_DSLEEP_LP|0.12mA|0.12mA|8.7us|8.6us|
|IDD_PDOWN_LP|1.75uA|1.95uA|9.8us|9.7us|
|IDD_PDOWN_RET_0V7|2.52uA|2.89uA|N/A|N/A|
|IDD_DPOWN_32K|1.28uA|1.55uA|5.6ms|5.6ms|


## 5. FAQs<a name="step5"></a>
*Include FAQs here if appropriate. If there are none, then state "No FAQs have been identified for this project".*

## 6. Support<a name="step6"></a>
*Provide URLs for help here.*

#### Project Metadata
<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN236-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN236+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-LOW%20POWER-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+low_power+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-CLOCKS-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+clocks+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-UART-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+uart+in%3Areadme&type=Repositories)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-IAR-orange)](https://github.com/search?q=org%3Anxp-appcodehub+iar+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code Hub        | May 21<sup>th</sup> 2024 |

