/**
  ******************************************************************************
  * File Name          : delay.h
  * Description        : This file provides code for the configuration
  *                      of the XXXXX instances.
  ******************************************************************************
  * @attention
  *
  * chip:   			stm32f103c8t6 chip.  
  * date:   			2020.3.27
  * pin: 					None
  * frequency: 	 	72MHz
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H
#ifdef __cplusplus
 extern "C" {
#endif

/* USER CODE BEGIN Includes --------------------------------------------------*/
#include "main.h"
/* USER CODE END Includes ----------------------------------------------------*/

/* USER CODE BEGIN Exported types --------------------------------------------*/
/* USER CODE END Exported types ----------------------------------------------*/


/* USER CODE BEGIN Private defines -------------------------------------------*/
/* USER CODE END Private defines ---------------------------------------------*/


/* USER CODE BEGIN Prototypes ------------------------------------------------*/
void delayUs(u32 num);
void delayMs(u32 num);
/* USER CODE END Prototypes --------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__ XXX_H */


/********************************* REFERENCE ***********************************
 * [1] code come from
 * https://blog.csdn.net/qq_35874273/article/details/78508927?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-8&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-8
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/
