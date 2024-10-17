/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32c0xx_nucleo.h"
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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t NormalTaskHandle;
osThreadId_t HighTaskHandle;
osThreadId_t LowTaskHandle;
osSemaphoreId_t BinSemHandle;

const osThreadAttr_t NormalTask_attributes = {
  .name = "NormalTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

const osThreadAttr_t HighTask_attributes = {
  .name = "HighTask",
  .priority = (osPriority_t) osPriorityAboveNormal, // 
  .stack_size = 128 * 4
};

const osThreadAttr_t LowTask_attributes = {
  .name = "LowTask",
  .priority = (osPriority_t) osPriorityBelowNormal, // 
  .stack_size = 128 * 4
};
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartNormalTask(void *argument);
void StartHighTask(void *argument);
void StartLowTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  BinSemHandle = osSemaphoreNew(1, 1, NULL);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of NormalTask */
  NormalTaskHandle = osThreadNew(StartNormalTask, NULL, &NormalTask_attributes);

  /* Create the HighTask */
  HighTaskHandle = osThreadNew(StartHighTask, NULL, &HighTask_attributes);

 /* Create the LowTask */
  LowTaskHandle = osThreadNew(StartLowTask, NULL, &LowTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartNormalTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  /* Infinite loop */
  for(;;)
  {
    //BSP_LED_Toggle(LED_GREEN);
		printf("Entered MediumTask\n");
    
		
    printf("Leaving MediumTask\n\n");
    
    osDelay(pdMS_TO_TICKS(500));
  }
  /* USER CODE END defaultTask */
}

/* Second task function */
void StartHighTask(void *argument) {
  for(;;) {
	printf("Entered HighTask and waiting for Semaphore\n");
	

	osSemaphoreAcquire(BinSemHandle, osWaitForever);

	printf("Semaphore acquired by HIGH Task\n");
	

	printf("Leaving HighTask and releasing Semaphore\n\n");
	
    osDelay(pdMS_TO_TICKS(500)); // Delay of 1 second
  }
}
void StartLowTask(void *argument) {
  for(;;) {
		printf("Entered LOWTask and waiting for semaphore\n");
		

		osSemaphoreAcquire(BinSemHandle, osWaitForever);

		printf("Semaphore acquired by LOW Task\n");
		

		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait till the pin go low
    

		printf( "Leaving LOWTask and releasing Semaphore\n\n");
		

		osSemaphoreRelease(BinSemHandle);
    osDelay(pdMS_TO_TICKS(500)); // Delay of 1 second
  }
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

