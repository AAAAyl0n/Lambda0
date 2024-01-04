# Lambda0

## Overview

This repository hosts the code for Lambda bot protype and Integrated FOC drive controller, ESP32&stm32 based self-balancing robot, which can switch between bipedal and quadrupedal state, can carry goods in bipedal state in the future.

##### 该库包含Lambda机器人原型和一体化FOC驱动控制器的代码，基于esp32和stm32的自平衡机器人，可以在两足和四足状态之间切换，将来可以在两足状态下携带货物。
![机器人行走图](https://github.com/AAAAyl0n/Lambda0/blob/main/5.Docs/pic0.jpg)

###  integrated FOC drive controller

This is a picture of my integrated FOC drive controller, this control board utilizes a dual-stack design, with the bottom layer STM32 board responsible for implementing the porting of the SimpleFOC library within the STM32 standard library framework. The top layer ESP32 board is used for running control algorithms, displaying information on the screen, and handling basic communication protocols such as BLE and Wi-Fi.

##### 使用了双主控叠板设计，其中底层stm32板用于实现simpleFOC的stm32标准库框架移植，顶层esp32板用于运行控制算法、屏幕显示以及基础的通信（BLE、Wifi）。简易支持两路iic编码器无刷电机以及一个SPI接口屏幕。

![驱动板](https://github.com/AHANAyl0n/Lambda0/blob/main/5.Docs/%E5%BC%80%E5%8F%91%E6%9D%BF%E5%9B%BE%E7%89%87.jpg)、

### some pics

![调试过程图](https://github.com/AHANAyl0n/Lambda0/blob/main/5.Docs/%E6%9C%BA%E5%99%A8%E4%BA%BA%E7%9B%B4%E7%AB%8B%E8%A1%8C%E8%B5%B0%E5%9B%BE.jpg)
![pic](https://github.com/AHANAyl0n/Lambda0/blob/main/5.Docs/%E6%9C%BA%E5%99%A8%E4%BA%BA%E8%B0%83%E8%AF%95%E5%9B%BE.jpg)


