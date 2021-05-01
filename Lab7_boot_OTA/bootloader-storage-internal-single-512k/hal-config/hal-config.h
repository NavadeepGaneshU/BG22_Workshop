#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#include "em_device.h"
#include "hal-config-types.h"

// This file is auto-generated by Hardware Configurator in Simplicity Studio.
// Any content between $[ and ]$ will be replaced whenever the file is regenerated.
// Content outside these regions will be preserved.

// $[ANTDIV]
// [ANTDIV]$

// $[BTL_BUTTON]
// [BTL_BUTTON]$

// $[BUTTON]
// [BUTTON]$

// $[CMU]
#define HAL_CLK_HFCLK_SOURCE               (HAL_CLK_HFCLK_SOURCE_HFRCODPLL)
#define HAL_CLK_PLL_CONFIGURATION          (HAL_CLK_PLL_CONFIGURATION_76_8MHZ)
#define HAL_CLK_EM01CLK_SOURCE             (HAL_CLK_HFCLK_SOURCE_HFRCODPLL)
#define HAL_CLK_EM23CLK_SOURCE             (HAL_CLK_LFCLK_SOURCE_DISABLED)
#define HAL_CLK_EM4CLK_SOURCE              (HAL_CLK_LFCLK_SOURCE_DISABLED)
#define HAL_CLK_RTCCCLK_SOURCE             (HAL_CLK_LFCLK_SOURCE_DISABLED)
#define HAL_CLK_WDOGCLK_SOURCE             (HAL_CLK_LFCLK_SOURCE_LFRCO)
#define BSP_CLK_HFXO_PRESENT               (1)
#define BSP_CLK_HFXO_FREQ                  (38400000UL)
#define BSP_CLK_HFXO_INIT                   CMU_HFXOINIT_DEFAULT
#define BSP_CLK_HFXO_CTUNE                 (120)
#define BSP_CLK_LFXO_PRESENT               (1)
#define BSP_CLK_LFXO_INIT                   CMU_LFXOINIT_DEFAULT
#define BSP_CLK_LFXO_FREQ                  (32768U)
#define BSP_CLK_LFXO_CTUNE                 (37U)
#define HAL_CLK_LFXO_PRECISION             (100UL)
#define HAL_CLK_LFRCO_PRECISION            (0)
// [CMU]$

// $[COEX]
// [COEX]$

// $[DCDC]
#define BSP_DCDC_PRESENT                   (1)

#define BSP_DCDC_INIT                       EMU_DCDCINIT_DEFAULT
#define HAL_DCDC_BYPASS                    (0)
// [DCDC]$

// $[EMU]
// [EMU]$

// $[EUART0]
// [EUART0]$

// $[EXTFLASH]
// [EXTFLASH]$

// $[EZRADIOPRO]
// [EZRADIOPRO]$

// $[FEM]
// [FEM]$

// $[GPIO]
// [GPIO]$

// $[I2C0]
// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[I2CSENSOR]
// [I2CSENSOR]$

// $[IADC0]
// [IADC0]$

// $[IOEXP]
// [IOEXP]$

// $[LED]
// [LED]$

// $[LETIMER0]
// [LETIMER0]$

// $[LFXO]
// [LFXO]$

// $[MODEM]
// [MODEM]$

// $[PA]
// [PA]$

// $[PDM]
// [PDM]$

// $[PORTIO]
// [PORTIO]$

// $[PRS]
// [PRS]$

// $[PTI]
// [PTI]$

// $[RSSI]
// [RSSI]$

// $[SERIAL]
// [SERIAL]$

// $[SPIDISPLAY]
// [SPIDISPLAY]$

// $[SPINCP]
// [SPINCP]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[TIMER2]
// [TIMER2]$

// $[TIMER3]
// [TIMER3]$

// $[TIMER4]
// [TIMER4]$

// $[UARTNCP]
// [UARTNCP]$

// $[USART0]
// [USART0]$

// $[USART1]
// [USART1]$

// $[VCOM]
// [VCOM]$

// $[VUART]
// [VUART]$

// $[WDOG]
// [WDOG]$

// $[Custom pin names]
#define MIC_ENABLE_PIN                     (0U)
#define MIC_ENABLE_PORT                    (gpioPortA)

#define IMU_CS_PIN                         (2U)
#define IMU_CS_PORT                        (gpioPortB)

#define IMU_INT_PIN                        (3U)
#define IMU_INT_PORT                       (gpioPortB)

#define IMU_ENABLE_PIN                     (4U)
#define IMU_ENABLE_PORT                    (gpioPortB)

#define MIC_CLK_PIN                        (6U)
#define MIC_CLK_PORT                       (gpioPortC)

#define MIC_DATA_PIN                       (7U)
#define MIC_DATA_PORT                      (gpioPortC)

// [Custom pin names]$

#if defined(_SILICON_LABS_MODULE)
#include "sl_module.h"
#endif


#endif /* HAL_CONFIG_H */

