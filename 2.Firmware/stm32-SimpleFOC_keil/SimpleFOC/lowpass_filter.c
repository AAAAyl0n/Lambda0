
#include "MyProject.h"


/******************************************************************************/
void LPF_init(MOTORController *M)
{
	M->LPF_q.Tf=0.05;    
	M->LPF_q.y_prev=0;
	M->LPF_q.timestamp_prev=_micros();
	
	M->LPF_d.Tf=0.05;
	M->LPF_d.y_prev=0;
	M->LPF_d.timestamp_prev=_micros();
	
	M->LPF_vel.Tf=0.05;
	M->LPF_vel.y_prev=0;
	M->LPF_vel.timestamp_prev=_micros();
}
/******************************************************************************/
float LPFoperator(LowPassFilter* LPF,float x)
{
	unsigned long now_us;
	float dt, alpha, y;
	
	now_us = _micros();
	dt = (now_us - LPF->timestamp_prev)*1e-6f;
	LPF->timestamp_prev = now_us;
	if (dt < 0.0f ) dt = 1e-3f;
	else if(dt > 0.3f)   //时间过长，大概是程序刚启动初始化，直接返回
	{
		LPF->y_prev = x;
		return x;
	}
	
	alpha = LPF->Tf/(LPF->Tf + dt);
	y = alpha*LPF->y_prev + (1.0f - alpha)*x;
	LPF->y_prev = y;
	
	return y;
}
/******************************************************************************/


