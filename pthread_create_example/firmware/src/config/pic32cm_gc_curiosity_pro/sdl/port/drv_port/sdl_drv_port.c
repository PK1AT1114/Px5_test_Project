/*******************************************************************************
  Software diagnostic library project

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_drv_port.c

  Summary:
    Source file for port diagnostic routines.

  Description:
    This file provides diagnostic functions used by PORT peripheral diagnostics.

 *******************************************************************************/

/*******************************************************************************
 * Copyright (C) 2026 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/

/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "sdl_drv_port.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/
#define SDL_PORT_GROUP_OFFSET  0x80U
#define SDL_PIN_TO_BIT(pin)      ((uint32_t)((pin) & 0x1FU))
#define SDL_PIN_TO_MASK(pin)     (1UL << SDL_PIN_TO_BIT(pin))

/* ============================================================
 *  PORT A MASK
 * ============================================================ */
/* Individual Pin Evaluations - Helpers removed and logic expanded inline */
#ifdef PIN_PA00
    #define SDL_PA00_MSK (1UL << ((PIN_PA00) & 0x1FU))
#else
    #define SDL_PA00_MSK 0U
#endif

#ifdef PIN_PA01
    #define SDL_PA01_MSK (1UL << ((PIN_PA01) & 0x1FU))
#else
    #define SDL_PA01_MSK 0U
#endif

#ifdef PIN_PA02
    #define SDL_PA02_MSK (1UL << ((PIN_PA02) & 0x1FU))
#else
    #define SDL_PA02_MSK 0U
#endif

#ifdef PIN_PA03
    #define SDL_PA03_MSK (1UL << ((PIN_PA03) & 0x1FU))
#else
    #define SDL_PA03_MSK 0U
#endif

#ifdef PIN_PA04
    #define SDL_PA04_MSK (1UL << ((PIN_PA04) & 0x1FU))
#else
    #define SDL_PA04_MSK 0U
#endif

#ifdef PIN_PA05
    #define SDL_PA05_MSK (1UL << ((PIN_PA05) & 0x1FU))
#else
    #define SDL_PA05_MSK 0U
#endif

#ifdef PIN_PA06
    #define SDL_PA06_MSK (1UL << ((PIN_PA06) & 0x1FU))
#else
    #define SDL_PA06_MSK 0U
#endif

#ifdef PIN_PA07
    #define SDL_PA07_MSK (1UL << ((PIN_PA07) & 0x1FU))
#else
    #define SDL_PA07_MSK 0U
#endif

#ifdef PIN_PA08
    #define SDL_PA08_MSK (1UL << ((PIN_PA08) & 0x1FU))
#else
    #define SDL_PA08_MSK 0U
#endif

#ifdef PIN_PA09
    #define SDL_PA09_MSK (1UL << ((PIN_PA09) & 0x1FU))
#else
    #define SDL_PA09_MSK 0U
#endif

#ifdef PIN_PA10
    #define SDL_PA10_MSK (1UL << ((PIN_PA10) & 0x1FU))
#else
    #define SDL_PA10_MSK 0U
#endif

#ifdef PIN_PA11
    #define SDL_PA11_MSK (1UL << ((PIN_PA11) & 0x1FU))
#else
    #define SDL_PA11_MSK 0U
#endif

#ifdef PIN_PA12
    #define SDL_PA12_MSK (1UL << ((PIN_PA12) & 0x1FU))
#else
    #define SDL_PA12_MSK 0U
#endif

#ifdef PIN_PA13
    #define SDL_PA13_MSK (1UL << ((PIN_PA13) & 0x1FU))
#else
    #define SDL_PA13_MSK 0U
#endif

#ifdef PIN_PA14
    #define SDL_PA14_MSK (1UL << ((PIN_PA14) & 0x1FU))
#else
    #define SDL_PA14_MSK 0U
#endif

#ifdef PIN_PA15
    #define SDL_PA15_MSK (1UL << ((PIN_PA15) & 0x1FU))
#else
    #define SDL_PA15_MSK 0U
#endif

#ifdef PIN_PA16
    #define SDL_PA16_MSK (1UL << ((PIN_PA16) & 0x1FU))
#else
    #define SDL_PA16_MSK 0U
#endif

#ifdef PIN_PA17
    #define SDL_PA17_MSK (1UL << ((PIN_PA17) & 0x1FU))
#else
    #define SDL_PA17_MSK 0U
#endif

#ifdef PIN_PA18
    #define SDL_PA18_MSK (1UL << ((PIN_PA18) & 0x1FU))
#else
    #define SDL_PA18_MSK 0U
#endif

#ifdef PIN_PA19
    #define SDL_PA19_MSK (1UL << ((PIN_PA19) & 0x1FU))
#else
    #define SDL_PA19_MSK 0U
#endif

#ifdef PIN_PA20
    #define SDL_PA20_MSK (1UL << ((PIN_PA20) & 0x1FU))
#else
    #define SDL_PA20_MSK 0U
#endif

#ifdef PIN_PA21
    #define SDL_PA21_MSK (1UL << ((PIN_PA21) & 0x1FU))
#else
    #define SDL_PA21_MSK 0U
#endif

#ifdef PIN_PA22
    #define SDL_PA22_MSK (1UL << ((PIN_PA22) & 0x1FU))
#else
    #define SDL_PA22_MSK 0U
#endif

#ifdef PIN_PA23
    #define SDL_PA23_MSK (1UL << ((PIN_PA23) & 0x1FU))
#else
    #define SDL_PA23_MSK 0U
