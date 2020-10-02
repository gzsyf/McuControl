/**
  ******************************************************************************
  * File Name          : pca9685.h
  * Description        : This file provides code for the configuration
  *                      of the pca9685 instances.
  ******************************************************************************
  * @attention
  *
  * chip:  	STM32F10.  
  * date:  	2020年10月3日
  * pin: 	io口连接：SCL --PB6   SDA -- PB7  vcc -- 3.3V  V+ -- 5V
  * frequency:  
  * note:
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32PCA9685_H
#define __STM32PCA9685_H	
#ifdef __cplusplus
 extern "C" {
#endif

/* USER CODE BEGIN Includes --------------------------------------------------*/
#include "main.h"
/* USER CODE END Includes ----------------------------------------------------*/

/* USER CODE BEGIN Exported types --------------------------------------------*/
/* USER CODE END Exported types ----------------------------------------------*/


/* USER CODE BEGIN Private defines -------------------------------------------*/
#define pca_adrr 0x80	// PCA9685地址

/**
  * Description: PCA9685寄存器地址
  * Attention:
  */  
#define pca_mode1 0x0  	// MODE1寄存器地址
#define pca_pre 0xFE	// pca_pre 寄存器地址
#define LED0_ON_L 0x6	// LED0_ON_L 寄存器地址
#define LED0_ON_H 0x7	// LED0_ON_H 寄存器地址
#define LED0_OFF_L 0x8	// LED0_OFF_L 寄存器地址
#define LED0_OFF_H 0x9	// LED0_OFF_H 寄存器地址

/**
  * Description: 计算值
  * Attention:
  */  
#define jdMIN  115 // minimum
#define jdMAX  590 // maximum
#define jd000  130 //0度对应4096的脉宽计数值
#define jd180  520 //180度对应4096的脉宽计算值

/* USER CODE END Private defines ---------------------------------------------*/


/* USER CODE BEGIN Prototypes ------------------------------------------------*/
void PCA_MG9XX_Init(float hz,u8 angle);
void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed);
/* USER CODE END Prototypes --------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__ XXX_H */

/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/












