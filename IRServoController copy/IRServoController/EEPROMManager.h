#ifndef EEPROMMANAGER_H
#define EEPROMMANAGER_H

void ReadEeprom();
int GetServoValue(int servo);
void SetServosToInitialPosition();
void WriteEeprom(int servoMotor);
void CallBack1();
void CallBack2();

#endif