#endif

#ifdef PIN_PA24
    #define SDL_PA24_MSK (1UL << ((PIN_PA24) & 0x1FU))
#else
    #define SDL_PA24_MSK 0U
#endif

#ifdef PIN_PA25
    #define SDL_PA25_MSK (1UL << ((PIN_PA25) & 0x1FU))
#else
    #define SDL_PA25_MSK 0U
#endif

#ifdef PIN_PA26
    #define SDL_PA26_MSK (1UL << ((PIN_PA26) & 0x1FU))
#else
    #define SDL_PA26_MSK 0U
#endif

#ifdef PIN_PA27
    #define SDL_PA27_MSK (1UL << ((PIN_PA27) & 0x1FU))
#else
    #define SDL_PA27_MSK 0U
#endif

#ifdef PIN_PA28
    #define SDL_PA28_MSK (1UL << ((PIN_PA28) & 0x1FU))
#else
    #define SDL_PA28_MSK 0U
#endif

#ifdef PIN_PA29
    #define SDL_PA29_MSK (1UL << ((PIN_PA29) & 0x1FU))
#else
    #define SDL_PA29_MSK 0U
#endif

#ifdef PIN_PA30
    #define SDL_PA30_MSK (1UL << ((PIN_PA30) & 0x1FU))
#else
    #define SDL_PA30_MSK 0U
#endif

#ifdef PIN_PA31
    #define SDL_PA31_MSK (1UL << ((PIN_PA31) & 0x1FU))
#else
    #define SDL_PA31_MSK 0U
#endif

/* Final Macro Definition remains the same */

/* ============================================================
 *  PORT B MASK
 * ============================================================ */
#ifdef PIN_PB00
    #define SDL_PB00_MSK (1UL << ((PIN_PB00) & 0x1FU))
#else
    #define SDL_PB00_MSK 0U
#endif

#ifdef PIN_PB01
    #define SDL_PB01_MSK (1UL << ((PIN_PB01) & 0x1FU))
#else
    #define SDL_PB01_MSK 0U
#endif

#ifdef PIN_PB02
    #define SDL_PB02_MSK (1UL << ((PIN_PB02) & 0x1FU))
#else
    #define SDL_PB02_MSK 0U
#endif

#ifdef PIN_PB03
    #define SDL_PB03_MSK (1UL << ((PIN_PB03) & 0x1FU))
#else
    #define SDL_PB03_MSK 0U
#endif

#ifdef PIN_PB04
    #define SDL_PB04_MSK (1UL << ((PIN_PB04) & 0x1FU))
#else
    #define SDL_PB04_MSK 0U
#endif

#ifdef PIN_PB05
    #define SDL_PB05_MSK (1UL << ((PIN_PB05) & 0x1FU))
#else
    #define SDL_PB05_MSK 0U
#endif

#ifdef PIN_PB06
    #define SDL_PB06_MSK (1UL << ((PIN_PB06) & 0x1FU))
#else
    #define SDL_PB06_MSK 0U
#endif

#ifdef PIN_PB07
    #define SDL_PB07_MSK (1UL << ((PIN_PB07) & 0x1FU))
#else
    #define SDL_PB07_MSK 0U
#endif

#ifdef PIN_PB08
    #define SDL_PB08_MSK (1UL << ((PIN_PB08) & 0x1FU))
#else
    #define SDL_PB08_MSK 0U
#endif

#ifdef PIN_PB09
    #define SDL_PB09_MSK (1UL << ((PIN_PB09) & 0x1FU))
#else
    #define SDL_PB09_MSK 0U
#endif

#ifdef PIN_PB10
    #define SDL_PB10_MSK (1UL << ((PIN_PB10) & 0x1FU))
#else
    #define SDL_PB10_MSK 0U
#endif

#ifdef PIN_PB11
    #define SDL_PB11_MSK (1UL << ((PIN_PB11) & 0x1FU))
#else
    #define SDL_PB11_MSK 0U
#endif

#ifdef PIN_PB12
    #define SDL_PB12_MSK (1UL << ((PIN_PB12) & 0x1FU))
#else
    #define SDL_PB12_MSK 0U
#endif

#ifdef PIN_PB13
    #define SDL_PB13_MSK (1UL << ((PIN_PB13) & 0x1FU))
#else
    #define SDL_PB13_MSK 0U
#endif

#ifdef PIN_PB14
    #define SDL_PB14_MSK (1UL << ((PIN_PB14) & 0x1FU))
#else
    #define SDL_PB14_MSK 0U
#endif

#ifdef PIN_PB15
    #define SDL_PB15_MSK (1UL << ((PIN_PB15) & 0x1FU))
#else
    #define SDL_PB15_MSK 0U
#endif

#ifdef PIN_PB16
    #define SDL_PB16_MSK (1UL << ((PIN_PB16) & 0x1FU))
#else
    #define SDL_PB16_MSK 0U
#endif

#ifdef PIN_PB17
    #define SDL_PB17_MSK (1UL << ((PIN_PB17) & 0x1FU))
#else
    #define SDL_PB17_MSK 0U
#endif

#ifdef PIN_PB18
    #define SDL_PB18_MSK (1UL << ((PIN_PB18) & 0x1FU))
#else
    #define SDL_PB18_MSK 0U
#endif

#ifdef PIN_PB19
    #define SDL_PB19_MSK (1UL << ((PIN_PB19) & 0x1FU))
#else
    #define SDL_PB19_MSK 0U
#endif

