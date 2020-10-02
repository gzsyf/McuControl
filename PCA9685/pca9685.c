/**
  ******************************************************************************
  * File Name          : pca9685.c
  * Description        : This file provides code for the configuration
  *                      of the 16路舵机驱动模块 instances.
  ******************************************************************************
  * @attention
  *
  * chip:  	stm32F10.  
  * date:  	2020年10月2日
  * pin: 	SCL --PB6   SDA -- PB7  vcc -- 3.3V  V+ -- 5V
  * frequency: 72MHz
  * note:
  *
  ******************************************************************************
  */
 
/* USER INCLUDES CODE BEGIN --------------------------------------------------*/
#include "pca9685.h"
#include "delay.h"
#include "math.h"
#include "iic.h"
/* USER INCLUDES CODE END ----------------------------------------------------*/

/* USER GLOBAL VARIABLE BEGIN ------------------------------------------------*/
/* USER GLOBAL VARIABLE END --------------------------------------------------*/

/* USER INIT CODE BEGIN ------------------------------------------------------*/
/* USER INIT CODE END --------------------------------------------------------*/

/* USER STATIC CODE BEGIN ----------------------------------------------------*/
/**
  * @file   向PCA写数据
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  adrrd:地址
  *         data:数据
  * @retval None
  * @date 
  */
void pca_write(u8 adrr,u8 data){ 
	I2C_Start();
	I2C_SendByte(pca_adrr);
	I2C_SendByte(adrr);
	I2C_SendByte(data);
	I2C_Stop();
}


/**
  * @file   从PCA读数据
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  adrrd:地址
  * @retval u8:数据
  * @date 
  */
u8 pca_read(u8 adrr){
	u8 data;
	I2C_Start();
	I2C_SendByte(pca_adrr);
	I2C_SendByte(adrr);
	I2C_Start();
	I2C_SendByte(pca_adrr|0x01);
	data=I2C_ReceiveByte(0);
	I2C_Stop();
	return data;
}


/**
  * @file   设置PWM频率
  * @brief  同时也设置PCAmode1寄存器
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  freq:频率
  * @retval None
  * @date 
  */
void pca_setfreq(float freq){
	u8 prescale,oldmode,newmode;
	double prescaleval;
	freq *= 0.92;  // 可能是补偿把*0.92
	prescaleval = 25000000;  // 25MHz
	prescaleval /= 4096;     
	prescaleval /= freq;
	prescaleval -= 1;
	prescale =floor(prescaleval + 0.5f); // 计算公式是根据PCA9685 PRE_SCALE寄存器

	oldmode = pca_read(pca_mode1);   // 读mode1寄存器
	newmode = (oldmode&0x7F) | 0x10; // 进入sleep模式才能修改IC频率
	pca_write(pca_mode1, newmode); 	 // 向IC写入sleep模式
	pca_write(pca_pre, prescale); 	 // 向IC设置频率
	pca_write(pca_mode1, oldmode);
	delayMs(2);

	pca_write(pca_mode1, oldmode | 0xa1); 
}


/**
  * @file   设置PWM占空比
  * @brief  一个PWM周期分成4096份，on是高电平的计数值，off是低电平的计数值，两者相加为4096
  *			当on等于0时，off/4096的值就是PWM的占空比
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  num:舵机PWM输出引脚0~15
  *			on:PWM上升计数值0~4096
  *			off:PWM下降计数值0~4096
  * @retval None
  * @date 
  */
void pca_setpwm(u8 num, u32 on, u32 off){
	/* 下面是写LED0_ON_L LED0_ON_H LED0_OFF_L LED0_OFF_H 寄存器 */
	pca_write(LED0_ON_L+4*num,on);
	pca_write(LED0_ON_H+4*num,on>>8);
	pca_write(LED0_OFF_L+4*num,off);
	pca_write(LED0_OFF_H+4*num,off>>8);
}
/* USER STATIC CODE END ------------------------------------------------------*/


/* USER EXTERN CODE BEGIN ----------------------------------------------------*/
/**
  * @file   初始化舵机驱动板
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  hz:PWM频率
  *			angle:初始化舵机角度
  * @retval None
  * @date 
  */
void PCA_MG9XX_Init(float hz,u8 angle){
	u32 off=0;
	I2C_Configuration();
	pca_write(pca_mode1,0x0);
	pca_setfreq(hz);//设置PWM频率
	off=(u32)(145+angle*2.4);
	/* 初始化设置PWM占空比都是0% */
	pca_setpwm(0,0,off);pca_setpwm(1,0,off);pca_setpwm(2,0,off);pca_setpwm(3,0,off);
	pca_setpwm(4,0,off);pca_setpwm(5,0,off);pca_setpwm(6,0,off);pca_setpwm(7,0,off);
	pca_setpwm(8,0,off);pca_setpwm(9,0,off);pca_setpwm(10,0,off);pca_setpwm(11,0,off);
	pca_setpwm(12,0,off);pca_setpwm(13,0,off);pca_setpwm(14,0,off);pca_setpwm(15,0,off);
	delayMs(500);
}


/**
  * @file   控制舵机转动
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  num:输出端口，可选0~15
  *			start_angle:起始角度，可选0~180
  *			end_angle:结束角度，可选0~180
  *			mode:模式选择， 0 表示函数内无延时，调用时需要在函数后另外加延时函数，且不可调速，第五个参数可填任意值；
  *							1 表示函数内有延时，调用时不需要在函数后另外加延时函数，且不可调速，第五个参数可填任意值；
  *							2 表示速度可调，第五个参数表示速度值；
  *			speed:速度，可填大于 0 的任意值，填 1 时速度最快，数值越大，速度越小；模式 0和1 的速度比模式 2 的最大速度大；
  * @retval None
  * @date 
  */
void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed){
	u8 i;
	u32 off=0;
	switch(mode){
		case 0:
			off=(u32)(158+end_angle*2.2);
			pca_setpwm(num,0,off);
			break;
		case 1:
			off=(u32)(158+end_angle*2.2);
			pca_setpwm(num,0,off);
			if(end_angle>start_angle){delayMs((u16)((end_angle-start_angle)*2.7));}
			else{delayMs((u16)((start_angle-end_angle)*2.7));}
			break;
		case 2:
			if(end_angle>start_angle){
				for(i=start_angle;i<=end_angle;i++){
					off=(u32)(158+i*2.2);
					pca_setpwm(num,0,off);
					delayMs(2);
					delayUs(speed*250);
				}
			}
			else if(start_angle>end_angle){
				for(i=start_angle;i>=end_angle;i--){
					off=(u32)(158+i*2.2);
					pca_setpwm(num,0,off);
					delayMs(2);
					delayUs(speed*250);
				}
			}
			break;
	}
}

/* USER EXTERN CODE END ------------------------------------------------------*/

/* USER INTERRUPT CODE BEGIN -------------------------------------------------*/
/* USER INTERRUPT  CODE END --------------------------------------------------*/


/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/



