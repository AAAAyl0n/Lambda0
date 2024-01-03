#ifndef LOBOT_SERVO_H
#define LOBOT_SERVO_H

#include "head.h"

#define GET_LOW_BYTE(A) (uint8_t)((A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
//宏函数 获得A的高八位
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//宏函数 以A为高八位 B为低八位 合并为16位整形

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

byte LobotCheckSum(byte buf[]);
void LobotSerialServoMove(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time);
void LobotSerialServoStopMove(HardwareSerial &SerialX, uint8_t id);
void LobotSerialServoSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID);
void LobotSerialServoSetMode(HardwareSerial &SerialX, uint8_t id, uint8_t Mode, int16_t Speed);
void LobotSerialServoLoad(HardwareSerial &SerialX, uint8_t id);
void LobotSerialServoUnload(HardwareSerial &SerialX, uint8_t id);

int LobotSerialServoReceiveHandle(HardwareSerial &SerialX, byte *ret);
int LobotSerialServoReadPosition(HardwareSerial &SerialX, uint8_t id);
int LobotSerialServoReadVin(HardwareSerial &SerialX, uint8_t id);


#endif // LOBOT_SERVO_H

/*使用案例*/
/*
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
}

#define ID1   1
#define ID2   2

void loop() {
  // put your main code here, to run repeatedly:
  LobotSerialServoMove(Serial, ID1, 100, 500);
  LobotSerialServoMove(Serial, ID2, 500, 500);
  delay(1000);
  LobotSerialServoMove(Serial, ID1, 500, 500);
  LobotSerialServoMove(Serial, ID2, 600, 500);
  delay(1000);
  LobotSerialServoMove(Serial, ID1, 900, 500);
  LobotSerialServoMove(Serial, ID2, 700, 500);
  delay(1000);
  LobotSerialServoMove(Serial, ID1, 500, 500);
  LobotSerialServoMove(Serial, ID2, 600, 500);
  delay(1000);
}
*/