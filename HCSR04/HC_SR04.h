/**
  ******************************************************************************
  * File Name          : XXXXXX.h
  * Description        : This file provides code for the configuration
  *                      of the XXXXX instances.
  ******************************************************************************
  * @attention
  *
  * chip:  XXXXXXchip.  
  * date:  XX.XX.XX
  * pin:
  * frequency:  
  * note:
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HCSR_H
#define __HCSR_H
#ifdef __cplusplus
 extern "C" {
#endif

/* USER CODE BEGIN Includes --------------------------------------------------*/
#include "main.h"

/* USER CODE END Includes ----------------------------------------------------*/

/* USER CODE BEGIN Exported types --------------------------------------------*/
/* USER CODE END Exported types ----------------------------------------------*/


/* USER CODE BEGIN Private defines -------------------------------------------*/

#define TIMER TIM2
#define TIMER_RCC RCC_APB1Periph_TIM2

#define TRIG_GPIO_RCC RCC_APB2Periph_GPIOB  
#define TRIG_GPIO_PORT GPIOB 
#define TRIG_GPIO_PIN GPIO_Pin_0

#define ECHO_GPIO_RCC RCC_APB2Periph_GPIOB  
#define ECHO_GPIO_PORT GPIOB 
#define ECHO_GPIO_PIN GPIO_Pin_1

#define TRIG_CLR() GPIO_ResetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN)
#define TRIG_SET() GPIO_SetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN)

#define READ_ECHO() GPIO_ReadInputDataBit(ECHO_GPIO_PORT, ECHO_GPIO_PIN)
/* USER CODE END Private defines ---------------------------------------------*/


/* USER CODE BEGIN Prototypes ------------------------------------------------*/
void configHcsrIO(void);
void configHcsrTIM(void);
float getDistance(void);

/* USER CODE END Prototypes --------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__ XXX_H */

/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/
