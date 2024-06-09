/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "../../Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.h"
#include "../../Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_ts.h"
#include <stdlib.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Base address of the Flash sectors Bank 2 */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base @ of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base @ of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base @ of Sector 11, 128 Kbytes */


#define LCD_FRAME_BUFFER_LAYER0                  (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1                  LCD_FRAME_BUFFER
#define CONVERTED_FRAME_BUFFER                   (LCD_FRAME_BUFFER+0x260000)

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define MAX_LEVEL_BBG 6


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOF
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOF
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOF
#define A3_Pin GPIO_PIN_3
#define A3_GPIO_Port GPIOF
#define A4_Pin GPIO_PIN_4
#define A4_GPIO_Port GPIOF
#define A5_Pin GPIO_PIN_5
#define A5_GPIO_Port GPIOF
#define SPI5_SCK_Pin GPIO_PIN_7
#define SPI5_SCK_GPIO_Port GPIOF
#define SPI5_MISO_Pin GPIO_PIN_8
#define SPI5_MISO_GPIO_Port GPIOF
#define SPI5_MOSI_Pin GPIO_PIN_9
#define SPI5_MOSI_GPIO_Port GPIOF
#define ENABLE_Pin GPIO_PIN_10
#define ENABLE_GPIO_Port GPIOF
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define SDNWE_Pin GPIO_PIN_0
#define SDNWE_GPIO_Port GPIOC
#define NCS_MEMS_SPI_Pin GPIO_PIN_1
#define NCS_MEMS_SPI_GPIO_Port GPIOC
#define CSX_Pin GPIO_PIN_2
#define CSX_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define MEMS_INT1_Pin GPIO_PIN_1
#define MEMS_INT1_GPIO_Port GPIOA
#define MEMS_INT2_Pin GPIO_PIN_2
#define MEMS_INT2_GPIO_Port GPIOA
#define B5_Pin GPIO_PIN_3
#define B5_GPIO_Port GPIOA
#define VSYNC_Pin GPIO_PIN_4
#define VSYNC_GPIO_Port GPIOA
#define G2_Pin GPIO_PIN_6
#define G2_GPIO_Port GPIOA
#define ACP_RST_Pin GPIO_PIN_7
#define ACP_RST_GPIO_Port GPIOA
#define OTG_FS_PSO_Pin GPIO_PIN_4
#define OTG_FS_PSO_GPIO_Port GPIOC
#define OTG_FS_OC_Pin GPIO_PIN_5
#define OTG_FS_OC_GPIO_Port GPIOC
#define R3_Pin GPIO_PIN_0
#define R3_GPIO_Port GPIOB
#define R6_Pin GPIO_PIN_1
#define R6_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define SDNRAS_Pin GPIO_PIN_11
#define SDNRAS_GPIO_Port GPIOF
#define A6_Pin GPIO_PIN_12
#define A6_GPIO_Port GPIOF
#define A7_Pin GPIO_PIN_13
#define A7_GPIO_Port GPIOF
#define A8_Pin GPIO_PIN_14
#define A8_GPIO_Port GPIOF
#define A9_Pin GPIO_PIN_15
#define A9_GPIO_Port GPIOF
#define A10_Pin GPIO_PIN_0
#define A10_GPIO_Port GPIOG
#define A11_Pin GPIO_PIN_1
#define A11_GPIO_Port GPIOG
#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOE
#define D5_Pin GPIO_PIN_8
#define D5_GPIO_Port GPIOE
#define D6_Pin GPIO_PIN_9
#define D6_GPIO_Port GPIOE
#define D7_Pin GPIO_PIN_10
#define D7_GPIO_Port GPIOE
#define D8_Pin GPIO_PIN_11
#define D8_GPIO_Port GPIOE
#define D9_Pin GPIO_PIN_12
#define D9_GPIO_Port GPIOE
#define D10_Pin GPIO_PIN_13
#define D10_GPIO_Port GPIOE
#define D11_Pin GPIO_PIN_14
#define D11_GPIO_Port GPIOE
#define D12_Pin GPIO_PIN_15
#define D12_GPIO_Port GPIOE
#define G4_Pin GPIO_PIN_10
#define G4_GPIO_Port GPIOB
#define G5_Pin GPIO_PIN_11
#define G5_GPIO_Port GPIOB
#define OTG_HS_ID_Pin GPIO_PIN_12
#define OTG_HS_ID_GPIO_Port GPIOB
#define VBUS_HS_Pin GPIO_PIN_13
#define VBUS_HS_GPIO_Port GPIOB
#define OTG_HS_DM_Pin GPIO_PIN_14
#define OTG_HS_DM_GPIO_Port GPIOB
#define OTG_HS_DP_Pin GPIO_PIN_15
#define OTG_HS_DP_GPIO_Port GPIOB
#define D13_Pin GPIO_PIN_8
#define D13_GPIO_Port GPIOD
#define D14_Pin GPIO_PIN_9
#define D14_GPIO_Port GPIOD
#define D15_Pin GPIO_PIN_10
#define D15_GPIO_Port GPIOD
#define TE_Pin GPIO_PIN_11
#define TE_GPIO_Port GPIOD
#define RDX_Pin GPIO_PIN_12
#define RDX_GPIO_Port GPIOD
#define WRX_DCX_Pin GPIO_PIN_13
#define WRX_DCX_GPIO_Port GPIOD
#define D0_Pin GPIO_PIN_14
#define D0_GPIO_Port GPIOD
#define D1_Pin GPIO_PIN_15
#define D1_GPIO_Port GPIOD
#define BA0_Pin GPIO_PIN_4
#define BA0_GPIO_Port GPIOG
#define BA1_Pin GPIO_PIN_5
#define BA1_GPIO_Port GPIOG
#define R7_Pin GPIO_PIN_6
#define R7_GPIO_Port GPIOG
#define DOTCLK_Pin GPIO_PIN_7
#define DOTCLK_GPIO_Port GPIOG
#define SDCLK_Pin GPIO_PIN_8
#define SDCLK_GPIO_Port GPIOG
#define HSYNC_Pin GPIO_PIN_6
#define HSYNC_GPIO_Port GPIOC
#define G6_Pin GPIO_PIN_7
#define G6_GPIO_Port GPIOC
#define I2C3_SDA_Pin GPIO_PIN_9
#define I2C3_SDA_GPIO_Port GPIOC
#define I2C3_SCL_Pin GPIO_PIN_8
#define I2C3_SCL_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_9
#define STLINK_RX_GPIO_Port GPIOA
#define STLINK_TX_Pin GPIO_PIN_10
#define STLINK_TX_GPIO_Port GPIOA
#define R4_Pin GPIO_PIN_11
#define R4_GPIO_Port GPIOA
#define R5_Pin GPIO_PIN_12
#define R5_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define TP_INT1_Pin GPIO_PIN_15
#define TP_INT1_GPIO_Port GPIOA
#define R2_Pin GPIO_PIN_10
#define R2_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_0
#define D2_GPIO_Port GPIOD
#define D3_Pin GPIO_PIN_1
#define D3_GPIO_Port GPIOD
#define G7_Pin GPIO_PIN_3
#define G7_GPIO_Port GPIOD
#define B2_Pin GPIO_PIN_6
#define B2_GPIO_Port GPIOD
#define G3_Pin GPIO_PIN_10
#define G3_GPIO_Port GPIOG
#define B3_Pin GPIO_PIN_11
#define B3_GPIO_Port GPIOG
#define B4_Pin GPIO_PIN_12
#define B4_GPIO_Port GPIOG
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOG
#define LD4_Pin GPIO_PIN_14
#define LD4_GPIO_Port GPIOG
#define SDNCAS_Pin GPIO_PIN_15
#define SDNCAS_GPIO_Port GPIOG
#define SDCKE1_Pin GPIO_PIN_5
#define SDCKE1_GPIO_Port GPIOB
#define SDNE1_Pin GPIO_PIN_6
#define SDNE1_GPIO_Port GPIOB
#define B6_Pin GPIO_PIN_8
#define B6_GPIO_Port GPIOB
#define B7_Pin GPIO_PIN_9
#define B7_GPIO_Port GPIOB
#define NBL0_Pin GPIO_PIN_0
#define NBL0_GPIO_Port GPIOE
#define NBL1_Pin GPIO_PIN_1
#define NBL1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
