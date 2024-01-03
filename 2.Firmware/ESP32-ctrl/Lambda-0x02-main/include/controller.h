#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "head.h"


#define CH1 1
#define CH2 2
#define CH3 44


int read_controller1();
int read_controller2();
int read_controller3();
void print_controller_value();
void send_controller_value();
void wheels_control(double leftwheel_v,double rightwheel_v);
void get_velocity(float *a, float *b);

#endif