/**
  ******************************************************************************
  * File Name          : DHT11.c
  * Description        : 温湿度传感器
  ******************************************************************************
  * @attention
  *
  * chip:  stm32f103c8t6.  
  * date:  XX.XX.XX
  * pin:  PB11 -> dat
  * frequency: 72MHz
  * note:
  *
  ******************************************************************************
  */


/* USER INCLUDES CODE BEGIN --------------------------------------------------*/
#include "DHT11.h"
/* USER INCLUDES CODE END ----------------------------------------------------*/

/* USER GLOBAL VARIABLE BEGIN ------------------------------------------------*/
/* USER GLOBAL VARIABLE END --------------------------------------------------*/


/* USER INIT CODE BEGIN ------------------------------------------------------*/
/**
  * @file   DHT11 数据脚的io口配置
  * @brief  暂时为PB11，这个是要最先配置(先于init，配置完后就用init初始化)
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
u8 DHT11_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//换IO口需要修改
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出，如果需要考虑到IC的电流驱动能力时要接上拉电阻（5K）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(DHT11_IO,&GPIO_InitStructure);
	
}

/**
  * @file   DHT11 数据脚的置为输出
  * @brief  由于单线传输，输出输入要变来变去，推挽输出模式
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
static void GPIO_SETOUT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//换IO口需要修改
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出，如果需要考虑到IC的电流驱动能力时要接上拉电阻（5K）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(DHT11_IO,&GPIO_InitStructure);
	
}

/**
  * @file   DHT11 数据脚的置为输入
  * @brief  由于单线传输，输出输入要变来变去，浮空输入模式
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
static void GPIO_SETIN(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//换IO口需要修改
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(DHT11_IO,&GPIO_InitStructure);
}


/* USER INIT CODE END --------------------------------------------------------*/


/* USER STATIC CODE BEGIN ----------------------------------------------------*/
/**
  * @file   主机发送开始信号
  * @brief  
  * @calls  	delay,delayMs()
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
static void DHT11_Rst(void){                 
	GPIO_SETOUT();						//配置成输出模式
	GPIO_ResetBits(DHT11_IO,DHT11_PIN); //拉低数据线
	delayMs(20);    					//拉低至少18ms
	GPIO_SetBits(DHT11_IO,DHT11_PIN); 	//拉高数据线 
	delayUs(30);     					//主机拉高20~40us
	GPIO_ResetBits(DHT11_IO,DHT11_PIN);
}

/**
  * @file   检测DHT11的响应信号
  * @brief  暂时为PB11，这个是要最先配置(先于init，配置完后就用init初始化)
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval 检测到回应-->返回1，否则0
  * @date 
  */
static u8 DHT11_Check(void){   
	u8 retry=0;				// 超时变量
	GPIO_SETIN();			// 设置为输入模式	
	
	/* DHT11会拉低40~50us */
	while(!GPIO_ReadInputDataBit(DHT11_IO,DHT11_PIN) && retry<100){
		retry++;
		delayUs(1);
	}
	if(retry >= 100)		//超时未响应/未收到开始信号，退出检测
		return 0;
	else 
		retry = 0;
	
	/* DHT11拉低后会再次拉高40~50us */
	while(GPIO_ReadInputDataBit(DHT11_IO,DHT11_PIN) && retry<100){
		retry++;
		delayUs(1);
	}
	if(retry>=100)			//超时，DHT11工作出错，退出检测
		return 0;
	return 1;				//设备正常响应，可以正常工作
}


/**
  * @file   从DHT11上读取一个Bit数据
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval 返回从DHT11上读取的一个Bit数据
  * @date 
  */
static u8 DHT11_Read_Bit(void){
 	u8 retry = 0;		// 超时变量
	/* DHT11的Bit开始信号为12-14us低电平 */
	while(GPIO_ReadInputDataBit(DHT11_IO,DHT11_PIN) && retry<100){//等待变为低电平(等待Bit开始信号)
		retry++;
		delayUs(1);
	}
	retry = 0;
	while(!GPIO_ReadInputDataBit(DHT11_IO,DHT11_PIN) && retry<100){//等待变高电平（代表数据开始传输）
		retry++;
		delayUs(1);
	}
	delayUs(30);//等待30us
	/* 0信号为26-28us，1信号则为116-118us,所以说超过30us去读取引脚状态就可以知道传输的值了 */
	if(GPIO_ReadInputDataBit(DHT11_IO,DHT11_PIN)) return 1;
	else return 0;		   
}

/**
  * @file   从DHT11上读取一个byte数据
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval 返回从DHT11上读取的一个byte数据
  * @date 
  */
static u8 DHT11_Read_Byte(void){        
	u8 i,dat;
	dat=0;
	for (i=0;i<8;i++){
		dat<<=1; 
		dat|=DHT11_Read_Bit();
	}	
	return dat;
}


/* USER STATIC CODE END ------------------------------------------------------*/


/* USER EXTERN CODE BEGIN ----------------------------------------------------*/
/**
  * @file   初始化，并发送开始信号
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
u8 DHT11_Init(void){
	DHT11_Rst();			//发送开始信号
	return DHT11_Check();	//检测DHT11的响应
}

/**
  * @file   从DHT11上读取温湿度数据（这里省略小数值）
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  temp:用于存放温度值(范围:0~50°)，humi:用于存放湿度值(范围:20%~90%)
  * @retval 1：成功读取数据，0：读取数据出错
  * @date 
  */
u8 DHT11_Read_Data(u8 *temp,u8 *humi){        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==1){	//设备响应正常
		for(i=0;i<5;i++){	//读取40位数据
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4]){//进行校验
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 0;				//设备未成功响应，返回0
	return 1;					//读取数据成功返回1
}


/* USER EXTERN CODE END ------------------------------------------------------*/


/* USER INTERRUPT CODE BEGIN -------------------------------------------------*/
/* USER INTERRUPT  CODE END --------------------------------------------------*/


/********************************* REFERENCE ***********************************
 * [1] code come from
 * https://blog.csdn.net/qq_38203996/article/details/103328291?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-5.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-5.channel_param
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/

