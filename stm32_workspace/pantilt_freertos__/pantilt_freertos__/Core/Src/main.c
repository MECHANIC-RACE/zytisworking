/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "head.h"
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
#define DISTANCE 1000 //???????? ??mm
#define PI 3.141592
#define ANGLE_MAXIMUM_UP 160  //?????????????4095???
#define ANGLE_MAXIMUM_DOWN 300  // ?????????????4095???
#define ANGLE_MAXIMUM_LEFT 400  //?????????????4095???
#define ANGLE_MAXIMUM_RIGHT 400  // ?????????????4095???

/*????*/
__IO uint8_t Reset;
/*??*/
__IO uint8_t Q_NO;

/***target from openmv***/
#ifdef GREEN
//uint8_t Rxbuffer[16];
#endif
#ifdef RED
uint8_t dot1x,dot1y,dot2x,dot2y,dot3x,dot3y,dot4x,dot4y;
int16_t tar_pos1,tar_pos2;
#endif
uint8_t red_x,red_y;



/***Feedback Data***/

/*spe_*/
int16_t spe1;
int16_t spe2;


__IO uint8_t gpio_interupt=0;
PID_t pid_x, pid_y;
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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2,Rxbuffer,16);    
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 20); // arr=100/越尝越亮
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 80); // arr=100
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim3);

  WheelMode(1, 0); // 模弝0：佝置模�? 模弝1：杒速； 模弝2：pwm调�?�；模弝3：步�?
  WheelMode(2, 0); // 模弝0：佝置模�? 模弝1：杒速； 模弝2：pwm调�?�；模弝3：步�?
  WriteSpe(1, 0, 0);
  WriteSpe(2, 0, 0);
  Q_NO = 1;
  pid_init(&pid_x, 10, 0.0, 0.1);
  pid_init(&pid_y, 5, 0.0, 0.1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
   
    #ifdef RED
        if(Q_NO==1)
        {
            /*past??reset???*/
            WheelMode(1, 0);
            WheelMode(2, 0);
            WritePosEx(1, 2350, 1000, 50);
            WritePosEx(2, 2200, 1000, 50); // 复位操作,红光no1
        }
        else if (Q_NO==2)
        {
            /* ???????? */
            WheelMode(1, 0);
            WheelMode(2, 0);
            uint16_t square_size=139;        //???????????
            tar_pos1=2350-square_size;
            tar_pos2=2200+150;
            WritePosEx(1, tar_pos1, 1000, 50);
            WritePosEx(2, tar_pos2, 1000, 50);
            HAL_Delay(3000);
            tar_pos1=2350+square_size;
            tar_pos2=2200+150;
            WritePosEx(1, tar_pos1, 1000, 50);
            WritePosEx(2, tar_pos2, 1000, 50);
            HAL_Delay(3000);
            tar_pos1=2350+square_size;
            tar_pos2=2200-28;
            WritePosEx(1, tar_pos1, 1000, 50);
            WritePosEx(2, tar_pos2, 1000, 50);
            HAL_Delay(3000);
            tar_pos1=2350-square_size;
            tar_pos2=2200-28;
            WritePosEx(1, tar_pos1, 1000, 50);
            WritePosEx(2, tar_pos2, 1000, 50);
            HAL_Delay(3000);
            tar_pos1=2350-square_size;
            tar_pos2=2200+150;
            WritePosEx(1, tar_pos1, 1000, 50);
            WritePosEx(2, tar_pos2, 1000, 50);
            HAL_Delay(3000);
        }
        else if (Q_NO>=3)       //???3?4????
        {
            if(Reset==0)
            {
                for(uint8_t j=0;j<N;j++)
                {
                    dot_cal_x[j]=1.0*j/N*dot2x+1.0*(N-j)/N*dot1x;
                    dot_cal_y[j]=1.0*j/N*dot2y+1.0*(N-j)/N*dot1y;
                }
                for(uint8_t j=0;j<N;j++)
                {
                    dot_cal_x[j+N]=1.0*j/N*dot3x+1.0*(N-j)/N*dot2x;
                    dot_cal_y[j+N]=1.0*j/N*dot3y+1.0*(N-j)/N*dot2y;
                }
                for(uint8_t j=0;j<N;j++)
                {
                    dot_cal_x[j+2*N]=1.0*j/N*dot4x+1.0*(N-j)/N*dot3x;
                    dot_cal_y[j+2*N]=1.0*j/N*dot4y+1.0*(N-j)/N*dot3y;
                }
                for(uint8_t j=0;j<N;j++)
                {
                    dot_cal_x[j+3*N]=1.0*j/N*dot1x+1.0*(N-j)/N*dot4x;
                    dot_cal_y[j+3*N]=1.0*j/N*dot1y+1.0*(N-j)/N*dot4y;
                }
                Reset = 1;
            }
            WheelMode(1, 1);
            WheelMode(2, 1);
            static uint16_t state=0;
            speedServo(dot_cal_x[state], red_x, &pid_x);
            speedServo(dot_cal_y[state], red_y, &pid_y);
            //spe1=-10*(dot_cal_x[state]-red_x);
            //spe2=5*(dot_cal_y[state]-red_y);
            //spe1 = -250;
            //spe2 = -100;
            WriteSpe(1, -1*pid_x.output, 50);
            WriteSpe(2, pid_y.output, 50);
            printf("%f,%f,%f,%f,%f,%f\n", (float)dot_cal_x[state], (float)red_x, (float)dot_cal_y[state], (float)red_y, pid_x.output, pid_y.output);
            //if(abs(dot_cal_x[state]-red_x)<5&&abs(dot_cal_y[state]-red_y)<5) 
            {
                state++;
                if (state == 4 * N) state = 0;
                if(state%N==0) 
                {
                  // if(state==0){
                  //     pid_init(&pid_x,  10, 0.02, 0.01);
                  //     pid_init(&pid_y, 10 , 0.02, 0.01);
                  // }
                  // if (state == N) {
                  //     pid_init(&pid_x, 14 , 0.02, 0.01);//x波动小
                  //     pid_init(&pid_y, 5 , 0.02, 0.01);
                  // }
                  // if (state == 2*N) {
                  //     pid_init(&pid_x, 10 , 0.02, 0.01);
                  //     pid_init(&pid_y, 8 , 0.02, 0.01);
                  // }
                  // if (state == 3*N) {
                  //     pid_init(&pid_x, 10 , 0.02, 0.01);
                  //     pid_init(&pid_y, 5 , 0.02, 0.01);
                  // }
                  HAL_Delay(10);
                }
                
                HAL_Delay(20);
            }
        }
        
    #endif
    #ifdef GREEN
    if(Q_NO>=4)
    {
        // spe1=red_x-80;  //????80?60???, ??????????
        // spe2=red_y-60;
        //spe1?spe2?openmv?????,??????????red??
    }
    
    #endif // DEBUG 
    //HAL_Delay(1);    
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
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

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == RED_NO1_RESET_Pin) // ????
    // ?? ????no1
    {
        gpio_interupt = 1;
        Reset = 1;
        Q_NO  = 1;
        
    }
#ifdef RED

    if (GPIO_Pin == Q_NO2_Pin) // ????
    {
        gpio_interupt = 1;

        Q_NO  = 2;
        
    }
    if (GPIO_Pin == Q_NO3_Pin) // ????
    {
        gpio_interupt = 1;

        Q_NO  = 3;
        
        // U_Transmit(3);
    }
#endif
#ifdef GREEN
    if (GPIO_Pin == Q_NO4_Pin) // ????
    {
        gpio_interupt = 1;

        Q_NO  = 4;
        
        // U_Transmit(4);
    }
#endif
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
