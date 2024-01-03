#include "head.h"

//Kalman kalman;

TwoWire I2Ctwo = TwoWire(1);

double acc2rotation(double x, double z);//for kalman
MPU6050 mpu6050(I2Ctwo);



float nowangle = 0; // 当前角度
double wheel_ctrl=0;
float left_v=0,right_v=0;
float offset_angle=-11.1;

// control algorithm parametersw
// stabilisation pid 自稳PID
//P0.55 I5.5 初始值0.5 5 
PIDController pid_stb(2.2, 6, 0.2, 100000, 8);

// velocity pid 速度PID P初始值1.5
PIDController pid_vel(0, 0, 0, 10000, 3.1415926535/4);


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 10, 3); 
  Serial2.begin(115200, SERIAL_8N1, 18, 17);

  I2Ctwo.begin(SDA_PIN, SCL_PIN);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  mytft_init();
  //imu_init();

  //Kalman_Init(&kalman, 0.05, 0.15, 0.05);

}

void loop() {
  
  //print_controller_value();
  //Serial2.println("Hello, It's me.\n"); 
  //send_controller_value();

  //nowangle=read_imu();
  mpu6050.update();
  nowangle = mpu6050.getAngleY();
  //Serial.println("nowangle:" + String(nowangle));
  
  get_velocity(&left_v,&right_v);

  float target_angle = pid_vel((left_v+right_v)/2-0);
  //Serial.println("target_angle:" + String(target_angle));

  float torque = pid_stb(offset_angle-nowangle+target_angle);
  wheel_ctrl=-torque/10*4;
  wheels_control(wheel_ctrl,wheel_ctrl);
  //delay(11);
  //Serial.println("nowangle:" + String(nowangle));
  delay(50);
  
}




