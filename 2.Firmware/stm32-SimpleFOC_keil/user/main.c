
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>
#include "MyProject.h"
#include "user.h"


/******************************************************************************/
#define LED_blink    GPIOC->ODR^=(1<<13)
/******************************************************************************/
void commander_run(void);
/******************************************************************************/
extern float voltage_power_supply;   //电源电压，在BLDCmotor.c中定义
/******************************************************************************/
MOTORController M1,M2;

long timecntr_pre=0;
long time_cntr=0;

float setPoint1=0, setPoint2=0;
/******************************************************************************/
//us计时，每71.5分钟溢出循环一次
uint32_t timecount(void)
{
	uint32_t  diff,now_us;
	
	now_us = _micros();    //0xFFFFFFFF=4294967295 us=71.5分钟
	if(now_us>=timecntr_pre)diff = now_us - timecntr_pre;   //us
	else
		diff = 0xFFFFFFFF - timecntr_pre + now_us;
	timecntr_pre = now_us;
	
	return diff;
}
/******************************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA,GPIOB,GPIOC,AFIO;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         //PC13是LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //对选中管脚初始化
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);                 //上电点亮LED
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_9;          //使能,PB9是motor1,PB3是motor2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_9);                  //低电平解除,Motor_init()中使能
}
/******************************************************************************/
int main(void)
{
	GPIO_Config();
	uart_init(115200);
	strcpy(M1.str, "M1");
	strcpy(M2.str, "M2");
	TIM2_PWM_Init();    //M1_PWM
	TIM3_PWM_Init();    //M2_PWM
	systick_CountInit();  //systick时钟开启1ms中断模式
	I2CandSPI_Init();   //根据编码器设定初始化I2C或者SPI, 在 MyProject.h 中定义编码器类型 
	
	delay_ms(1000);               //Wait for the system to stabilize
	MagneticSensor_Init(&M1);     //初始化编码器参数 
	MagneticSensor_Init(&M2);
	InlineCurrentSense(&M1,0.001,50,ADC_Channel_3,ADC_Channel_4,NOT_SET);    //SimpleMotor//采样电阻阻值，运放倍数，A相，B相，C相
	InlineCurrentSense(&M2,0.001,50,ADC_Channel_5,ADC_Channel_9,NOT_SET);
	InlineCurrentSense_Init(&M1); //ADC初始化和偏置电压校准
	InlineCurrentSense_Init(&M2);
	LPF_init(&M1);                //LPF参数初始化
	LPF_init(&M2);
	PID_init(&M1);                //PID参数初始化
	PID_init(&M2);
	
	voltage_power_supply=12;      //V,两个电机的共同参数
	
	M1.pole_pairs=7;              //电机极对数,3505极对数是10,5008电机极对数是7
	M1.voltage_sensor_align=2;    //V alignSensor() use it，大功率电机设置的值小一点比如0.5-1，小电机设置的大一点比如2-3
	M1.voltage_limit=5;           //V，最大值需小于12/1.732=6.9
	M1.velocity_limit=20;         //rad/s angleOpenloop() and PID_angle() use it
	M1.current_limit=50;          //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
	M1.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	M1.controller=Type_torque;    //Type_angle; //Type_torque; //Type_velocity
	M1.target=0;
	
	M2.pole_pairs=7;              //电机极对数,2804云台电机极对数是7
	M2.voltage_sensor_align=2;    //V alignSensor() use it，大功率电机设置的值小一点比如0.5-1，小电机设置的大一点比如2-3
	M2.voltage_limit=5;           //V，最大值需小于12/1.732=6.9
	M2.velocity_limit=20;         //rad/s angleOpenloop() and PID_angle() use it
	M2.current_limit=50;          //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
	M2.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	M2.controller=Type_torque;    //Type_angle; //Type_torque; //Type_velocity
	M2.target=0;
	
	Motor_init(&M1);
	Motor_init(&M2);
	Motor_initFOC(&M1, 0, UNKNOWN);  //(&M1, 3.68, CCW);  //(&M1, 0, UNKNOWN);如果填入零点偏移角度和方向，将跳过上电检测。电机极对数要设置正确。 
	Motor_initFOC(&M2, 0, UNKNOWN);
  printf("Motor ready.\r\n");
	
	while(1)
	{
		time_cntr = _micros();
		if((time_cntr - timecntr_pre) >= 1000)  //us
		{
			timecntr_pre = time_cntr;
			//LED_blink;
			//printf("A%.2f,%.2f\r\n", M1.shaft_angle,M2.shaft_angle);  //观察角度变化，便于调试
			printf("V%.2f,%.2f\r\n", M1.shaft_velocity,-M2.shaft_velocity);  //观察速度变化，便于调试
		}
		commander_run();
		
		move(&M1, M1.target);
		
		loopFOC(&M1);
		
		move(&M2, M2.target);
		
		loopFOC(&M2);
		commander_run();
	}
}
/******************************************************************************/
void commander_run(void)
{
	if((USART_RX_STA&0x8000)!=0)
	{
		switch(USART_RX_BUF[0])
		{
			case 'H':
				printf("Hello World!\r\n");
				break;
			case 'A':   //A6.28
				M1.target=atof((const char *)(USART_RX_BUF+1));
				printf("A=%.4f\r\n", M1.target);
				break;
			case 'B':   //B6.28
				M2.target=atof((const char *)(USART_RX_BUF+1));
				printf("B=%.4f\r\n", M2.target);
				break;
			case 'T':   //
				M1.target=-atof((const char *)(USART_RX_BUF+1));
				M2.target=atof((const char *)(USART_RX_BUF+1));
				printf("A=%.4f\r\n", M1.target);
				printf("B=%.4f\r\n", M2.target);
				break;
			case 'M':   // M5.23,6.78
            {
                char *commaPos = strchr((const char *)(USART_RX_BUF + 1), ',');
                if (commaPos != NULL) 
                {
                    *commaPos = '\0';  // Terminate the first number string at the comma
                    M1.target = -atof((const char *)(USART_RX_BUF + 1));
                    M2.target = atof(commaPos + 1);
                    printf("A=%.4f\r\n", M1.target);
                    printf("B=%.4f\r\n", M2.target);
                }
                break;
            }			
		}
		USART_RX_STA=0;
	}
}
/******************************************************************************/



