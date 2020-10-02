/**
  ******************************************************************************
  * File Name          : DHT11.h
  * Description        : DHT11 温湿度传感
  ******************************************************************************
  * @attention
  *
  * chip:  stm32F103c8t6.  
  * date:  XX.XX.XX
  * pin:   dat -> PB11
  * frequency:  72MHz 
  * note:
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DHT11_H
#define __DHT11_H
#ifdef __cplusplus
 extern "C" {
#endif

/* USER CODE BEGIN Includes --------------------------------------------------*/
#include "main.h"
/* USER CODE END Includes ----------------------------------------------------*/


/* USER CODE BEGIN Exported types --------------------------------------------*/
/* USER CODE END Exported types ----------------------------------------------*/


/* USER CODE BEGIN Private defines -------------------------------------------*/
#define DHT11_IO 		GPIOB      		/* 设置GPIO脚，默认为PB11 */
#define DHT11_PIN		GPIO_Pin_11
/* USER CODE END Private defines ---------------------------------------------*/


/* USER CODE BEGIN Prototypes ------------------------------------------------*/
u8 DHT11_Init(void);					/* 初始化函数，如果DHT11存在响应则返回1，否则0 */
u8 DHT11_Read_Data(u8 *temp,u8 *humi);  /* 从DHT11读取数据，没有小数部分 */
/* USER CODE END Prototypes --------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif /*__ XXX_H */

/********************************* REFERENCE ***********************************
 * [1] code come from
 * https://blog.csdn.net/qq_38203996/article/details/103328291?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-5.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-5.channel_param
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/