#ifdef PIN_PB20
    #define SDL_PB20_MSK (1UL << ((PIN_PB20) & 0x1FU))
#else
    #define SDL_PB20_MSK 0U
#endif

#ifdef PIN_PB21
    #define SDL_PB21_MSK (1UL << ((PIN_PB21) & 0x1FU))
#else
    #define SDL_PB21_MSK 0U
#endif

#ifdef PIN_PB22
    #define SDL_PB22_MSK (1UL << ((PIN_PB22) & 0x1FU))
#else
    #define SDL_PB22_MSK 0U
#endif

#ifdef PIN_PB23
    #define SDL_PB23_MSK (1UL << ((PIN_PB23) & 0x1FU))
#else
    #define SDL_PB23_MSK 0U
#endif

#ifdef PIN_PB24
    #define SDL_PB24_MSK (1UL << ((PIN_PB24) & 0x1FU))
#else
    #define SDL_PB24_MSK 0U
#endif

#ifdef PIN_PB25
    #define SDL_PB25_MSK (1UL << ((PIN_PB25) & 0x1FU))
#else
    #define SDL_PB25_MSK 0U
#endif

#ifdef PIN_PB26
    #define SDL_PB26_MSK (1UL << ((PIN_PB26) & 0x1FU))
#else
    #define SDL_PB26_MSK 0U
#endif

#ifdef PIN_PB27
    #define SDL_PB27_MSK (1UL << ((PIN_PB27) & 0x1FU))
#else
    #define SDL_PB27_MSK 0U
#endif

#ifdef PIN_PB28
    #define SDL_PB28_MSK (1UL << ((PIN_PB28) & 0x1FU))
#else
    #define SDL_PB28_MSK 0U
#endif

#ifdef PIN_PB29
    #define SDL_PB29_MSK (1UL << ((PIN_PB29) & 0x1FU))
#else
    #define SDL_PB29_MSK 0U
#endif

#ifdef PIN_PB30
    #define SDL_PB30_MSK (1UL << ((PIN_PB30) & 0x1FU))
#else
    #define SDL_PB30_MSK 0U
#endif

#ifdef PIN_PB31
    #define SDL_PB31_MSK (1UL << ((PIN_PB31) & 0x1FU))
#else
    #define SDL_PB31_MSK 0U
#endif

/* ============================================================
 *  PORT C MASK
 * ============================================================ */
#ifdef PIN_PC00
    #define SDL_PC00_MSK (1UL << ((PIN_PC00) & 0x1FU))
#else
    #define SDL_PC00_MSK 0U
#endif

#ifdef PIN_PC01
    #define SDL_PC01_MSK (1UL << ((PIN_PC01) & 0x1FU))
#else
    #define SDL_PC01_MSK 0U
#endif

#ifdef PIN_PC02
    #define SDL_PC02_MSK (1UL << ((PIN_PC02) & 0x1FU))
#else
    #define SDL_PC02_MSK 0U
#endif

#ifdef PIN_PC03
    #define SDL_PC03_MSK (1UL << ((PIN_PC03) & 0x1FU))
#else
    #define SDL_PC03_MSK 0U
#endif

#ifdef PIN_PC04
    #define SDL_PC04_MSK (1UL << ((PIN_PC04) & 0x1FU))
#else
    #define SDL_PC04_MSK 0U
#endif

#ifdef PIN_PC05
    #define SDL_PC05_MSK (1UL << ((PIN_PC05) & 0x1FU))
#else
    #define SDL_PC05_MSK 0U
#endif

#ifdef PIN_PC06
    #define SDL_PC06_MSK (1UL << ((PIN_PC06) & 0x1FU))
#else
    #define SDL_PC06_MSK 0U
#endif

#ifdef PIN_PC07
    #define SDL_PC07_MSK (1UL << ((PIN_PC07) & 0x1FU))
#else
    #define SDL_PC07_MSK 0U
#endif

#ifdef PIN_PC08
    #define SDL_PC08_MSK (1UL << ((PIN_PC08) & 0x1FU))
#else
    #define SDL_PC08_MSK 0U
#endif

#ifdef PIN_PC09
    #define SDL_PC09_MSK (1UL << ((PIN_PC09) & 0x1FU))
#else
    #define SDL_PC09_MSK 0U
#endif

#ifdef PIN_PC10
    #define SDL_PC10_MSK (1UL << ((PIN_PC10) & 0x1FU))
#else
    #define SDL_PC10_MSK 0U
#endif

#ifdef PIN_PC11
    #define SDL_PC11_MSK (1UL << ((PIN_PC11) & 0x1FU))
#else
    #define SDL_PC11_MSK 0U
#endif

#ifdef PIN_PC12
    #define SDL_PC12_MSK (1UL << ((PIN_PC12) & 0x1FU))
#else
    #define SDL_PC12_MSK 0U
#endif

#ifdef PIN_PC13
    #define SDL_PC13_MSK (1UL << ((PIN_PC13) & 0x1FU))
#else
    #define SDL_PC13_MSK 0U
#endif

#ifdef PIN_PC14
    #define SDL_PC14_MSK (1UL << ((PIN_PC14) & 0x1FU))
#else
    #define SDL_PC14_MSK 0U
#endif

#ifdef PIN_PC15
    #define SDL_PC15_MSK (1UL << ((PIN_PC15) & 0x1FU))
#else
    #define SDL_PC15_MSK 0U
#endif

#ifdef PIN_PC16
    #define SDL_PC16_MSK (1UL << ((PIN_PC16) & 0x1FU))
