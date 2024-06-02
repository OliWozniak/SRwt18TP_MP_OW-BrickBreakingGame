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
#include <stdlib.h>
#include "klocek.h"
#include "Kulka.h"
#include "Platforma.h"
#include "BBG.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t layer_flag;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void menu_bbg();
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


  int odswiezanie = 16;
      BSP_LCD_Init();

          BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
          BSP_LCD_SelectLayer(1);
          BSP_LCD_Clear(LCD_COLOR_RED);
          BSP_LCD_SetLayerVisible(1, DISABLE);

          BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);
          BSP_LCD_SelectLayer(0);
          layer_flag=0;
          BSP_LCD_Clear(LCD_COLOR_RED);


          BSP_LCD_DisplayOn();

          Touchscreen_Calibration();
          menu_bbg();
          BSP_LCD_Clear(LCD_COLOR_RED);


          int liczba_klockow = 32; // Liczba klocków
          int klocek_szerokosc = BSP_LCD_GetXSize() / 8; // Klocki są szersze niż wyższe
          int klocek_wysokosc = BSP_LCD_GetYSize() / 16;   // Zakładamy 4 rzędy klocków

          Platforma* platforma = (Platforma*)malloc(sizeof(Platforma));
          Kulka* kulka = (Kulka*)malloc(sizeof(Kulka));
          Klocek** klocki = (Klocek**)malloc(liczba_klockow * sizeof(Klocek*));
          int licznik = 0;

          for (int kk = 0; kk < liczba_klockow / 8; kk++) { // Zakładając 4 rzędy klocków
              for (int k = 0; k < 8; k++, licznik++) { // 8 kolumn klocków
                  klocki[licznik] = (Klocek*)malloc(sizeof(Klocek));
                  uint32_t kolor_klocka = ((k % 2 == 0 && kk % 2 == 0) || (k % 2 == 1 && kk % 2 == 1)) ? LCD_COLOR_BLUE : LCD_COLOR_YELLOW;
                  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka);
              }
          }

          int platforma_x = 50;
          int platforma_y = BSP_LCD_GetYSize() - 20;
          int platforma_szerokosc = 100;
          int platforma_wysokosc = 10;
          int platforma_krok = 5;
          uint32_t platforma_kolor = LCD_COLOR_WHITE;

          Platforma_init(platforma, platforma_x, platforma_y, platforma_szerokosc, platforma_wysokosc, platforma_krok, platforma_kolor);

          int kulka_pocz_x = 20;
          int kulka_pocz_y = BSP_LCD_GetYSize() / 2;
          int kulka_r = 5;
          int kulka_vx = 2;
          int kulka_vy = 2;
          uint32_t kulka_kolor = LCD_COLOR_WHITE;

          Kulka_init(kulka, kulka_pocz_x, kulka_pocz_y, kulka_r, kulka_vx, kulka_vy, kulka_kolor);

          BBG bbg;
          BBG_init(&bbg, platforma, klocki, kulka, liczba_klockow);

  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(layer_flag==0){

	  }
	  else if(layer_flag==1){

	  }
	  if(BBG_ruchKulki(&bbg)==1){
			BSP_LCD_SetFont(&Font20);
			BSP_LCD_SetBackColor(LCD_COLOR_CYAN);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		  BSP_LCD_DisplayStringAt(0, 100, "Game Over", CENTER_MODE);
		  //return;
	  }
	  BBG_obsluga_zbicia_klocka(&bbg);

// 		Get touch state
	  TS_StateTypeDef  TS_State;
      BSP_TS_GetState(&TS_State);
      BBG_obsluzDotykEkranu(&bbg, TS_State);
	  HAL_Delay(odswiezanie);


//
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
//  for (int i = 0; i < liczba_klockow; i++) {
//	  free(klocki[i]);
//  }
//  free(klocki);
//  free(platforma);
//  free(kulka);

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

void menu_bbg(){
	BSP_LCD_Clear(LCD_COLOR_RED);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetBackColor(LCD_COLOR_CYAN);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2, "BBG", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 20, "Touch screen to begin", CENTER_MODE);

	while(1){
		TS_StateTypeDef  TS_State;
		BSP_TS_GetState(&TS_State);
		if(TS_State.TouchDetected){
			BSP_LCD_SetFont(&Font20);

		BSP_LCD_DisplayStringAt(0, 20, "TOUCHED!", CENTER_MODE);
		HAL_Delay(500);
		return;
		}
	}
}

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
