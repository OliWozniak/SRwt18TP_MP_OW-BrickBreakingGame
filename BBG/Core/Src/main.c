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


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_2   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_23  +  GetSectorSize(ADDR_FLASH_SECTOR_23) -1 /* End @ of user Flash area : sector start address + sector size -1 */

#define DATA_32                 ((uint32_t)0x12345678)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint32_t Address;
char data[4]={'a','b','c','d'};
char read_data[4];
uint8_t level;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void menu_bbg();
void ReadRecord(Klocek *klocek, uint32_t flash_address);
int WriteRecord(Klocek *klocek, uint32_t address);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int fd, char *ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
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
  BSP_LCD_Clear(LCD_COLOR_RED);

  BSP_LCD_DisplayOn();

  Touchscreen_Calibration();
  BSP_LCD_Clear(LCD_COLOR_RED);


  menu_bbg();


  // Tutaj zmieniamy wczytywany/zapisywany poziom

  switch (level) {
	case 0:  Address=ADDR_FLASH_SECTOR_5;
		break;
	case 1:  Address=ADDR_FLASH_SECTOR_6;
		break;
	case 2:  Address=ADDR_FLASH_SECTOR_7;
		break;
	case 3:  Address=ADDR_FLASH_SECTOR_8;
		break;
	case 4:  Address=ADDR_FLASH_SECTOR_9;
		break;
	case 5:  Address=ADDR_FLASH_SECTOR_10;
		break;
	case 6:  Address=ADDR_FLASH_SECTOR_11;
		break;
	default: // Nie powinno cię tu być
		break;
}
  BSP_LCD_Clear(LCD_COLOR_RED);

                        // Liczba klocków
  int klocek_szerokosc = BSP_LCD_GetXSize() / 12; // Klocki są szersze niż wyższe
  int klocek_wysokosc = BSP_LCD_GetYSize() / 24; // Zakładamy 4 rzędy klocków
  int liczba_klockow = COLLUMNS_BBG*ROWS_BBG; // Liczba klocków



  Platforma *platforma = (Platforma *)malloc(sizeof(Platforma));
  Kulka *kulka = (Kulka *)malloc(sizeof(Kulka));

  Klocek **klocki = (Klocek **)malloc((liczba_klockow) * sizeof(Klocek *));
  int licznik = 0;

  for (int kk = 0; kk < COLLUMNS_BBG; kk++)
  { // Zakładając 4 rzędy klocków
    for (int k = 0; k < ROWS_BBG; k++, licznik++)
    { // 8 kolumn klocków
      klocki[licznik] = (Klocek *)malloc(sizeof(Klocek));
      uint32_t kolor_klocka = ((k % 2 == 0 && kk % 2 == 0) || (k % 2 == 1 && kk % 2 == 1)) ? LCD_COLOR_BLUE : LCD_COLOR_YELLOW;
      /////LEVEL1
      //Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);

      /////////////LEVEL2
      /*if(kk == 7  && (k >3 && k < 9)){
    	  kolor_klocka = LCD_COLOR_GRAY;
    	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
    	  continue;
      }
      else{
    	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
      }
      */

    /////////LEVEL3
	/*if(( k == 3  || k == 7) && (kk >=2 && kk <= 10)){
	  kolor_klocka = LCD_COLOR_GRAY;
	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
	  continue;
	}
	else{
	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
	}*/

    //////LEVEL4
      /*if(( k == 3  || k == 7) && (kk >=2 && kk <= 10)){
      	  kolor_klocka = LCD_COLOR_GRAY;
      	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
      	  continue;
      	}
      	else{
      	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
      	}*/
     //LEVEL5
     /* if(kk == 7  && ( (k >1 && k < 5) || (k > 6 && k <10 ) ) ){
		  kolor_klocka = LCD_COLOR_GRAY;
		  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
		  continue;
      }
      else{
	  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
      }
      */

      //LEVEL 6

       if( (kk == 2 || kk == 6 || kk == 10)  && ( (k >1 && k < 5) || (k > 6 && k <10 ) ) ){
      		  kolor_klocka = LCD_COLOR_GRAY;
      		  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
      		  continue;
		}
		else{
			Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
		}



      //LEVEL 7
      /*
      if(k * kk % 4 == 2){
			  kolor_klocka = LCD_COLOR_GRAY;
			  Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 0, 1);
			  continue;
		}
		else{
			Klocek_init(klocki[licznik], k * klocek_szerokosc, kk * klocek_wysokosc, klocek_szerokosc, klocek_wysokosc, kolor_klocka, 1, 1);
		}
		*/





//      HAL_FLASH_Unlock();
//      FLASH_Erase_Sector(5, FLASH_VOLTAGE_RANGE_3);
//      WriteRecord(klocki[licznik], Address + 16*licznik);
//      HAL_FLASH_Lock();
//
//      ReadRecord(klocki[licznik], Address + 16*licznik);
    }
  }




  int platforma_x = 50;
  int platforma_y = BSP_LCD_GetYSize() - 20;
  int platforma_szerokosc = 80;
  int platforma_wysokosc = 8;
  int platforma_krok = 5;
  uint32_t platforma_kolor = LCD_COLOR_WHITE;
  Platforma_init(platforma, platforma_x, platforma_y, platforma_szerokosc, platforma_wysokosc, platforma_krok, platforma_kolor);
  int kulka_pocz_x = 10 + (rand() % (BSP_LCD_GetXSize() - 20));
  int kulka_pocz_y = platforma_y-10;
  int kulka_r = 4;
  int kulka_vx = 2;
  int kulka_vy = -2;
  uint32_t kulka_kolor = LCD_COLOR_WHITE;
  uint32_t prev_tick=0;

  Kulka_init(kulka, kulka_pocz_x, kulka_pocz_y, kulka_r, kulka_vx, kulka_vy, kulka_kolor);

  BBG bbg;
  BBG_init(&bbg, platforma, klocki, kulka, liczba_klockow);

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
   {
	  if(HAL_GetTick()-prev_tick>=odswiezanie){
		  prev_tick=HAL_GetTick();
    if (BBG_ruchKulki(&bbg) == 1)
    {
      BSP_LCD_SetFont(&Font24);
      BSP_LCD_SetBackColor(LCD_COLOR_CYAN);
      BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
      BSP_LCD_DisplayStringAt(0, 100, "Game Over", CENTER_MODE);
      HAL_Delay(2000);
      return;
    }

    if(BBG_obsluga_zbicia_klocka(&bbg)==1){
        BSP_LCD_SetFont(&Font24);
        BSP_LCD_SetBackColor(LCD_COLOR_CYAN);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, 100, "!!! VICTORY !!!", CENTER_MODE);
        HAL_Delay(2000);
        return;
    }
    // 		Get touch state
    TS_StateTypeDef TS_State;
    BSP_TS_GetState(&TS_State);
    BBG_obsluzDotykEkranu(&bbg, TS_State);
	  }

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

