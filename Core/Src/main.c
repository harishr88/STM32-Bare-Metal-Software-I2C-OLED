/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define sclhigh()  (GPIOA->BSRR = (1 << 0))
#define scllow()   (GPIOA->BSRR = (1 << 16))

#define sdahigh()  (GPIOA->BSRR = (1 << 1))
#define sdalow()   (GPIOA->BSRR = (1 << 17))

#define sdaread()  (GPIOA->IDR & (1<<1))
#define timeout()  (GPIOC->ODR |= (1<<13))
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
volatile uint8_t ackflag = 0;
volatile uint8_t ackcount = 0;
volatile uint8_t movflag = 0;
uint8_t oleddata[1024];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
void delay(uint32_t  time);
void i2cdelay(void);
void start(void);
void stop(void);
void oledsetcursor(uint8_t page, uint8_t col);
void transmit(char byte);
void oledinit(char address);
void oledclear(char address);
void oledset(char address);
void oledwrite(uint8_t page, uint8_t col, uint8_t *bitmap, uint8_t len);
void oledpageclear(char address, uint8_t page);
void oledpageset(char address, uint8_t page);
void moveright(char address);
void moveleft(char address);
void rotateleft(char address);
void rotateright(char address);
void upoleddata(uint8_t page , uint8_t col, uint8_t *bitmap, uint8_t len);
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
  /* USER CODE BEGIN 2 */
  oledinit(0x78);

  oledset(0x78);
  oledclear(0x78);

  uint8_t H_bitmap[5] = {0x7F,0x08,0x08,0x08,0x7F};
  uint8_t A_bitmap[5] = {0x7E,0x11,0x11,0x11,0x7E};
  uint8_t R_bitmap[5] = {0x7F,0x09,0x19,0x29,0x46};
  uint8_t I_bitmap[5] = {0x00,0x41,0x7F,0x41,0x00};
  uint8_t S_bitmap[5] = {0x46,0x49,0x49,0x49,0x31};

  uint8_t vhline_bitmap[] = {0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80, 0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};


  oledwrite(0, 0, H_bitmap, sizeof(H_bitmap));
  oledwrite(0, 8, A_bitmap, sizeof(H_bitmap));
  oledwrite(0, 16, R_bitmap, sizeof(H_bitmap));
  oledwrite(0, 24, I_bitmap, sizeof(H_bitmap));
  oledwrite(0, 32, S_bitmap, sizeof(H_bitmap));
  oledwrite(0, 40, H_bitmap, sizeof(H_bitmap));



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	 // moveright(0x78);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void start(void)
{
	sclhigh();
	sdahigh();
	i2cdelay();
	sdalow();
	i2cdelay();
	scllow();
}

void transmit(char byte)
{
	uint32_t time;

	for(uint8_t i = 8; i>0 ; i--)
	{

		scllow();
		i2cdelay();
		(byte & (1 << (i-1)))? sdahigh():sdalow();
		sclhigh();
		i2cdelay();
		scllow();

	}

	sdahigh(); //ack
	sclhigh();
	i2cdelay();

	time = HAL_GetTick();
	while (sdaread() && ((HAL_GetTick()-time) < 100));

	if(sdaread())		timeout();
	else
	{
		ackflag = 1;
		ackcount++;

	}
	scllow();

}


void stop(void)
{
	sdalow();
	scllow();
	sclhigh();
	i2cdelay();
	sdahigh();

}

void i2cdelay(void)
{
    for(volatile int16_t i=0;i<200;i++);
}

void delay(uint32_t time)
{
	uint32_t now = HAL_GetTick();

    while(HAL_GetTick() - now < time);
}

void oledinit(char address)
{
	start();
	transmit(address);
	transmit(0x00);
	transmit(0xA8);
	transmit(0x3F);
	transmit(0xD3);
	transmit(0x00);
	transmit(0x40);
	transmit(0xA1);
	transmit(0xC8);
	transmit(0xDA);
	transmit(0x12);
	transmit(0x81);
	transmit(0x7F);
	transmit(0xA4);
	transmit(0xA6);
	transmit(0xD5);
	transmit(0x80);
	transmit(0x8D);
	transmit(0x14);
	transmit(0xAF);
	transmit(0x20);
	transmit(0x00);   // Horizontal addressing mode
	stop();
}

void oledsetcursor(uint8_t page, uint8_t col)
{
    start();
    transmit(0x78);
    transmit(0x00);   // command mode
    transmit(0x21);   // column address
    transmit(col);    // start column
    transmit(0x7F);   // end column
    transmit(0x22);   // page address
    transmit(page);   // start page
    transmit(page);   // end page
    stop();
}

void oledwrite(uint8_t page, uint8_t col, uint8_t *bitmap, uint8_t len)
{
    oledsetcursor(page, col);
    upoleddata(page,col,bitmap,len);
    start();
    transmit(0x78);
    transmit(0x40);   // data mode
    for(int i = 0; i < len; i++)
        transmit(bitmap[i]);
    stop();
}

