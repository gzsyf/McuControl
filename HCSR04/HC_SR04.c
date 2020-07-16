/**
  ******************************************************************************
  * File Name          : HC-SR04.c
  * Description        : This file provides code for the configuration
  *                      of the HC-SR04 module.
  ******************************************************************************
  * @attention
  *
  * chip:  XXXXXXchip.  
  * date:  XX.XX.XX
  * pin:   PB0->Trig  PB1->Echo  VCC->5V
  * frequency: 72MHz
  * note:
  *
  ******************************************************************************
  */

/* USER INCLUDES CODE BEGIN --------------------------------------------------*/
#include "HC_SR04.h"
/* USER INCLUDES CODE END ----------------------------------------------------*/

/* USER GLOBAL VARIABLE BEGIN ------------------------------------------------*/
/* USER GLOBAL VARIABLE END --------------------------------------------------*/



/* USER INIT CODE BEGIN ------------------------------------------------------*/

/**
  * @file   初始化HCSR04模块的引脚
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void configHcsrIO(void){	
    //定义一个GPIO_InitTypeDef 类型的结构体
    GPIO_InitTypeDef  GPIO_InitStructure;	
    RCC_APB2PeriphClockCmd(TRIG_GPIO_RCC|ECHO_GPIO_RCC,ENABLE);//使能GPIO的外设时钟
    /*定义Trig引脚*/
    GPIO_InitStructure.GPIO_Pin =TRIG_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置引脚模式为推免输出模式						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHZ         
    GPIO_Init(TRIG_GPIO_PORT, &GPIO_InitStructure);
    /*定义Echo引脚*/
    GPIO_InitStructure.GPIO_Pin =ECHO_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置引脚模式为输入模式			 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHZ   
    GPIO_Init(ECHO_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @file   初始化TIM2定时器
  * @brief  不开启中断，单纯计时
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void configHcsrTIM(void){
	//定时器定时时间T计算公式：T=(TIM预分频+1)*(TIM自动重载值+1)/APB1时钟频率
	TIM_TimeBaseInitTypeDef	 TIM_BaseInitStructure;			//定义一个定时器结构体变量
	RCC_APB1PeriphClockCmd(TIMER_RCC, ENABLE);   	//使能定时器2
	
	TIM_DeInit(TIMER);//将TIMER定时器初始化位复位值
	TIM_InternalClockConfig(TIMER);//配置 TIMER 内部时钟
	
	TIM_BaseInitStructure.TIM_Period = 49999;//设置自动重载寄存器值为最大值	0~65535之间  1000000/1000=1000us=1ms													
	TIM_BaseInitStructure.TIM_Prescaler = 71;//自定义预分频系数，TIM1_CLK=72/72=1MHz
													
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分割为0
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式 从0开始向上计数  
													
	TIM_TimeBaseInit(TIMER, &TIM_BaseInitStructure); //根据指定参数初始化TIM时间基数寄存器
}  
/* USER INIT CODE END --------------------------------------------------------*/



/* USER STATIC CODE BEGIN ----------------------------------------------------*/
/**
  * @file   激活Trig引脚
  * @brief  让超声波测距模块开始工作
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
static void activateTrig(void){
	TRIG_CLR();//预先拉低Trig引脚
	TRIG_SET();
	delayUs(10);
	TRIG_CLR();
}

/* USER STATIC CODE END ------------------------------------------------------*/


/* USER EXTERN CODE BEGIN ----------------------------------------------------*/
/**
  * @file   读取HCSR测距模块的距离
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
float getDistance(void){
	u32 count = 0;
	float Distance = 0;
	TIMER->CNT = 0;	//计数器的值为0
	while(READ_ECHO() == 0);	//等待高电平
	TIM_Cmd(TIMER, ENABLE);	//开启定时器
	while(READ_ECHO() == 1){}	//等待低电平
	TIM_Cmd(TIMER, DISABLE);	//关闭定时器
	count = TIMER->CNT;	//获取定时器的值
	Distance = (float)count * 0.017 ;
	return Distance;
}


/* USER EXTERN CODE END ------------------------------------------------------*/

/* USER INTERRUPT CODE BEGIN -------------------------------------------------*/
/* USER INTERRUPT  CODE END --------------------------------------------------*/


/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/