#else
    #define SDL_PC16_MSK 0U
#endif

#ifdef PIN_PC17
    #define SDL_PC17_MSK (1UL << ((PIN_PC17) & 0x1FU))
#else
    #define SDL_PC17_MSK 0U
#endif

#ifdef PIN_PC18
    #define SDL_PC18_MSK (1UL << ((PIN_PC18) & 0x1FU))
#else
    #define SDL_PC18_MSK 0U
#endif

#ifdef PIN_PC19
    #define SDL_PC19_MSK (1UL << ((PIN_PC19) & 0x1FU))
#else
    #define SDL_PC19_MSK 0U
#endif

#ifdef PIN_PC20
    #define SDL_PC20_MSK (1UL << ((PIN_PC20) & 0x1FU))
#else
    #define SDL_PC20_MSK 0U
#endif

#ifdef PIN_PC21
    #define SDL_PC21_MSK (1UL << ((PIN_PC21) & 0x1FU))
#else
    #define SDL_PC21_MSK 0U
#endif

#ifdef PIN_PC22
    #define SDL_PC22_MSK (1UL << ((PIN_PC22) & 0x1FU))
#else
    #define SDL_PC22_MSK 0U
#endif

#ifdef PIN_PC23
    #define SDL_PC23_MSK (1UL << ((PIN_PC23) & 0x1FU))
#else
    #define SDL_PC23_MSK 0U
#endif

#ifdef PIN_PC24
    #define SDL_PC24_MSK (1UL << ((PIN_PC24) & 0x1FU))
#else
    #define SDL_PC24_MSK 0U
#endif

#ifdef PIN_PC25
    #define SDL_PC25_MSK (1UL << ((PIN_PC25) & 0x1FU))
#else
    #define SDL_PC25_MSK 0U
#endif

#ifdef PIN_PC26
    #define SDL_PC26_MSK (1UL << ((PIN_PC26) & 0x1FU))
#else
    #define SDL_PC26_MSK 0U
#endif

#ifdef PIN_PC27
    #define SDL_PC27_MSK (1UL << ((PIN_PC27) & 0x1FU))
#else
    #define SDL_PC27_MSK 0U
#endif

#ifdef PIN_PC28
    #define SDL_PC28_MSK (1UL << ((PIN_PC28) & 0x1FU))
#else
    #define SDL_PC28_MSK 0U
#endif

#ifdef PIN_PC29
    #define SDL_PC29_MSK (1UL << ((PIN_PC29) & 0x1FU))
#else
    #define SDL_PC29_MSK 0U
#endif

#ifdef PIN_PC30
    #define SDL_PC30_MSK (1UL << ((PIN_PC30) & 0x1FU))
#else
    #define SDL_PC30_MSK 0U
#endif

#ifdef PIN_PC31
    #define SDL_PC31_MSK (1UL << ((PIN_PC31) & 0x1FU))
#else
    #define SDL_PC31_MSK 0U
#endif


/* ============================================================
 *  PORT D MASK
 * ============================================================ */

#ifdef PIN_PD00
    #define SDL_PD00_MSK (1UL << ((PIN_PD00) & 0x1FU))
#else
    #define SDL_PD00_MSK 0U
#endif

#ifdef PIN_PD01
    #define SDL_PD01_MSK (1UL << ((PIN_PD01) & 0x1FU))
#else
    #define SDL_PD01_MSK 0U
#endif

#ifdef PIN_PD02
    #define SDL_PD02_MSK (1UL << ((PIN_PD02) & 0x1FU))
#else
    #define SDL_PD02_MSK 0U
#endif

#ifdef PIN_PD03
    #define SDL_PD03_MSK (1UL << ((PIN_PD03) & 0x1FU))
#else
    #define SDL_PD03_MSK 0U
#endif

#ifdef PIN_PD04
    #define SDL_PD04_MSK (1UL << ((PIN_PD04) & 0x1FU))
#else
    #define SDL_PD04_MSK 0U
#endif

#ifdef PIN_PD05
    #define SDL_PD05_MSK (1UL << ((PIN_PD05) & 0x1FU))
#else
    #define SDL_PD05_MSK 0U
#endif

#ifdef PIN_PD06
    #define SDL_PD06_MSK (1UL << ((PIN_PD06) & 0x1FU))
#else
    #define SDL_PD06_MSK 0U
#endif

#ifdef PIN_PD07
    #define SDL_PD07_MSK (1UL << ((PIN_PD07) & 0x1FU))
#else
    #define SDL_PD07_MSK 0U
#endif

#ifdef PIN_PD08
    #define SDL_PD08_MSK (1UL << ((PIN_PD08) & 0x1FU))
#else
    #define SDL_PD08_MSK 0U
#endif

#ifdef PIN_PD09
    #define SDL_PD09_MSK (1UL << ((PIN_PD09) & 0x1FU))
#else
    #define SDL_PD09_MSK 0U
#endif

#ifdef PIN_PD10
    #define SDL_PD10_MSK (1UL << ((PIN_PD10) & 0x1FU))
#else
    #define SDL_PD10_MSK 0U
#endif

#ifdef PIN_PD11
    #define SDL_PD11_MSK (1UL << ((PIN_PD11) & 0x1FU))
#else
    #define SDL_PD11_MSK 0U
#endif

#ifdef PIN_PD12
    #define SDL_PD12_MSK (1UL << ((PIN_PD12) & 0x1FU))
#else
    #define SDL_PD12_MSK 0U
#endif

