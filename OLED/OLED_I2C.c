/**
  ******************************************************************************
  * File Name          : OLED_I2C.c
  * Description        : This file provides code for the configuration
  *                      of the OLED_I2C instances.
  ******************************************************************************
  * @attention
  *
  * chip:  stm32f103c8t6 chip.  
  * date:  XX.XX.XX
  * pin:   PB6 -> SCL  PB7 -> SDA
  * frequency: 72MHz
  * note: 
  *
  ******************************************************************************
  */

/* USER INCLUDES CODE BEGIN --------------------------------------------------*/
#include "OLED_I2C.h"
#include "codetab.h"  /* 字符头文件 */
/* USER INCLUDES CODE END ----------------------------------------------------*/

/* USER GLOBAL VARIABLE BEGIN ------------------------------------------------*/
/* USER GLOBAL VARIABLE END --------------------------------------------------*/

/* USER INIT CODE BEGIN ------------------------------------------------------*/
/* USER INIT CODE END --------------------------------------------------------*/

/* USER STATIC CODE BEGIN ----------------------------------------------------*/
/**
  * @file   I2C写函数
  * @brief  写设备地址，写寄存器地址，写数据
  * @calls  	iic.I2C_Start(); iic.I2C_Stop(); iic.I2C_SendByte();
  * @call by 	OLED_I2C.WriteCmd(); 
  * @param  None
  * @retval None
  * @date 
  */
void I2C_WriteByte(uint8_t addr,uint8_t data){
	I2C_Start();
	while(!I2C_SendByte(0x78));
	while(!I2C_SendByte(addr));
	while(!I2C_SendByte(data));
	I2C_Stop();
}

/**
  * @file   写命令函数
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void WriteCmd(unsigned char I2C_Command){
	I2C_WriteByte(0x00, I2C_Command);
}

/**
  * @file   写数据函数
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void WriteDat(unsigned char I2C_Data){
	I2C_WriteByte(0x40, I2C_Data);
}

/* USER STATIC CODE END ------------------------------------------------------*/


/* USER EXTERN CODE BEGIN ----------------------------------------------------*/
/**
  * @file   oled初始化函数
  * @brief  
  * @calls  	delay.delayMs(); 
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void OLED_Init(void){
	delayMs(100); /* 这里的延时很重要 */
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

/**
  * @file   设置起始光标
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  x：光标的横坐标(0~127)
  *         y：光标的纵坐标(0~7)
  * @retval None
  * @date 
  */
void OLED_SetPos(unsigned char x, unsigned char y) { 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

/**
  * @file   全屏填充
  * @brief  全屏都会发亮
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  fill_Data: 要覆盖的数据
  * @retval None
  * @date 
  */
void OLED_Fill(unsigned char fill_Data){
	unsigned char m,n;
	for(m=0;m<8;m++){
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);			//low column start address
		WriteCmd(0x10);			//high column start address
		for(n=0;n<128;n++){
				WriteDat(fill_Data);
		}
	}
}
/**
  * @file   清屏函数
  * @brief  全屏变暗
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void OLED_CLS(void){
	OLED_Fill(0x00);
}

/**
  * @file   OLED唤醒
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void OLED_ON(void){
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

/**
  * @file   OLED休眠
  * @brief  休眠模式下,OLED功耗不到10uA
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  None
  * @retval None
  * @date 
  */
void OLED_OFF(void){
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

/**
  * @file   显示codetab.h中的ASCII字符
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  x,y：起始点坐标(x:0~127, y:0~7);
  *			ch[]：要显示的字符串
  *			TextSize:字符大小(1:6*8 ; 2:8*16)
  * @retval None
  * @date 
  */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize){
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize){
		case 1:{
			while(ch[j] != '\0'){
				c = ch[j] - 32;
				if(x > 126){
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:{
			while(ch[j] != '\0'){
				c = ch[j] - 32;
				if(x > 120){
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

/**
  * @file   显示codetab.h中的汉字
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  x,y：起始点坐标(x:0~127, y:0~7)
  *			N：汉字在codetab.h中的索引
  * @retval None
  * @date 
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N){
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++){
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++){
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

/**
  * @file   显示BMP位图
  * @brief  
  * @calls  	xxxx:
  * @call by 	xxxx:
  * @param  x0,y0：起始点坐标(x0:0~127, y0:0~7)
  *			x1,y1:起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
  * @retval None
  * @date 
  */
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]){
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++){
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++){
			WriteDat(BMP[j++]);
		}
	}
}
/* USER EXTERN CODE END ------------------------------------------------------*/

/* USER INTERRUPT CODE BEGIN -------------------------------------------------*/
/* USER INTERRUPT  CODE END --------------------------------------------------*/


/********************************* REFERENCE ***********************************
 * [1] 
 ******************************************************************************/

/************************ (C) COPYRIGHT gzsyf *****END OF FILE*****************/














