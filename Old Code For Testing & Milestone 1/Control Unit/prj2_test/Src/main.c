/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2021 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MY_Keypad4x4.h"
#include "lcd16x2.h"
#include <stdbool.h>
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t enter_threshold_msg[26] = {'E', 'n', 't', 'e', 'r', ' ', '#', 'L', 'E', 'D', 's', ' ', 't' , 'h', 'e', 'n', ' ', '#', 'P', 'e', 'o', 'p', 'l', 'e','\n', '\r'};
uint8_t enter_limit_msg[15] = {'E', 'n', 't', 'e', 'r', ' ', '#', 'P', 'e', 'o', 'p', 'l', 'e', '\n', '\r'};
uint8_t done_msg[17] = {'U', 's', 'e', 'r', ' ', 'I', 'n', 'p', 'u', 't', ' ', 'd', 'o' , 'n', 'e', '\n', '\r'};
uint8_t newline[2] = {'\n', '\r'};
uint8_t threshold;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool mySwitches[16];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	Keypad_WiresTypeDef myKeypadStruct;
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	myKeypadStruct.IN0_Port = GPIOB;
	myKeypadStruct.IN1_Port = GPIOB;
	myKeypadStruct.IN2_Port = GPIOB;
	myKeypadStruct.IN3_Port = GPIOB;
	
	myKeypadStruct.OUT0_Port = GPIOA;
	myKeypadStruct.OUT1_Port = GPIOA;
	myKeypadStruct.OUT2_Port = GPIOA;
	myKeypadStruct.OUT3_Port = GPIOA;
	
	myKeypadStruct.IN0pin = GPIO_PIN_3;
	myKeypadStruct.IN1pin = GPIO_PIN_0;
	myKeypadStruct.IN2pin = GPIO_PIN_6;
	myKeypadStruct.IN3pin = GPIO_PIN_7;
	
	myKeypadStruct.OUT0pin = GPIO_PIN_5;
	myKeypadStruct.OUT1pin = GPIO_PIN_6;
	myKeypadStruct.OUT2pin = GPIO_PIN_7;
	myKeypadStruct.OUT3pin = GPIO_PIN_4;
	
	Keypad4x4_Init(&myKeypadStruct);
	
	int bulbsInputted = 0;
	int limitInputted = 0;
	int inputCount = 0;
	
	lcd16x2_init_4bits(GPIOB, GPIO_PIN_4, GPIO_PIN_5,
	GPIOA, GPIO_PIN_8, GPIO_PIN_11, GPIO_PIN_0, GPIO_PIN_1);
	
	HAL_UART_Transmit(&huart2, enter_threshold_msg, sizeof(enter_threshold_msg), HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
//		if (inputCount == 1) {
//			HAL_UART_Transmit(&huart2, newline, sizeof(newline), HAL_MAX_DELAY);
//			HAL_UART_Transmit(&huart2, enter_limit_msg, sizeof(enter_limit_msg), HAL_MAX_DELAY);
////			HAL_Delay(3000);
//		} else 
		if (inputCount == 3) {
			HAL_UART_Transmit(&huart2, newline, sizeof(newline), HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart2, done_msg, sizeof(done_msg), HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart2, newline, sizeof(newline), HAL_MAX_DELAY);
			HAL_Delay(3000);
		}
		// stop receiving over keypad!
		
		lcd16x2_printf("Pressed Key: ");
		lcd16x2_setCursor(2,1);
		
		int i=0;
		for (i=0; i<16; i++) {
			if (mySwitches[i]) {
				switch (i) {
					case 0: threshold = '1';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("1");
					inputCount = inputCount + 1;
					break;
					case 1: threshold = '2';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("2");
					inputCount = inputCount + 1;
					break;
					case 2: threshold = '3';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("3");
					inputCount = inputCount + 1;
					break;
					case 3: threshold = 'A';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);					
					lcd16x2_printf("A");
					inputCount = inputCount + 1;
					break;
					case 4: threshold = '4';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("4");
					inputCount = inputCount + 1;
					break;
					case 5: threshold = '5';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("5");
					inputCount = inputCount + 1;
					break;
					case 6: threshold = '6';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("6");
					inputCount = inputCount + 1;
					break;
					case 7: threshold = 'B';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("B");
					inputCount = inputCount + 1;
					break;
					case 8: threshold = '7';
					break;
					case 9: threshold = '8';
					break;
					case 10: threshold = '9';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("9");
					inputCount = inputCount + 1;
					break;
					case 11: threshold = 'C';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("C");
					inputCount = inputCount + 1;
					break;
					case 12: threshold = NULL; // '*'
					break;
					case 13: threshold = '0';
					break;
					case 14: threshold = '#';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("#");
					inputCount = inputCount + 1;
					break;
					default: threshold = 'D';
//					HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					HAL_UART_Transmit(&huart2, &threshold, sizeof(threshold), HAL_MAX_DELAY);
					lcd16x2_printf("D");
					inputCount = inputCount + 1;
				}
			}
		}

		//HAL_UART_Transmit(&huart1, &threshold, sizeof(threshold), HAL_MAX_DELAY);
		Keypad4x4_ReadKeypad(mySwitches);
		HAL_Delay(100);
		lcd16x2_clear();
		
//		uint8_t buffer;
//		HAL_UART_Transmit(&huart2, &buffer, sizeof(buffer), HAL_MAX_DELAY);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /**Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7
                           PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB3 PB4 PB5
                           PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
