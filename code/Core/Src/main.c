/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include <stdio.h>
#include <stdint.h>
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

#ifdef TASK1
uint8_t task[] = TASK1;
#endif
#ifdef TASK2
uint8_t task[] = TASK2;
#endif
#ifdef TASK3
uint8_t task[] = TASK3;
uint8_t a;
#endif
#ifdef TASK4
uint8_t task[] = TASK4;
#endif
#ifdef TASK5
uint8_t task[] = TASK5;
static uint16_t compare = 0;
uint8_t brightness;
uint8_t bri[4];
#endif
#ifdef TASK6
uint8_t task[] = TASK6;
static uint32_t time = 0;
static uint8_t times = 0;
uint16_t distance = 0;
uint8_t num[7];
#endif
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef TASK3

uint16_t FIBONACCI(uint8_t a);

void uint16_t_to_bin_string(uint16_t value, uint8_t *buf, size_t buf_size);

#endif
#ifdef TASK4

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
#ifdef TASK6

void user_delay_us(uint16_t us);

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
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
    MX_I2C1_Init();
    MX_TIM2_Init();
    MX_TIM1_Init();
    /* USER CODE BEGIN 2 */
#ifndef TASK5
#ifndef TASK4
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
#endif
#ifdef TASK4
    //    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
#endif
#ifdef TASK5
    //    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
#endif
    OLED_init();
    OLED_LOGO();
    HAL_Delay(2000);
#ifndef TASK3
    OLED_operate_gram(PEN_CLEAR);
    OLED_show_string(0, 0, "The current task is:");
    OLED_show_string(1, 0, task);
#endif
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
#ifdef TASK3
        OLED_operate_gram(PEN_CLEAR);
        OLED_show_string(0, 0, "The current task is: TASK3");
//        OLED_show_string(1, 0, task);
#endif
#ifdef TASK1
        FLOWLED();
#endif
#ifdef TASK2
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
            HAL_Delay(80);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
                OLED_show_string(2, 0, "              ");
                OLED_show_string(2, 0, "KEY0 is down!");
                //鍒ゆ柇鎸夐敭鎸変笅
                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET);
                HAL_Delay(80);
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET) {
                    //鍒ゆ柇鎸夐敭鏉惧紑锛屾澗寮?鍚庡弽杞琹ed鐢靛钩
                    HAL_GPIO_TogglePin(GPIOA, 0X00FF);
                    OLED_show_string(2, 0, "             ");
                    OLED_show_string(2, 0, "KEY0 is up!");
                }
            }
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
            HAL_Delay(80);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
                OLED_show_string(2, 0, "              ");
                OLED_show_string(3, 0, "KEY1 is down!");
                //鍒ゆ柇鎸夐敭鎸変笅
                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET);
                HAL_Delay(80);
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_SET) {
                    OLED_show_string(3, 0, "              ");
                    OLED_show_string(3, 0, "KEY1 is up!");
                    //鍒ゆ柇鎸夐敭鏉惧紑锛屾澗寮?鍚庡弽杞琹ed鐢靛钩
                    while (1) {
                        FLOWLED();
                    }
                }
            }
        }
#endif
#ifdef TASK3
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
            HAL_Delay(80);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
                //鍒ゆ柇鎸夐敭鎸変笅
                OLED_show_string(2, 0, "              ");
                OLED_show_string(2, 0, "KEY0 is down!");
                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET);
                HAL_Delay(80);
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET) {
                    //鍒ゆ柇鎸夐敭鏉惧紑锛屾澗寮?鍚庡弽杞琹ed鐢靛钩
                    OLED_show_string(2, 0, "             ");
                    OLED_show_string(2, 0, "KEY0 is up!");
                    uint8_t str0[4];
                    uint8_t str1[17];
                    uint8_t str2[4];
                    for (a = 1;
                         FIBONACCI(a) <= 0x00FF; a++) {
                        //浠呭湪椤规暟鍊煎湪1-255鏃朵寒璧峰寲涓轰簩杩涘埗鏃剁浉搴旂殑LED
                        HAL_GPIO_TogglePin(GPIOA, FIBONACCI(a));
                        sprintf(str0, "%d", FIBONACCI(a));
                        sprintf(str2, "%d", a);
                        uint16_t_to_bin_string(FIBONACCI(a), str1, sizeof(str1));
                        // 将整数转为二进制字符串
                        OLED_show_string(3, 0, "The binary num is:");
                        OLED_show_string(4, 0, str1);
                        OLED_show_string(1, 10, "Num:");
                        OLED_show_string(1, 15, str0);
                        OLED_show_string(2, 12, "Time:");
                        OLED_show_string(2, 17, str2);
                        HAL_Delay(1000);
                        HAL_GPIO_TogglePin(GPIOA, FIBONACCI(a));
                    }
                }
            }
        }
