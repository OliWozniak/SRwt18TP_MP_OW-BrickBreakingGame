/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int fd, char* ptr, int len) {
    HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	static char buffer [sizeof(int)*8+1];
	static  int polozenie_x;
	static  int polozenie_y;
	static  int liczba_klockow = 6 ;
	static int szerokosc_klocka = 30;
	static int wysokosc_klocka = 10;
	static int wysokosc_platformy = 10;
	static int szerekosc_platformy = 50;
	static int dlugosc_kroku = 5;
	static int odswiezanie = 16;
	static int promien_kulki = 5;
	static int predkosc_kulki_x = 1;
	static int predkosc_kulki_y = 2;
	static int polozenie_kulki_x = 35;
	static int polozenie_kulki_y = 55 ;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    //HAL_Delay(1000);
    BSP_LCD_SetColorKeying(1, LCD_COLOR_WHITE);
    BSP_LCD_SetLayerVisible(1, DISABLE);

    BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);
    BSP_LCD_SelectLayer(0);
    BSP_LCD_DisplayOn();

    BSP_LCD_Clear(LCD_COLOR_WHITE);

    BSP_LCD_SetFont(&Font12);

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

//    Touchscreen_Calibration();
    BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    BSP_LCD_Clear(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);

  polozenie_x = (BSP_LCD_GetXSize() / 2 ) - (szerekosc_platformy / 2 );
  polozenie_y = BSP_LCD_GetYSize() - 30;



   //rysowanie klockow
  for (int i = 0; i < liczba_klockow; i++) {
  		// rysowanie klockow na przemian kolorami
  		if (i % 2 == 0){
  			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  		}
  		else{
  			BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  		}

  		BSP_LCD_FillRect(i * (szerokosc_klocka), 30, szerokosc_klocka, wysokosc_klocka);

   }

  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillRect(polozenie_x, polozenie_y, szerekosc_platformy, wysokosc_platformy);

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_DrawCircle(polozenie_kulki_x, polozenie_kulki_x, promien_kulki);
  BSP_LCD_FillCircle(polozenie_kulki_x, polozenie_y, promien_kulki);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */

  /* Start scheduler */


  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if (polozenie_kulki_x +  promien_kulki > BSP_LCD_GetXSize()){
			polozenie_kulki_x = BSP_LCD_GetXSize() - promien_kulki ;
			predkosc_kulki_x *= -1;
		}
		else if (polozenie_kulki_x < 0){
		  polozenie_kulki_x =  promien_kulki;
		  predkosc_kulki_x *= -1;
		}

		if (polozenie_kulki_y +  promien_kulki > BSP_LCD_GetYSize()){
			polozenie_kulki_y = BSP_LCD_GetYSize() - promien_kulki;
			predkosc_kulki_y *= -1;
		}
		else if(polozenie_kulki_y < 2 * promien_kulki){
			 polozenie_kulki_y = 2 * promien_kulki;
			 predkosc_kulki_y *= -1;
		}

		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DrawCircle(polozenie_kulki_x, polozenie_kulki_y , promien_kulki);
		BSP_LCD_FillCircle(polozenie_kulki_x, polozenie_kulki_y , promien_kulki);

		polozenie_kulki_x += predkosc_kulki_x;
		polozenie_kulki_y += predkosc_kulki_y;

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DrawCircle(polozenie_kulki_x + predkosc_kulki_x, polozenie_kulki_y + predkosc_kulki_y, promien_kulki);
		BSP_LCD_FillCircle(polozenie_kulki_x + predkosc_kulki_x, polozenie_kulki_y + predkosc_kulki_y, promien_kulki);

//		itoa(polozenie_kulki_x, buffer, 10);
//		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)"X:", LEFT_MODE);
//		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)buffer, CENTER_MODE);
//		itoa(polozenie_kulki_y, buffer, 10);
//		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*)"Y:", LEFT_MODE);
//		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*)buffer, CENTER_MODE);

      uint32_t prev_x = polozenie_x;
      uint32_t prev_y = polozenie_y;

      // Get touch state
      TS_StateTypeDef  TS_State;
      BSP_TS_GetState(&TS_State);

      if (TS_State.TouchDetected) {
          uint32_t x = Calibration_GetX(TS_State.X);
          uint32_t y = Calibration_GetY(TS_State.Y);

          // Update platform position based on touch input
          if ((x < BSP_LCD_GetXSize() / 2 ) &( x > 0)) {
              polozenie_x = max(0, polozenie_x - dlugosc_kroku);  // Move left
          } else if ((x > BSP_LCD_GetXSize() / 2) & (x <  BSP_LCD_GetXSize())) {
              polozenie_x = min(BSP_LCD_GetXSize() - szerekosc_platformy, polozenie_x + dlugosc_kroku);  // Move right
          }

          BSP_LCD_SetTextColor(LCD_COLOR_RED);
          BSP_LCD_FillRect(prev_x, prev_y, szerekosc_platformy + dlugosc_kroku, wysokosc_platformy);

          BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
          BSP_LCD_FillRect(polozenie_x, polozenie_y, szerekosc_platformy, wysokosc_platformy);
          // Update previous position
          prev_x = polozenie_x;
          prev_y = polozenie_y;

          // wyswietlanie wspolrzdnych punktu dotyku
//          itoa(x, buffer, 10);
//          BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//          BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//          BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)"X:", LEFT_MODE);
//          BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80, (uint8_t*)buffer, CENTER_MODE);
//          itoa(y, buffer, 10);
//          BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*)"Y:", LEFT_MODE);
//          BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 112, (uint8_t*)buffer, CENTER_MODE);

      }

      HAL_Delay(odswiezanie);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */


  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
