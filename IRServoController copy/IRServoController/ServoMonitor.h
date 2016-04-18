
#ifndef SERVOMONITOR_H
#define SERVOMONITOR_H
#include <Servo.h>

#define SERVO_1_PIN (10)
#define SERVO_2_PIN (9)

void AttachServos();
void AttachServo(Servo servo, char pinNumber, char minBoundary, char maxBoundary);
void DetachServo(Servo servo);
Servo GetServo(int servoNumber);
void WriteServoServoPosition(int theServo, int dutyCycle);
void WriteServo1(int dutyCycle);
void WriteServo2(int dutyCycle);
void MonitorMotorIncrementButton(unsigned int *dutyCycle, unsigned int dutyMax, void (*WriteServo)(int duty));
void MonitorMotorDecrementButton(unsigned int *dutyCycle, unsigned int dutyMin, void (*WriteServo)(int duty));
void MonitorCenterButton();
void MonitorRelayButton();

void MotorController(int servoMotor, int option);
void MoveMotor1(int option);
void MoveMotor2(int option);
unsigned int GetDutyCycle(int servoMotor);
void SetDutyCycle(int servoMotor, int dutyCycleValue);
#endif