void menu_bbg()
{
  BSP_LCD_Clear(LCD_COLOR_RED);

  BSP_LCD_SetTextColor(LCD_COLOR_GRAY);

  BSP_LCD_FillRect(0, (BSP_LCD_GetYSize() / 4)-25, 50, 50);
  BSP_LCD_FillRect(BSP_LCD_GetXSize() -50, (BSP_LCD_GetYSize() / 4)-25, 50, 50);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

  BSP_LCD_FillTriangle(15, 25, 25, BSP_LCD_GetYSize() / 4, (BSP_LCD_GetYSize() / 4)+10, (BSP_LCD_GetYSize() / 4)-10);
  BSP_LCD_FillTriangle(BSP_LCD_GetXSize() -15, BSP_LCD_GetXSize() -25, BSP_LCD_GetXSize() -25, BSP_LCD_GetYSize() / 4, (BSP_LCD_GetYSize() / 4)+10, (BSP_LCD_GetYSize() / 4)-10);

  BSP_LCD_SetFont(&Font20);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize() / 4)-30, "BBG", CENTER_MODE);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize() / 4)-10, "Select level", CENTER_MODE);
  level=0;
  char level_txt[5];

  BSP_LCD_SetFont(&Font24);
BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize() / 4)+10, itoa(level+1,level_txt, 10), CENTER_MODE);
BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize() / 4)*3, "START", CENTER_MODE);


  while (1)
  {
    TS_StateTypeDef TS_State;
    BSP_TS_GetState(&TS_State);
    if (TS_State.TouchDetected)
    {
    	uint16_t x = Calibration_GetX(TS_State.X);
    	uint16_t y = Calibration_GetY(TS_State.Y);

    	if(y<BSP_LCD_GetYSize() / 2 && x>BSP_LCD_GetXSize() / 2){
    		if(level<MAX_LEVEL_BBG) level++;
    		HAL_Delay(200);
    	}

    	if(y<BSP_LCD_GetYSize() / 2 && x < BSP_LCD_GetXSize() / 2){
    		if(level>0) level--;
    		HAL_Delay(200);
    	}

    	if(y>BSP_LCD_GetYSize() / 2){
    	      HAL_Delay(500);
    	      return;
    	}


    	BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize() / 4)+10, itoa(level+1,level_txt, 10), CENTER_MODE);

    }
  }
}


void ReadRecord(Klocek *klocek, uint32_t flash_address)
{
    uint32_t *ptr = (uint32_t* )klocek;

  for (int i = 0; i < sizeof(Klocek); i+=4, ptr++, flash_address+=4 )
     *ptr = *(__IO uint32_t *)flash_address;
}

int WriteRecord(Klocek *klocek, uint32_t address)
{
    int i;
    uint32_t *pRecord = (uint32_t* )klocek;
    uint32_t flash_address = address;


    HAL_FLASH_Unlock();
    for(i=0; i<sizeof(Klocek); i+=4, pRecord++, flash_address+=4){
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_address,*pRecord);
    }
    HAL_FLASH_Lock();
    return i;
}

void WriteKlockiToFlash(Klocek **klocki, int liczba_klockow) {
    HAL_StatusTypeDef status;

    // Odblokowanie pamięci flash
    HAL_FLASH_Unlock();

    // Konfiguracja struktury do kasowania sektora
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SectorError = 0;

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = FLASH_SECTOR_6; // Numer sektora do skasowania
    EraseInitStruct.NbSectors = 1;

    // Kasowanie sektora
    status = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
    if (status != HAL_OK) {
        // Obsługa błędów kasowania
        while (1) {}
    }

    // Programowanie pamięci flash
    for (int i = 0; i < liczba_klockow; i++) {
        WriteRecord(klocki[i], FLASH_SECTOR_6 + i * sizeof(Klocek));
    }

    // Zablokowanie pamięci flash
    HAL_FLASH_Lock();
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
	  BSP_LED_On(LED4);
	  while(1)
	  {
	  }
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