#ifdef PIN_PD13
    #define SDL_PD13_MSK (1UL << ((PIN_PD13) & 0x1FU))
#else
    #define SDL_PD13_MSK 0U
#endif

#ifdef PIN_PD14
    #define SDL_PD14_MSK (1UL << ((PIN_PD14) & 0x1FU))
#else
    #define SDL_PD14_MSK 0U
#endif

#ifdef PIN_PD15
    #define SDL_PD15_MSK (1UL << ((PIN_PD15) & 0x1FU))
#else
    #define SDL_PD15_MSK 0U
#endif

#ifdef PIN_PD16
    #define SDL_PD16_MSK (1UL << ((PIN_PD16) & 0x1FU))
#else
    #define SDL_PD16_MSK 0U
#endif

#ifdef PIN_PD17
    #define SDL_PD17_MSK (1UL << ((PIN_PD17) & 0x1FU))
#else
    #define SDL_PD17_MSK 0U
#endif

#ifdef PIN_PD18
    #define SDL_PD18_MSK (1UL << ((PIN_PD18) & 0x1FU))
#else
    #define SDL_PD18_MSK 0U
#endif

#ifdef PIN_PD19
    #define SDL_PD19_MSK (1UL << ((PIN_PD19) & 0x1FU))
#else
    #define SDL_PD19_MSK 0U
#endif

#ifdef PIN_PD20
    #define SDL_PD20_MSK (1UL << ((PIN_PD20) & 0x1FU))
#else
    #define SDL_PD20_MSK 0U
#endif

#ifdef PIN_PD21
    #define SDL_PD21_MSK (1UL << ((PIN_PD21) & 0x1FU))
#else
    #define SDL_PD21_MSK 0U
#endif

#ifdef PIN_PD22
    #define SDL_PD22_MSK (1UL << ((PIN_PD22) & 0x1FU))
#else
    #define SDL_PD22_MSK 0U
#endif

#ifdef PIN_PD23
    #define SDL_PD23_MSK (1UL << ((PIN_PD23) & 0x1FU))
#else
    #define SDL_PD23_MSK 0U
#endif

#ifdef PIN_PD24
    #define SDL_PD24_MSK (1UL << ((PIN_PD24) & 0x1FU))
#else
    #define SDL_PD24_MSK 0U
#endif

#ifdef PIN_PD25
    #define SDL_PD25_MSK (1UL << ((PIN_PD25) & 0x1FU))
#else
    #define SDL_PD25_MSK 0U
#endif

#ifdef PIN_PD26
    #define SDL_PD26_MSK (1UL << ((PIN_PD26) & 0x1FU))
#else
    #define SDL_PD26_MSK 0U
#endif

#ifdef PIN_PD27
    #define SDL_PD27_MSK (1UL << ((PIN_PD27) & 0x1FU))
#else
    #define SDL_PD27_MSK 0U
#endif

#ifdef PIN_PD28
    #define SDL_PD28_MSK (1UL << ((PIN_PD28) & 0x1FU))
#else
    #define SDL_PD28_MSK 0U
#endif

#ifdef PIN_PD29
    #define SDL_PD29_MSK (1UL << ((PIN_PD29) & 0x1FU))
#else
    #define SDL_PD29_MSK 0U
#endif

#ifdef PIN_PD30
    #define SDL_PD30_MSK (1UL << ((PIN_PD30) & 0x1FU))
#else
    #define SDL_PD30_MSK 0U
#endif

#ifdef PIN_PD31
    #define SDL_PD31_MSK (1UL << ((PIN_PD31) & 0x1FU))
#else
    #define SDL_PD31_MSK 0U
#endif

/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Global Variables
*------------------------------------------------------------------------------------------------------------*/
static const uint32_t sdlPortAMask = ( \
    SDL_PA00_MSK | SDL_PA01_MSK | SDL_PA02_MSK | SDL_PA03_MSK | \
    SDL_PA04_MSK | SDL_PA05_MSK | SDL_PA06_MSK | SDL_PA07_MSK | \
    SDL_PA08_MSK | SDL_PA09_MSK | SDL_PA10_MSK | SDL_PA11_MSK | \
    SDL_PA12_MSK | SDL_PA13_MSK | SDL_PA14_MSK | SDL_PA15_MSK | \
    SDL_PA16_MSK | SDL_PA17_MSK | SDL_PA18_MSK | SDL_PA19_MSK | \
    SDL_PA20_MSK | SDL_PA21_MSK | SDL_PA22_MSK | SDL_PA23_MSK | \
    SDL_PA24_MSK | SDL_PA25_MSK | SDL_PA26_MSK | SDL_PA27_MSK | \
    SDL_PA28_MSK | SDL_PA29_MSK | SDL_PA30_MSK | SDL_PA31_MSK   \
);

