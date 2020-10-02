/**
  ******************************************************************************
  * File Name          : OLED_I2C.h
  * Description        : This file provides code for the configuration
  *                      of the OLED_I2C instances.
  ******************************************************************************
  * @attention
  *
  * chip:  stm32c8t6chip.  
  * date:  XX.XX.XX
  * pin:   PB6 -> SCL  PB7 -> SDA
  * frequency:  72MHz
  * note: 本模块采用i2c的oled
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OLED_I2C_H
#define __OLED_I2C_H
#ifdef __cplusplus
 extern "C" {
#endif


/* USER CODE BEGIN Includes --------------------------------------------------*/
#include "main.h"
/* USER CODE END Includes ----------------------------------------------------*/
	 
/* USER CODE BEGIN Exported types --------------------------------------------*/
/* USER CODE END Exported types ----------------------------------------------*/
	 
/* USER CODE BEGIN Private defines -------------------------------------------*/
#define OLED_ADDRESS	0x78	/* 通过调整0R电阻,屏可以0x78和0x7A两个地址 
								 * 默认0x78 
								 */
/* USER CODE END Private defines ---------------------------------------------*/
	 
/* USER CODE BEGIN Prototypes ------------------------------------------------*/
void OLED_Init(void); /* OLED初始化函数 */
void OLED_SetPos(unsigned char x, unsigned char y); 
					  /* 设置起始光标函数 */
void OLED_Fill(unsigned char fill_Data); /* 全屏布满函数 */
void OLED_CLS(void);  /* 清屏函数 */
void OLED_ON(void);   /* OLED唤醒 */
void OLED_OFF(void);  /* OLED休眠 */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
					  /* 显示codetab.h中的ASCII字符 */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
					  /* 显示codetab.h中的汉字 */
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
					  /* 显示BMP位图 */
/* USER CODE END Prototypes --------------------------------------------------*/


#ifdef __cplusplus
}
#endif
#endif /*__OLED_I2C_H */

/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/



