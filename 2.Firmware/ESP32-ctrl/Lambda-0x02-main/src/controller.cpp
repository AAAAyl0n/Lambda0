#include "controller.h"

static int previousData2 = -1; 

int read_controller1(){
    int tmp = pulseIn(CH1, HIGH, 25000);
    if(tmp<=100){
            tmp=1501;
    }
    tmp-=1501;
    return tmp;
}
int read_controller2(){
    int tmp = pulseIn(CH2, HIGH, 25000);
    if(tmp<=100){
            tmp=1501;
    }
    tmp-=1501;
    return tmp;
}
int read_controller3(){
    int tmp = pulseIn(CH3, HIGH, 25000);
    if(tmp<=100){
            tmp=1501;
    }
    tmp-=1501;
    return tmp;
}


void print_controller_value(){

    char buffer[50];
    sprintf(buffer, "CH1: %d", read_controller1());
    Serial.println(buffer);

    sprintf(buffer, "CH2: %d", read_controller2());
    Serial.println(buffer);

}

void wheels_control(double leftwheel_v,double rightwheel_v){
    Serial2.print("M");       
    Serial2.print(leftwheel_v, 2);  
    Serial2.print(','); 
    Serial2.print(rightwheel_v, 2);
    
    Serial2.print('\r');      
    Serial2.print('\n');      
}

void send_controller_value(){
    double data1=0.0;//FOC轮子控制量
    double data3=0.0;
    data1 = read_controller1();
    data3 = read_controller3();
    // Change the divisor to 60 and multiply by 2 to get the range -10 to 10
    data1 = (data1/60) * 2;  
    data3 = (data3/60); 
    if(data1<0.1&&data1>-0.1){
        data1=0.0;
    }
    if(data3<0.1&&data3>-0.1){
        data3=0.0;
    }

    Serial2.print("M");       
    Serial2.print(data1+data3, 2);  
    Serial2.print(','); 
    Serial2.print(data1-data3, 2);
    
    Serial2.print('\r');      
    Serial2.print('\n');      

  /******************************************************/
    int data2 = read_controller2();//舵机控制量

    // 只有当data2与上次的值不同时，才执行LobotSerialServoMove
    if (data2 != previousData2) {
        LobotSerialServoMove(Serial1, ID1, 535+data2,500);
        LobotSerialServoMove(Serial1, ID2, 470-data2,500);

        // 更新previousData2的值
        previousData2 = data2;
    }
}

double get_controller_value(){
    double data1=0.0;//FOC轮子控制量
    double data3=0.0;
    data1 = read_controller1();
    data3 = read_controller3();
    // Change the divisor to 60 and multiply by 2 to get the range -10 to 10
    data1 = (data1/60) * 2;  
    data3 = (data3/60); 
    if(data1<0.1&&data1>-0.1){
        data1=0.0;
    }
    if(data3<0.1&&data3>-0.1){
        data3=0.0;
    }
    return data1;
}

/*
    Serial2.print("T");       // Command for A
    Serial2.print(data1, 2);  // Send the value of data with 2 decimal places
    Serial2.print('\r');      // Send carriage return (CR)
    Serial2.print('\n');      // Send newline (LF)
  
  
  
  LobotSerialServoMove(Serial1, ID1, 535, 500);
  LobotSerialServoMove(Serial1, ID2, 470, 500);
  delay(1000);
  LobotSerialServoMove(Serial1, ID1, 735, 500);
  LobotSerialServoMove(Serial1, ID2, 270, 500);
  delay(1000);
*/


void get_velocity(float *a, float *b) {//获取FOC控制的无刷电机的双轮速度

     if (Serial2.available()){
        String receivedData = Serial2.readStringUntil('\n');  // 读取直到换行符

        if (receivedData.startsWith("V")) {
            int commaPos = receivedData.indexOf(',');
            if (commaPos != -1) {
                String firstValue = receivedData.substring(1, commaPos);
                String secondValue = receivedData.substring(commaPos + 1);
                
                *a = firstValue.toFloat();
                *b = secondValue.toFloat();
            }
        }
    }
}