static const uint32_t sdlPortBMask = ( \
    SDL_PB00_MSK | SDL_PB01_MSK | SDL_PB02_MSK | SDL_PB03_MSK | \
    SDL_PB04_MSK | SDL_PB05_MSK | SDL_PB06_MSK | SDL_PB07_MSK | \
    SDL_PB08_MSK | SDL_PB09_MSK | SDL_PB10_MSK | SDL_PB11_MSK | \
    SDL_PB12_MSK | SDL_PB13_MSK | SDL_PB14_MSK | SDL_PB15_MSK | \
    SDL_PB16_MSK | SDL_PB17_MSK | SDL_PB18_MSK | SDL_PB19_MSK | \
    SDL_PB20_MSK | SDL_PB21_MSK | SDL_PB22_MSK | SDL_PB23_MSK | \
    SDL_PB24_MSK | SDL_PB25_MSK | SDL_PB26_MSK | SDL_PB27_MSK | \
    SDL_PB28_MSK | SDL_PB29_MSK | SDL_PB30_MSK | SDL_PB31_MSK   \
);
static const uint32_t sdlPortCMask = ( \
    SDL_PC00_MSK | SDL_PC01_MSK | SDL_PC02_MSK | SDL_PC03_MSK | \
    SDL_PC04_MSK | SDL_PC05_MSK | SDL_PC06_MSK | SDL_PC07_MSK | \
    SDL_PC08_MSK | SDL_PC09_MSK | SDL_PC10_MSK | SDL_PC11_MSK | \
    SDL_PC12_MSK | SDL_PC13_MSK | SDL_PC14_MSK | SDL_PC15_MSK | \
    SDL_PC16_MSK | SDL_PC17_MSK | SDL_PC18_MSK | SDL_PC19_MSK | \
    SDL_PC20_MSK | SDL_PC21_MSK | SDL_PC22_MSK | SDL_PC23_MSK | \
    SDL_PC24_MSK | SDL_PC25_MSK | SDL_PC26_MSK | SDL_PC27_MSK | \
    SDL_PC28_MSK | SDL_PC29_MSK | SDL_PC30_MSK | SDL_PC31_MSK   \
);
static const uint32_t sdlPortDMask =  ( \
    SDL_PD00_MSK | SDL_PD01_MSK | SDL_PD02_MSK | SDL_PD03_MSK | \
    SDL_PD04_MSK | SDL_PD05_MSK | SDL_PD06_MSK | SDL_PD07_MSK | \
    SDL_PD08_MSK | SDL_PD09_MSK | SDL_PD10_MSK | SDL_PD11_MSK | \
    SDL_PD12_MSK | SDL_PD13_MSK | SDL_PD14_MSK | SDL_PD15_MSK | \
    SDL_PD16_MSK | SDL_PD17_MSK | SDL_PD18_MSK | SDL_PD19_MSK | \
    SDL_PD20_MSK | SDL_PD21_MSK | SDL_PD22_MSK | SDL_PD23_MSK | \
    SDL_PD24_MSK | SDL_PD25_MSK | SDL_PD26_MSK | SDL_PD27_MSK | \
    SDL_PD28_MSK | SDL_PD29_MSK | SDL_PD30_MSK | SDL_PD31_MSK   \
);