#endif
#ifdef TASK4
        uint8_t brightness;
        uint8_t bri[4];
        uint16_t i = 0;
        for (; i + 40 <= 1000;) {
            i += 40;
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
//            HAL_Delay(1);
            OLED_show_string(2, 0, "The brightness is:");
            brightness = i / 10;
            sprintf(bri, "%d", brightness);
            OLED_show_string(3, 0, bri);
            OLED_show_string(3, 3, "%");
        }
        HAL_Delay(200);
        OLED_show_string(3, 2, " ");
        for (; i - 40 >= 0;) {
            i -= 40;
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
//            HAL_Delay(1);
            OLED_show_string(2, 0, "The brightness is:");
            brightness = i / 10;
            if (brightness < 10) {
                OLED_show_string(3, 1, " ");
            }
            sprintf(bri, "%d", brightness);
            OLED_show_string(3, 0, bri);
            OLED_show_string(3, 3, "%");
        }
        HAL_Delay(200);
#endif
#ifdef TASK5
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
            HAL_Delay(80);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {           //鍒ゆ柇鎸夐敭鎸変笅
                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
                    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
                        if ((compare + 25) < 1000) {
                            compare += 25;
                            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, compare);
//                            HAL_Delay(3);
                            OLED_show_string(2, 0, "The brightness is:");
                            brightness = compare / 10;
                            sprintf(bri, "%d", brightness);
                            OLED_show_string(3, 0, bri);
                            OLED_show_string(3, 3, "%");
                        }
                    }
                    HAL_Delay(80);
                }
            }
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
            HAL_Delay(80);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {           //鍒ゆ柇鎸夐敭鎸変笅
                while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
                    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
                        if ((compare - 25) > 0) {
                            compare -= 25;
                            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, compare);
//                            HAL_Delay(3);
                            OLED_show_string(2, 0, "The brightness is:");
                            brightness = compare / 10;
                            if (brightness < 10) {
                                OLED_show_string(3, 1, " ");
                            }
                            sprintf(bri, "%d", brightness);
                            OLED_show_string(3, 2, " ");
                            OLED_show_string(3, 0, bri);
                            OLED_show_string(3, 3, "%");
                        }
                    }
                    HAL_Delay(80);
                }
            }
        }
#endif
#ifdef TASK6
//        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
//        HAL_Delay(1);
//        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
//        time = 0;
//        while (1) {
//            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
//                time = HAL_GetTick() - time;
//                while (1) {
//                    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
//                        time = HAL_GetTick() - time;
//                        break;
//                    }
//                }
//                break;
//            }
//        }
// 开始测距
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);  // trig引脚置高
        HAL_Delay(1);  // 持续至少10us
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); // trig引脚置低

        // 等待echo上升沿
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET);

        // 重置定时器
        __HAL_TIM_SET_COUNTER(&htim1, 0);

        // 等待echo下降沿
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET);

        // 读取定时器值
        time = __HAL_TIM_GET_COUNTER(&htim1);

        // 计算距离 (假设声速为340m/s)
        distance = time * 0.017; // 时间转为秒并计算距离

        // 在此可以添加代码将distance值输出到某个显示设备或串口打印出来。
//        distance = time * 17;
        sprintf(num, "%d", distance);
        OLED_show_string(2, 0, "Distance:");
        OLED_show_string(2, 10, "     ");
        OLED_show_string(2, 10, num);
        OLED_show_string(2, 15, "cm");
#endif
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
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
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }

    /** Enables the Clock Security System
    */
    HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
#ifdef TASK3

uint16_t FIBONACCI(uint8_t a) {
    uint16_t b = 1, c = 1, d = 0;
    /**娉ㄦ剰鍙橀噺绫诲瀷鐨勫ぇ灏忥紝鍙兘澶т笉鑳藉皬锛屽惁鍒欎細杈撳嚭闅忔満鑼冨洿鏁帮紒
    */
    if (a == 1) {
        return 1;
    } else if (a == 2) {
        return 1;
    } else if (a > 2) {
        for (int j = 2; j < a; j++) {
            d = b + c;
            b = c;
            c = d;
        }
        return c;
    } else {
        return 0;
    }
}

//将16位十进制数转成二进制字符串
void uint16_t_to_bin_string(uint16_t value, uint8_t *buf, size_t buf_size) {
    for (size_t i = 0; i < buf_size - 1; ++i) {
        buf[i] = (value >> (15 - i)) & 1 ? '1' : '0';
    }
    buf[buf_size - 1] = '\0';
}

#endif
#ifdef TASK4

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim == &htim2) {
//        //500ms trigger
//        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//    }
//}

#endif
#ifdef TASK6

void user_delay_us(uint16_t us) {
    for (; us > 0; us--) {
        for (uint8_t i = 50; i > 0; i--);
    }
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//    if (times == 2) {
//        times = 0;
//        time = 0;
//    }
//    time = HAL_GetTick() - time;
//    times++;
//}
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim == &htim2) {
//        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
//        user_delay_us(100);
//        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
//    }
//}

#endif
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
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
