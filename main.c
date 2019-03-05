/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "hdmi_cec.h"
#include "i2c.h"
#include "i2s.h"
#include "sdadc.h"
#include "spi.h"
#include "tsc.h"
#include "usart.h"
#include "usb.h"
#include "gpio.h"

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	
// System
#define LED_Port LED1_GPIO_Port

const int waitTime = 500;
int delay;
const uint16_t pins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin};

// Morse
const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
const char* morseLetters[37] = { " ", "._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._", "._..",  "__", "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._",".__", "_.._", "_.__", "__..", ".____", "..___", "...__", "...._", ".....", "_....", "__...", "___..", "____.", "_____"};


const char* letterToMorse(const char a)
{
	for(int i = 0; i < 37; i++)	
		if(letters[i] == a)
			return morseLetters[i];
	
	return NULL;	
}
void wait(short i)
{
	delay = HAL_GetTick() + (waitTime * i);
	while(HAL_GetTick() < delay){}		
}

void turnLEDs(short on)
{
	if(on == 1)
		for(int j = 0; j < 4; j++)
			HAL_GPIO_WritePin(LED_Port, pins[j], GPIO_PIN_RESET);
	else
		for(int j = 0; j < 4; j++)
			HAL_GPIO_WritePin(LED_Port, pins[j], GPIO_PIN_SET);	
}

void showCharInMorse(const char* a)
{
	for(int i = 0; i < sizeof(a); i++)
	{
		if(a[i] == '.' || a[i] == '_'){			
			turnLEDs(1);
			
			if(a[i] == '.')	// fent tart
				wait(1);
			else
				wait(3);
			
			turnLEDs(0);
			wait(1); 				// lent tart
		} else if(a[i] == ' '){				
			turnLEDs(0);		// sz�k�z 5 +2
			wait(5);
		}		
	}
	// 1+2 (bet�k�z) v 5+2 (sz�k�z)
	wait(2);
}

void showStringInMorse(char* string){
	for(int i = 0; i < sizeof(string); i++)	
		showCharInMorse(letterToMorse(string[i]));
	
}
			
// Morse_END

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
  MX_ADC1_Init();
  MX_COMP2_Init();
  MX_HDMI_CEC_Init();
  MX_I2C1_Init();
  MX_I2C2_SMBUS_Init();
  MX_I2S1_Init();
  MX_SDADC1_Init();
  MX_SDADC2_Init();
  MX_SPI3_Init();
  MX_TSC_Init();
  MX_USART2_UART_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */
	
  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {		
		showStringInMorse("sos");
  }
	
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_CEC|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_ADC1
                              |RCC_PERIPHCLK_SDADC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.CecClockSelection = RCC_CECCLKSOURCE_HSI;
  PeriphClkInit.SdadcClockSelection = RCC_SDADCSYSCLK_DIV12;
  PeriphClkInit.Adc1ClockSelection = RCC_ADC1PCLK2_DIV2;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_PWREx_EnableSDADC(PWR_SDADC_ANALOG1);
  HAL_PWREx_EnableSDADC(PWR_SDADC_ANALOG2);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