const SDL_SFR_RW_INFO sdlPortWRSFRInfo[4][8] =
{

    {

                /* writeReg*/                    /* readReg */                      /* Mask */                      /*Reg Size */   /* Write Mode */

        {   PORT_DIR_REG_OFST,                  PORT_DIR_REG_OFST,           (PORT_DIR_DIR_Msk & sdlPortAMask),         4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_DIRCLR_REG_OFST,               PORT_DIRCLR_REG_OFST,        (PORT_DIRCLR_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_DIRSET_REG_OFST,               PORT_DIRSET_REG_OFST,        (PORT_DIRSET_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_DIRTGL_REG_OFST,               PORT_DIRTGL_REG_OFST,        (PORT_DIRTGL_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUT_REG_OFST,                  PORT_OUT_REG_OFST,           (PORT_OUT_Msk & sdlPortAMask),             4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_OUTCLR_REG_OFST,               PORT_OUTCLR_REG_OFST,        (PORT_OUTCLR_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUTSET_REG_OFST,               PORT_OUTSET_REG_OFST,        (PORT_OUTSET_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_OUTTGL_REG_OFST,               PORT_OUTTGL_REG_OFST,        (PORT_OUTTGL_Msk & sdlPortAMask),          4U,          SDL_WRITE_1_READ_0        },

    },


    {

                /* writeReg*/                    /* readReg */                      /* Mask */                      /*Reg Size */   /* Write Mode */

        {   PORT_DIR_REG_OFST,                  PORT_DIR_REG_OFST,           (PORT_DIR_DIR_Msk & sdlPortBMask),         4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_DIRCLR_REG_OFST,               PORT_DIRCLR_REG_OFST,        (PORT_DIRCLR_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_DIRSET_REG_OFST,               PORT_DIRSET_REG_OFST,        (PORT_DIRSET_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_DIRTGL_REG_OFST,               PORT_DIRTGL_REG_OFST,        (PORT_DIRTGL_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUT_REG_OFST,                  PORT_OUT_REG_OFST,           (PORT_OUT_Msk & sdlPortBMask),             4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_OUTCLR_REG_OFST,               PORT_OUTCLR_REG_OFST,        (PORT_OUTCLR_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUTSET_REG_OFST,               PORT_OUTSET_REG_OFST,        (PORT_OUTSET_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_OUTTGL_REG_OFST,               PORT_OUTTGL_REG_OFST,        (PORT_OUTTGL_Msk & sdlPortBMask),          4U,          SDL_WRITE_1_READ_0        },

    },

    {

                /* writeReg*/                    /* readReg */                      /* Mask */                      /*Reg Size */   /* Write Mode */

        {   PORT_DIR_REG_OFST,                  PORT_DIR_REG_OFST,           (PORT_DIR_DIR_Msk & sdlPortCMask),         4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_DIRCLR_REG_OFST,               PORT_DIRCLR_REG_OFST,        (PORT_DIRCLR_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_DIRSET_REG_OFST,               PORT_DIRSET_REG_OFST,        (PORT_DIRSET_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_DIRTGL_REG_OFST,               PORT_DIRTGL_REG_OFST,        (PORT_DIRTGL_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUT_REG_OFST,                  PORT_OUT_REG_OFST,           (PORT_OUT_Msk & sdlPortCMask),             4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_OUTCLR_REG_OFST,               PORT_OUTCLR_REG_OFST,        (PORT_OUTCLR_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUTSET_REG_OFST,               PORT_OUTSET_REG_OFST,        (PORT_OUTSET_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_OUTTGL_REG_OFST,               PORT_OUTTGL_REG_OFST,        (PORT_OUTTGL_Msk & sdlPortCMask),          4U,          SDL_WRITE_1_READ_0        },

    },

    {

                /* writeReg*/                    /* readReg */                      /* Mask */                      /*Reg Size */   /* Write Mode */

        {   PORT_DIR_REG_OFST,                  PORT_DIR_REG_OFST,           (PORT_DIR_DIR_Msk & sdlPortDMask),         4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_DIRCLR_REG_OFST,               PORT_DIRCLR_REG_OFST,        (PORT_DIRCLR_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_DIRSET_REG_OFST,               PORT_DIRSET_REG_OFST,        (PORT_DIRSET_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_DIRTGL_REG_OFST,               PORT_DIRTGL_REG_OFST,        (PORT_DIRTGL_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUT_REG_OFST,                  PORT_OUT_REG_OFST,           (PORT_OUT_Msk & sdlPortDMask),             4U,          SDL_WRITE_1_0_READ_1_0    },

        {   PORT_OUTCLR_REG_OFST,               PORT_OUTCLR_REG_OFST,        (PORT_OUTCLR_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_0        },

        {   PORT_OUTSET_REG_OFST,               PORT_OUTSET_REG_OFST,        (PORT_OUTSET_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_1        },

        {   PORT_OUTTGL_REG_OFST,               PORT_OUTTGL_REG_OFST,        (PORT_OUTTGL_Msk & sdlPortDMask),          4U,          SDL_WRITE_1_READ_0        },

    }
};

const SDL_SFR_RESET_INFO sdlPortResetSFRInfo[] =
{
            /* Offset*/                         /* Default Value */             /* Register size */
    {   PORT_DIR_REG_OFST,                     PORT_DIR_RESETVALUE,                      4U          },
    {   PORT_DIRCLR_REG_OFST,                  PORT_DIRCLR_RESETVALUE,                   4U          },
    {   PORT_DIRSET_REG_OFST,                  PORT_DIRSET_RESETVALUE,                   4U          },
    {   PORT_DIRTGL_REG_OFST,                  PORT_DIRTGL_RESETVALUE,                   4U          },
    {   PORT_OUT_REG_OFST,                     PORT_OUT_RESETVALUE,                      4U          },
    {   PORT_OUTCLR_REG_OFST,                  PORT_OUTCLR_RESETVALUE,                   4U          },
    {   PORT_OUTSET_REG_OFST,                  PORT_OUTSET_RESETVALUE,                   4U          },
    {   PORT_OUTTGL_REG_OFST,                  PORT_OUTTGL_RESETVALUE,                   4U          },
    {   PORT_CTRL_REG_OFST,                    PORT_CTRL_RESETVALUE,                     4U          },
    {   PORT_EVCTRL_REG_OFST,                  PORT_EVCTRL_RESETVALUE,                   4U          },
    {   PORT_PMUX0_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX1_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX2_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX3_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX4_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX5_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX6_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX7_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX8_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX9_REG_OFST,                   PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX10_REG_OFST,                  PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX11_REG_OFST,                  PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX12_REG_OFST,                  PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX13_REG_OFST,                  PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PMUX14_REG_OFST,                  PORT_PMUX_RESETVALUE,                     1U          },
    {   PORT_PINCFG0_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG1_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG2_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG3_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG4_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG5_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG6_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG7_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG8_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG9_REG_OFST,                 PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG10_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG11_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG12_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG13_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG14_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG15_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG16_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG17_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG18_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG19_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG20_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG21_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG22_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG23_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG24_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG25_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG26_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG27_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG28_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG29_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
    {   PORT_PINCFG31_REG_OFST,                PORT_PINCFG_RESETVALUE,                   1U          },
};

/*------------------------------------------------------------------------------------------------------------
* Local Variables
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Local Function Prototypes
*------------------------------------------------------------------------------------------------------------*/
/* None */

/*------------------------------------------------------------------------------------------------------------
* Function Definitions
*------------------------------------------------------------------------------------------------------------*/

/* Function:
    uint32_t SDL_DRV_PORT_GetPortGroupAddress(uint8_t sdlPortGroup)

  Description:
    Returns the base register address of the specified PORT group.

  Precondition:
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Base address of the PORT group registers.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_GetPortGroupAddress(uint8_t sdlPortGroup)
{
    return (PORT_BASE_ADDRESS + ((uint32_t)sdlPortGroup * (uint32_t)SDL_PORT_GROUP_OFFSET));
}

/* Function:
    SDL_BOOL SDL_DRV_PORT_IsPortValid(uint8_t sdlPortGroup)

  Description:
    Checks whether the specified PORT group index is valid for the device.

  Precondition:
    None

  Parameters:
    uint8_t sdlPortGroup - PORT group index to be validated.

  Returns:
    SDL_BOOL
      SDL_TRUE  - Valid PORT group.
      SDL_FALSE - Invalid PORT group.

  Remarks:
    None
*/
SDL_BOOL SDL_DRV_PORT_IsPortValid(uint8_t sdlPortGroup)
{
    SDL_BOOL sdlPortvalidGroup = SDL_FALSE;

    if(sdlPortGroup < (uint8_t)PORT_GROUP_NUMBER)
    {
        sdlPortvalidGroup = SDL_TRUE;
    }

    return sdlPortvalidGroup;
}

/* Function:
    SDL_BOOL SDL_DRV_PORT_IsPinValid(uint8_t sdlPortPin)

  Description:
    Verifies whether the specified logical PORT pin is valid for the device
    based on the available PORT group and pin mask.

  Precondition:
    None

  Parameters:
    uint8_t sdlPortPin - Encoded PORT pin value.

  Returns:
    SDL_BOOL
      SDL_TRUE  - Valid PORT pin.
      SDL_FALSE - Invalid PORT pin.

  Remarks:
    Pin validity is determined using device-specific PORT mask definitions.
*/
SDL_BOOL SDL_DRV_PORT_IsPinValid(uint8_t sdlPortPin)
{
    SDL_BOOL sdlPortValidPin = SDL_FALSE;
    uint8_t sdlPortGroup = sdlPortPin / 32U;
    sdlPortPin  = sdlPortPin % 32U;
    if (sdlPortGroup < 4U)
    {
        uint32_t mask = ((uint32_t)1U << (uint32_t)sdlPortPin);
        switch (sdlPortGroup)
        {
            case 0U:

                if ((sdlPortAMask & mask) != 0U)
                {
                    sdlPortValidPin = SDL_TRUE;
                }
                break;

            case 1U:
                if ((sdlPortBMask & mask) != 0U)
                {
                    sdlPortValidPin = SDL_TRUE;
                }
                break;
            case 2U:
                if ((sdlPortCMask & mask) != 0U)
                {
                    sdlPortValidPin = SDL_TRUE;
                }

                break;

            case 3U:
                if ((sdlPortDMask & mask) != 0U)
                {
                    sdlPortValidPin = SDL_TRUE;
                }
                break;

            default:
                /* do nothing */
                break;
        }
    }
    return sdlPortValidPin;
}

/* Function:
    void SDL_DRV_PORT_DirSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Configures the specified PORT pin direction as output.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_DirSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)
{
    PORT_REGS->GROUP[sdlPortGroup].PORT_DIR |= (1UL << (uint32_t)sdlPortPin);
    PORT_REGS->GROUP[sdlPortGroup].PORT_PINCFG[sdlPortPin] = (uint8_t)(PORT_PINCFG_INEN_Msk);
}

/* Function:
    void SDL_DRV_PORT_DirClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Configures the specified PORT pin direction as input.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_DirClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)
{
    PORT_REGS->GROUP[sdlPortGroup].PORT_DIR &= ~(1UL << (uint32_t)sdlPortPin);
    PORT_REGS->GROUP[sdlPortGroup].PORT_PINCFG[sdlPortPin] = (uint8_t)(PORT_PINCFG_INEN_Msk);
}

/* Function:
    void SDL_DRV_PORT_OutSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Sets the output level of the specified PORT pin to HIGH.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_OutSet(uint8_t sdlPortGroup, uint8_t sdlPortPin)
{
    PORT_REGS->GROUP[sdlPortGroup].PORT_OUT |= (1UL << (uint32_t)sdlPortPin);
}

/* Function:
    void SDL_DRV_PORT_OutClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Sets the output level of the specified PORT pin to LOW.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid

  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    None
*/
void SDL_DRV_PORT_OutClr(uint8_t sdlPortGroup, uint8_t sdlPortPin)
{
    PORT_REGS->GROUP[sdlPortGroup].PORT_OUT &= ~(1UL << (uint32_t)sdlPortPin);
}

/* Function:
    uint32_t SDL_DRV_PORT_DirRead(uint8_t sdlPortGroup)

  Description:
    Reads the PORT direction register for the specified group.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Direction register value.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_DirRead(uint8_t sdlPortGroup)
{
    return PORT_REGS->GROUP[sdlPortGroup].PORT_DIRSET;
}

/* Function:
    uint32_t SDL_DRV_PORT_PinRead(uint8_t sdlPortGroup)

  Description:
    Reads the input status register of the specified PORT group.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.

  Parameters:
    uint8_t sdlPortGroup - PORT group index.

  Returns:
    uint32_t - Input register value.

  Remarks:
    None
*/
uint32_t SDL_DRV_PORT_PinRead(uint8_t sdlPortGroup)
{
    return PORT_REGS->GROUP[sdlPortGroup].PORT_IN;
}

/* Function:
    void SDL_DRV_PORT_PullupEnable(uint8_t sdlPortGroup, uint8_t sdlPortPin)

  Description:
    Enables the internal pull-up resistor for the specified PORT pin.

  Precondition:
    - The PORT module clock must be initialized.
    - The input port group must be valid.
    - The port group and pin must be valid.


  Parameters:
    uint8_t sdlPortGroup - PORT group index.
    uint8_t sdlPortPin   - PORT pin number within the group.

  Returns:
    None

  Remarks:
    Input buffer is also enabled when pull-up is configured.
*/
void SDL_DRV_PORT_PullupEnable(uint8_t sdlPortGroup, uint8_t sdlPortPin)
{
    PORT_REGS->GROUP[sdlPortGroup].PORT_PINCFG[sdlPortPin] = (uint8_t)(PORT_PINCFG_PULLEN_Msk | PORT_PINCFG_INEN_Msk);
}
