//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-03-29
//  ����޸�   : 
//  ��������   :��ʾ����(STM32F0ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   3.3v��Դ
//              SCL   PA0��SCLK��
//              SDA   PA1��MOSI��
//              RES   PA2
//              DC    PA3
//              CS    PA4
//              BLK   PA5
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018/3/16
//All rights reserved
//******************************************************************************/
#include "stm32f0xx.h"
#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"

int main(void)
{
	float t=0;
	delay_init();
	LED_Init();//LED��ʼ��
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	LED_ON;
	while(1)
	{
		LCD_ShowChinese(40,0,"�о�԰����",RED,WHITE,32,0);
		LCD_ShowString(10,33,"LCD_W:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);
		LCD_ShowString(10,66,"LCD_H:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);
		LCD_ShowFloatNum1(10,99,t,4,RED,WHITE,32);
		t+=0.11;
		LCD_ShowPicture(160,95,40,40,gImage_1);
	}
}

