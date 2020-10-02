/**
  ******************************************************************************
  * File Name          : DHT11.h
  * Description        : DHT11 ��ʪ�ȴ���
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
#define DHT11_IO 		GPIOB      		/* ����GPIO�ţ�Ĭ��ΪPB11 */
#define DHT11_PIN		GPIO_Pin_11
/* USER CODE END Private defines ---------------------------------------------*/


/* USER CODE BEGIN Prototypes ------------------------------------------------*/
u8 DHT11_Init(void);					/* ��ʼ�����������DHT11������Ӧ�򷵻�1������0 */
u8 DHT11_Read_Data(u8 *temp,u8 *humi);  /* ��DHT11��ȡ���ݣ�û��С������ */
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


