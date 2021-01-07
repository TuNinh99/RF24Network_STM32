#include "main.h"

const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};
char Bluetooth_Rx_data[2]; //receive data from  smartphone
char NRF24_Rx_data[32]; //receive data from Node
char feedback[32];
int mess;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);

/*Function Setup*/
void Setup_NRF24_Address(uint64_t address_Read, uint64_t address_Write);
void Setup(void);

uint64_t TxpipeAddrs[] = {0x00, 0x01, 0x02, 0x03};

char* lcd_Node[] = {"Lamp:", "Fan:", "Tivi:"};
char* state[] = {"ON ", "OFF"};
	
int main(void)
{
  HAL_Init();
	
  SystemClock_Config();

  MX_GPIO_Init();

  MX_SPI1_Init();
  MX_USART2_UART_Init();
	
	/*Cai dat LCD*/
	lcd16x2_init_4bits(GPIOB, rs_lcd_Pin, en_lcd_Pin, GPIOA, d4_lcd_Pin, d5_lcd_Pin, d6_lcd_Pin, d7_lcd_Pin);
	lcd16x2_clear();
	lcd16x2_setCursor(0, 0);
	lcd16x2_printf(lcd_Node[0]);
	lcd16x2_setCursor(0, 5);
	lcd16x2_printf(state[1]);
	
	lcd16x2_setCursor(0, 9);
	lcd16x2_printf(lcd_Node[1]);
	lcd16x2_setCursor(0, 13);
	lcd16x2_printf(state[1]);
	
	lcd16x2_setCursor(1, 4);
	lcd16x2_printf(lcd_Node[2]);
	lcd16x2_setCursor(1, 9);
	lcd16x2_printf(state[1]);
	
	lcd16x2_cursorShow(false);
					
	Setup();
	Setup_NRF24_Address(TxpipeAddrs[0], TxpipeAddrs[1]);
	Setup_NRF24_Address(TxpipeAddrs[0], TxpipeAddrs[2]);
	Setup_NRF24_Address(TxpipeAddrs[0], TxpipeAddrs[3]);
	
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, low);
  while (1)
  {
		HAL_UART_Receive(&huart2, (uint8_t*)Bluetooth_Rx_data, 1, 10);
		
		switch(Bluetooth_Rx_data[0])
		{
			case '0':
				NRF24_openWritingPipe(TxpipeAddrs[1]);
				HAL_Delay(5);
				NRF24_stopListening();		
				mess = 0;
				NRF24_write(&mess, 32);
			
				NRF24_startListening();
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
				
				if(NRF24_available()) 
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 0)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, high);							
						lcd16x2_setCursor(0 ,5);
						lcd16x2_printf(state[0]);
					}
				}
			break;		
				
			case '1':
				NRF24_openWritingPipe(TxpipeAddrs[1]);
				HAL_Delay(5);
				NRF24_stopListening();
				mess = 1;
				NRF24_write(&mess, 32);

				NRF24_startListening();			
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
			
				if(NRF24_available())
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 1)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, low);
						lcd16x2_setCursor(0 ,5);
						lcd16x2_printf(state[1]);
					}
				}
				break;
				
			case '2':
				NRF24_openWritingPipe(TxpipeAddrs[2]);
				HAL_Delay(5);
				NRF24_stopListening();		
				mess = 0;
				NRF24_write(&mess, 32);
			
				NRF24_startListening();
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
				
				if(NRF24_available()) 
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 0)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, high);							
						lcd16x2_setCursor(0 ,13);
						lcd16x2_printf(state[0]);
					}
				}
			break;		
				
			case '3':
				NRF24_openWritingPipe(TxpipeAddrs[2]);
				HAL_Delay(5);
				NRF24_stopListening();
				mess = 1;
				NRF24_write(&mess, 32);

				NRF24_startListening();			
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
			
				if(NRF24_available())
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 1)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, low);
						lcd16x2_setCursor(0 ,13);
						lcd16x2_printf(state[1]);
					}
				}
				break;
				
			case '4':
				NRF24_openWritingPipe(TxpipeAddrs[3]);
				HAL_Delay(5);
				NRF24_stopListening();		
				mess = 0;
				NRF24_write(&mess, 32);
			
				NRF24_startListening();
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
				
				if(NRF24_available()) 
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 0)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, high);							
						lcd16x2_setCursor(1 ,9);
						lcd16x2_printf(state[0]);
					}
				}
			break;		
				
			case '5':
				NRF24_openWritingPipe(TxpipeAddrs[3]);
				HAL_Delay(5);
				NRF24_stopListening();
				mess = 1;
				NRF24_write(&mess, 32);

				NRF24_startListening();			
				NRF24_openReadingPipe(1, TxpipeAddrs[0]);
				HAL_Delay(5);
			
				if(NRF24_available())
				{
					NRF24_read(&feedback, 32);
					if(feedback[0] == 1)
					{
						HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, low);
						lcd16x2_setCursor(1 ,9);
						lcd16x2_printf(state[1]);
					}
				}
				break;
			default: break;
		}
	}
}

void Setup(void){
	NRF24_begin(GPIOA, CSN_Pin, CE_Pin, hspi1);
	NRF24_setAutoAck(false);
	NRF24_setChannel(52);						
	NRF24_setPayloadSize(32);
	NRF24_setPALevel(RF24_PA_0dB); 
}

void Setup_NRF24_Address(uint64_t address_Read, uint64_t address_Write) 
{
	NRF24_openReadingPipe(1, address_Read);
	NRF24_openWritingPipe(address_Write);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CSN_Pin|CE_Pin|d4_lcd_Pin|d5_lcd_Pin
                          |d6_lcd_Pin|d7_lcd_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, rs_lcd_Pin|rw_lcd_Pin|en_lcd_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CSN_Pin CE_Pin d4_lcd_Pin d5_lcd_Pin
                           d6_lcd_Pin d7_lcd_Pin */
  GPIO_InitStruct.Pin = CSN_Pin|CE_Pin|d4_lcd_Pin|d5_lcd_Pin
                          |d6_lcd_Pin|d7_lcd_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : rs_lcd_Pin rw_lcd_Pin en_lcd_Pin */
  GPIO_InitStruct.Pin = rs_lcd_Pin|rw_lcd_Pin|en_lcd_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