void oledclear(char address)
{
    // Set page and column address to start
    start();
    transmit(address);   // address
    transmit(0x00);   // command mode
    transmit(0x21);   // set column address
    transmit(0x00);   // start column 0
    transmit(0x7F);   // end column 127
    transmit(0x22);   // set page address
    transmit(0x00);   // start page 0
    transmit(0x07);   // end page 7
    stop();

    // Fill entire display with 0x00 (black)
    start();
    transmit(0x78);   // address
    transmit(0x40);   // data mode
    for(int i = 0; i < 1024; i++)  // 128×64/8 = 1024 bytes
    {
        transmit(0x00);
        oleddata[i] = 0x00;
    }
    stop();
}

void oledset(char address)
{
    // Set page and column address to start
    start();
    transmit(address);   // address
    transmit(0x00);   // command mode
    transmit(0x21);   // set column address
    transmit(0x00);   // start column 0
    transmit(0x7F);   // end column 127
    transmit(0x22);   // set page address
    transmit(0x00);   // start page 0
    transmit(0x07);   // end page 7
    stop();

    // Fill entire display with 0x00 (black)
    start();
    transmit(0x78);   // address
    transmit(0x40);   // data mode
    for(int i = 0; i < 1024; i++)  // 128×64/8 = 1024 bytes
    {
        transmit(0xFF);
        oleddata[i] = 0xFF;
    }
    stop();
}


void oledpageclear(char address, uint8_t page)
{
	start();
	transmit(address);
	transmit(0x00);
	transmit(0x22);   // set page address
	transmit(page);   // start page 0
	transmit(page);   // end page
	transmit(0x21);   // set column address
	transmit(0x00);   // start column 0
	transmit(0x7F);   // end column 127
	stop();

	start();
	transmit(address);

	uint8_t bitmap[128];
	for(int i = 0 ; i<128 ; i++)
	{
		bitmap[i] = 0x00;
	}
	upoleddata(page,0,bitmap,128);

	transmit(0x40);
	for(int i = 0; i<128 ; i++)
	{
		transmit(0x00);
	}
	stop();

}

void oledpageset(char address, uint8_t page)
{
	start();
	transmit(address);
	transmit(0x00);
	transmit(0x22);   // set page address
	transmit(page);   // start page 0
	transmit(page);   // end page
	transmit(0x21);   // set column address
	transmit(0x00);   // start column 0
	transmit(0x7F);   // end column 127
	stop();

	start();
	transmit(address);
	transmit(0x40);
	for(int i = 0; i<128 ; i++)
	{
		transmit(0xFF);
	}
	stop();

	uint8_t bitmap[128];
	for(int i = 0 ; i<128 ; i++)
	{
		bitmap[i] = 0xFF;
	}
	upoleddata(page,0,bitmap,128);

}

void upoleddata(uint8_t page, uint8_t col, uint8_t *bitmap, uint8_t len)
{
    uint16_t index = (page * 128) + col;

    for(uint16_t i = 0; i < len; i++)
    {
        oleddata[index + i] = bitmap[i];
    }
}

void moveright(char address)
{
	movflag++;
	static uint8_t data[1024] = {0x00};

	for(int8_t i=0 ; i<8 ; i++)
	{
		for(int16_t j=0 ; j<128 ;j++)
		{
			int16_t index = (i*128) + j;
			if(j == 127) data[index] = oleddata[i*128];
			else data[index] = oleddata[index+1];

		}
	}

	oledclear(0x78);
	oledsetcursor(0,0);

	start();
	transmit(address);   // address
	transmit(0x00);   // command mode
	transmit(0x21);   // set column ad dress
	transmit(0x00);   // start column 0
	transmit(0x7F);   // end column 127
	transmit(0x22);   // set page address
	transmit(0x00);   // start page 0
	transmit(0x07);   // end page 7
	stop();

	start();
	transmit(address);
	transmit(0x40);

	for (int16_t i = 0; i<1024 ; i++)
	{
		transmit(data[i]);
		oleddata[i] = data[i];
	}

	stop();


}

void rotateright(char address)
{
	while(1)
	{
		moveright(address);
		delay(2000);
	}

}

void moveleft(char address)
{
	uint8_t data[1024] = {0x00};

	oledsetcursor(0,0);
	start();
	transmit(address);
	transmit(0x40);

	for(int16_t i=1023 ; i>=0 ; i--)
	{
		if(i == 0)	data[i] = data[1023];
		else	data[i] = oleddata[i-1];

	}

	for (int16_t i = 0; i<1024 ; i++)	transmit(data[i]);

	stop();
}

void rotateleft(char address)
{
	while(1)
	{
		moveleft(address);
		delay(500);
	}

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
