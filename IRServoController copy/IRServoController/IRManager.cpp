#include <IRremote.h>
#include <IRremoteInt.h>
#include "ServoMonitor.h"
#include "IRServoController.h"
#include "EEPROMManager.h"

void TranslateIR(decode_results *results)
{
  switch(results->value)
  {
    case INCREMENT_BUTTON_ONE_SIGNAL:
    AttachServo(GetServo(FirstServo), SERVO_1_PIN);
    MotorController(FirstServo, Increment);
    InitializeEepromTimer(FirstServo);
    break;
    
    case DECREMENT_BUTTON_ONE_SIGNAL:
    AttachServo(GetServo(FirstServo), SERVO_1_PIN);
    MotorController(FirstServo, Decrement);
    InitializeEepromTimer(FirstServo);
    break;

    case INCREMENT_BUTTON_TWO_SIGNAL:
    AttachServo(GetServo(SecondServo), SERVO_2_PIN);
    MotorController(SecondServo, Increment);
    InitializeEepromTimer(SecondServo);
    break;

    case DECREMENT_BUTTON_TWO_SIGNAL:
    AttachServo(GetServo(SecondServo), SERVO_2_PIN);
    MotorController(SecondServo, Decrement);
    InitializeEepromTimer(SecondServo);
    break;

    case CENTER_BUTTON_SIGNAL:
    AttachServos();
    MonitorCenterButton();
    InitializeEepromTimer(FirstServo);
    InitializeEepromTimer(SecondServo);
    break;

    case RELAY_BUTTON_SIGNAL:
    MonitorRelayButton();
    break;
  }
}
