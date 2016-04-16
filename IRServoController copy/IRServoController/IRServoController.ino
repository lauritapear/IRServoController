//#include <Event.h>
#include <Timer.h>
#include <EEPROM.h>
#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <avr/wdt.h>
#include "IRServoController.h"
#include "ServoMonitor.h"
#include "IRManager.h"
#include "EEPROMManager.h"

Timer eepromWriteServo1Timer;
Timer eepromWriteServo2Timer;

IRrecv irrecv(RECV_PIN);
decode_results results;

void InitializePins() {
  
    pinMode(RELAY_OUTPUT_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void InitializeEepromTimer(int servoMotor)
{
  if (servoMotor == FirstServo)
  {
  eepromWriteServo1Timer.after(60000, CallBack1);
  }
  else
  {
   eepromWriteServo2Timer.after(60000, CallBack2);
  }
}

void setup() {

    InitializePins();
    SetServosToInitialPosition();
    AttachServos();
    

    Serial.begin(9600);
    irrecv.enableIRIn();
    wdt_enable(WDTO_1S); //Do we really need this?
}

void loop() {
  eepromWriteServo1Timer.update();
  eepromWriteServo2Timer.update();
    
    if (irrecv.decode(&results)) {

       TranslateIR(&results);
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value
    }
    delay(100);
    wdt_reset();
}
