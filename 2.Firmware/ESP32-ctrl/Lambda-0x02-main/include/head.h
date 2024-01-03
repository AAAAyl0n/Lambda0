#ifndef _HEAD_H
#define _HEAD_H

#include "Arduino.h"
//#include "Adafruit_MPU6050.h"
//#include "Adafruit_Sensor.h"
#include "Wire.h"
#include "TFT_eSPI.h"
//#include "imu.h"
#include "MPU6050_tockn.h"
#include "mytft.h"
#include "controller.h"
#include "HardwareSerial.h"
#include "botservo.h"
#include "math.h"
#include "pid.h"
#include "lowpassfilter.h"

#define ID1   1
#define ID2   2

#define SDA_PIN 21  // SDA
#define SCL_PIN 16  // SCL


extern TFT_eSPI tft;
//extern Adafruit_MPU6050 mpu;


#endif