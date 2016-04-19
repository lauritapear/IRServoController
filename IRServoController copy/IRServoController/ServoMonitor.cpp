
#include "ServoMonitor.h"
#include "IRServoController.h"
#include "Arduino.h"
#include <Servo.h>



extern "C" {
 #include <stddef.h>
 #include <stdint.h>
 #include <math.h>
}

static unsigned int dutyCycle1Counter = 0;
static unsigned int periodCounter = 0;
static unsigned int dutyCycle2Counter = 0;
static bool relayState = 0;
static unsigned int dutyCycle1 = CENTERED_DUTY;
static unsigned int dutyCycle2 = CENTERED_DUTY;

Servo servo1;
Servo servo2;

void AttachServos()
{
   servo1.attach(SERVO_1_PIN);
   servo2.attach(SERVO_2_PIN);
}

void AttachServo(Servo servo, int pinNumber)
{
  servo.attach(pinNumber);
}

void DetachServo(Servo servo)
{
  servo.detach();
}

Servo GetServo(int servoNumber)
{
  if (servoNumber == FirstServo)
  {
    return servo1;
  }
  else if(servoNumber == SecondServo)
  {
     return servo2;
  }
}

void WriteServoServoPosition(int theServo, int dutyCycle)
{
  if (theServo == FirstServo)
  {
    dutyCycle1 = dutyCycle;
    WriteServo1(dutyCycle1);
  }
  else if (theServo == SecondServo)
  {
    dutyCycle2 = dutyCycle;
    WriteServo2(dutyCycle2);
  }
}

void WriteServo1(int dutyCycle)
{
    servo1.write(dutyCycle);
}

void WriteServo2(int dutyCycle)
{
    servo2.write(dutyCycle);
}

void MonitorMotorIncrementButton(unsigned int *dutyCycle, unsigned int dutyMax, void (*WriteServo)(int duty))
{
  if(*dutyCycle < dutyMax)
  {
      *dutyCycle += DUTY_DELTA;
      WriteServo(*dutyCycle);
      delay(10);
  }
}

void MonitorMotorDecrementButton(unsigned int *dutyCycle, unsigned int dutyMin, void (*WriteServo)(int duty))
{
  if(*dutyCycle > dutyMin)
  {
      *dutyCycle -= DUTY_DELTA;
      WriteServo(*dutyCycle);
      delay(10);
  }
}

void CenterServoSlowly(Servo servo, char servoIndex)
{
//      while((abs(servo.read()) - CENTERED_DUTY) != 0)
//     {
//      char currentPosition = servo.read();
//       if(servo.read() > 90)
//       {
//        currentPosition--;
//        servo.write(currentPosition);
//        delay(20);
//       }
//       else
//       {
//        currentPosition++;
//        servo.write(currentPosition);
//        delay(20);
//       }
//     }
  if(servo.read() > 90)
  {
    while((GetDutyCycle(servoIndex)) >= CENTERED_DUTY)
    {
       char currentPosition = GetDutyCycle(servoIndex);
       currentPosition--;
       WriteServoServoPosition(servoIndex, currentPosition);
       delay(50);
    }
       
  }else
  {
    while((GetDutyCycle(servoIndex)) <= CENTERED_DUTY)
    {
      char currentPosition = GetDutyCycle(servoIndex);
      currentPosition++;
      WriteServoServoPosition(servoIndex, currentPosition);
      delay(50);
    }
  }
}

void MonitorCenterButton()
{
    char duryTemp1 = GetDutyCycle(FirstServo);
    char duryTemp2 = GetDutyCycle(SecondServo);

    CenterServoSlowly(servo1, FirstServo);
    delay(100);
    CenterServoSlowly(servo2, SecondServo);
//
//    WriteServo1(dutyCycle1);
//    delay(250);
//    WriteServo2(dutyCycle2);
//    delay(250);    
}

void MonitorRelayButton()
{
    relayState = !relayState;
    digitalWrite(RELAY_OUTPUT_PIN, relayState);
}

void MotorController(int servoMotor, int option)
{
  if (servoMotor == FirstServo)
  {
    MoveMotor1(option);
  }else
  {
    MoveMotor2(option);
  }
}

void MoveMotor1(int option)
{
  if(option == Increment)
  {
    MonitorMotorIncrementButton(&dutyCycle1, DUTY1_MAX, WriteServo1);
  }else
  {
    MonitorMotorDecrementButton(&dutyCycle1, DUTY1_MIN, WriteServo1);
  }
}

void MoveMotor2(int option)
{
    if(option == Decrement)
    {
    MonitorMotorIncrementButton(&dutyCycle2, DUTY2_MAX, WriteServo2);
    }else
    {
    MonitorMotorDecrementButton(&dutyCycle2, DUTY2_MIN, WriteServo2);
    }
}

unsigned int GetDutyCycle(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
    return dutyCycle1;
  }else
  {
    return dutyCycle2;
  }
}

void SetDutyCycle(int servoMotor, int dutyCycleValue)
{
  if (servoMotor == FirstServo)
  {
    dutyCycle1 = dutyCycleValue;
  }else
  {
    dutyCycle2 = dutyCycleValue;
  }
}
