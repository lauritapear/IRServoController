#include <EEPROM.h>
#include "ServoMonitor.h"
#include "IRServoController.h"

static const int addressFirstServo = 0x50;
static const int addressSecondServo = 0x100;
int valueServo1;
int valueServo2;

void ReadEeprom()
{
  valueServo1 = EEPROM.read(addressFirstServo);
  valueServo2 = EEPROM.read(addressSecondServo);
}

int GetServoValue(int servo)
{
  if (servo == FirstServo)
  {
    return EEPROM.read(addressFirstServo);
  }
  else
  {
     return EEPROM.read(addressSecondServo);
  }
}

void WriteEeprom(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
     EEPROM.update(addressFirstServo, GetDutyCycle(FirstServo));
     DetachServo(GetServo(FirstServo));
  }
  else
  {
     EEPROM.update(addressSecondServo, GetDutyCycle(SecondServo));
     DetachServo(GetServo(SecondServo));
  }
}

void CallBack1()
{
  WriteEeprom(FirstServo);
}

void CallBack2()
{
  WriteEeprom(SecondServo);
}

bool PositionValueOutOfRange(int ServoValue)
{
  return (ServoValue < DUTY2_MIN)||(ServoValue > DUTY1_MAX);
}

void SetServosToInitialPosition()
{
   ReadEeprom();
   
   if (PositionValueOutOfRange(valueServo1))
    {
      WriteServoServoPosition(FirstServo,CENTERED_DUTY);
    }
    else
    {
      WriteServoServoPosition(FirstServo, valueServo1);
    }

 if (PositionValueOutOfRange(valueServo2))
    {
      WriteServoServoPosition(SecondServo,CENTERED_DUTY);
    }
    else
    {
      WriteServoServoPosition(SecondServo, valueServo2);
    }
}

