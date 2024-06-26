/*!
 * @file simpleTest.ino
 * @brief read data and write data to nfc card
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2024-04-12
 * @url https://github.com/DFRobot/DFRobot_PN7150
*/
#include "DFRobot_PN7150.h"

DFRobot_PN7150_I2C PN7150;

void setup()
{
  Serial.begin(115200);

  // Initialize the NFC module
  Serial.print(F("Connecting Device . . ."));
  while (!(PN7150.begin(NXPNCI_MODE_RW))) {
    Serial.print(F(" ."));
    delay(1000);
  }
  Serial.println(F("\nBegin ok!"));
}

void loop()
{
  PN7150.writeData(1, 1, 200);
  Serial.println(PN7150.readData(1));
  Serial.println(PN7150.readData(1, 1));
  Serial.println(PN7150.readUid());
  Serial.println(PN7150.scan("acee50e3"));
  Serial.println(PN7150.scan());
  Serial.println("---------------------");
}
