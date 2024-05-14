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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  char buffer [sizeof(int)*8+1];
  int polozenie_x;
  int polozenie_y=10;

  // klocki
  int wysokosc = 5;
  int szerokosc = 10;

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

  /*uint8_t status = 0;
  status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  if (status != TS_OK)
  {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t*)"ERROR", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)"Touchscreen cannot be initialized", CENTER_MODE);
  }
  else if (status == TS_OK)
  {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t*)"STATUS OK", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)"Touchscreen is initialized", CENTER_MODE);
  }*/
  Touchscreen_Calibration();
  BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  BSP_LCD_Clear(LCD_COLOR_RED); //
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  polozenie_x=BSP_LCD_GetXSize()/2;
  //BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Hello, world!", CENTER_MODE);

  BSP_LCD_SetBackColor(LCD_COLOR_YELLOW); // Ustaw kolor tła na żółty
      for (int i = 0; i < 5; i++) {
          uint16_t x = i * 10; // Oblicz pozycję X dla każdego klocka
          BSP_LCD_FillRect(x, 0, 10, 5); // Narysuj prostokąt (klocek) o zadanej szerokości i wysokości
      }




  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  TS_StateTypeDef  TS_State;
	   uint16_t x = 0, y = 0; // Zmienne na współrzędne X i Y
	   BSP_TS_GetState(&TS_State);
	          if (TS_State.TouchDetected !=0) {
	              x = TS_State.X; // Pierwszy punkt dotknięcia
	              y = TS_State.Y;
	              // Tutaj możesz wykorzystać współrzędne x i y do dalszej obróbki
	          }


//
//	  static uint32_t x = 0, y = 0;
//	  static TS_StateTypeDef  TS_State;
//	  BSP_TS_GetState(&TS_State);
//	  x = Calibration_GetX(TS_State.X);
//	  y = Calibration_GetY(TS_State.Y);
//
//	  if (TS_State.TouchDetected){
////	  BSP_LCD_SelectLayer(0);
////		  BSP_LCD_Clear(LCD_COLOR_BLUE);
////		  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//		  if ((TS_State.TouchDetected) & ( x > 0 ) & ( x < BSP_LCD_GetXSize()/2)){
//			  //BSP_LCD_FillRect(BSP_LCD_GetXSize()/4, BSP_LCD_GetYSize()/2, BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize());
//			  //BSP_LCD_FillRect((x), (y), 20, 10);
//			  BSP_LCD_SetTextColor(LCD_COLOR_RED);
//			  BSP_LCD_FillRect((polozenie_x), (polozenie_y), 20, 10);
//			  polozenie_x--;
//			  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//			  BSP_LCD_FillRect((polozenie_x), (polozenie_y), 20, 10);
//
//		  }
//		  else if ((TS_State.TouchDetected) & ( x > BSP_LCD_GetXSize()/2 ) & ( x < BSP_LCD_GetXSize())){
//			  //BSP_LCD_FillRect((3*(BSP_LCD_GetXSize())/4), BSP_LCD_GetYSize()/2, BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize());
//			  //BSP_LCD_FillRect((x), (y), 10, 20);
//			  BSP_LCD_SetTextColor(LCD_COLOR_RED);
//			  BSP_LCD_FillRect((polozenie_x), (polozenie_y), 20, 10);
//			  polozenie_x++;
//			  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//			  BSP_LCD_FillRect((polozenie_x), (polozenie_y), 20, 10);
//
//		  }
//		  BSP_LCD_SelectLayer(1);
//		  itoa(x,buffer,10);
//			  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)"X:", LEFT_MODE);
//			  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)buffer, CENTER_MODE);
//			  itoa (y,buffer,10);
//			  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 112, (uint8_t*)"Y:", LEFT_MODE);
//			  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 112, (uint8_t*)buffer, CENTER_MODE);
//		  }

	  HAL_Delay(5);

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
  /* User can add his own implementation to report the HAL error return state */

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
