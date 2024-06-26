/*!
 * @file nfcCardEmuSupport.ino
 * @brief nfc card simulation example
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2024-01-29
 * @url https://github.com/DFRobot/DFRobot_PN7150
*/
#include "DFRobot_PN7150.h"

#define CARDEMU_RAW_EXCHANGE

/* Discovery loop configuration according to the targeted modes of operation */
unsigned char DiscoveryTechnologies[] = {
    MODE_LISTEN | TECH_PASSIVE_NFCA,
    MODE_LISTEN | TECH_PASSIVE_NFCB,
};

/* Mode configuration according to the targeted modes of operation */
unsigned char mode = NXPNCI_MODE_CARDEMU;

DFRobot_PN7150_I2C PN7150;
DFRobot_PN7150_I2C::NxpNci_RfIntf_t RfInterface;

#define ADD (uint32_t)0 // Enlarge NDEF message by adding dummy content
const char NDEF_MESSAGE[14 + ADD] = { '\xC1',   // MB/ME/CF/1/IL/TNF
        0x01,   // TYPE LENGTH
        (0x07 + ADD) >> 24,   // PAYLOAD LENTGH MSB
        (0x07 + ADD) >> 16,   // PAYLOAD LENTGH
        (0x07 + ADD) >> 8,    // PAYLOAD LENTGH
        (0x07 + ADD) & 0xFF,  // PAYLOAD LENTGH LSB
        'T',    // TYPE
  // PAYLOAD
      0x02,   // Status
      'e', 'n', // Language
      'T', 'e', 's', 't' };

void NdefPush_Cb(unsigned char* pNdefRecord, unsigned short NdefRecordSize)
{
  (void)pNdefRecord;
  (void)NdefRecordSize;
  Serial.println(F("--- NDEF Record sent"));
}

#ifdef CARDEMU_RAW_EXCHANGE
void PICC_ISO14443_4_scenario(void)
{
  unsigned char OK[] = { 0x90, 0x00 };
  unsigned char Cmd[256];
  unsigned char CmdSize;

  while (1) {
    if (PN7150.NxpNci_CardModeReceive(Cmd, &CmdSize) == NFC_SUCCESS) {
      if ((CmdSize >= 2) && (Cmd[0] == 0x00)) {
        switch (Cmd[1]) {
        case 0xA4:
          Serial.println(F("Select File received"));
          break;

        case 0xB0:
          Serial.println(F("Read Binary received"));
          break;

        case 0xD0:
          Serial.println(F("Write Binary received"));
          break;

        default:
          break;
        }

        PN7150.NxpNci_CardModeSend(OK, sizeof(OK));
      }
    } else {
      Serial.println(F("End of transaction"));
      return;
    }
  }
}
#endif // ifdef CARDEMU_RAW_EXCHANGE

void setup()
{
  Serial.begin(115200);
  
  /* Register NDEF message to be sent to remote reader */
  T4T_NDEF_EMU_SetMessage((unsigned char*)NDEF_MESSAGE, sizeof(NDEF_MESSAGE), *NdefPush_Cb);

  // Initialize the NFC module
  Serial.print(F("Connecting Device . . ."));
  while (!(PN7150.begin(mode))) {
    Serial.print(F(" ."));
    delay(1000);
  }
  /* Start Discovery */
  while (PN7150.NxpNci_StartDiscovery(DiscoveryTechnologies, sizeof(DiscoveryTechnologies)) != NFC_SUCCESS) {
    Serial.println(F("Error: cannot start discovery"));
    delay(1000);
  }
  Serial.println(F("\nBegin ok!"));
}

void loop()
{
  Serial.println(F("\nWAITING FOR DEVICE DISCOVERY"));

  /* Wait until a peer is discovered */
  while (PN7150.NxpNci_WaitForDiscoveryNotification(&RfInterface) != NFC_SUCCESS);

  /* Is activated from remote T4T ? */
  if ((RfInterface.Interface == INTF_ISODEP) && ((RfInterface.ModeTech & MODE_MASK) == MODE_LISTEN)) {
    Serial.println(F(" - LISTEN MODE: Activated from remote Reader"));
#ifndef CARDEMU_RAW_EXCHANGE
    PN7150.NxpNci_ProcessCardMode(RfInterface);
#else
    PICC_ISO14443_4_scenario();
#endif
    Serial.println(F("READER DISCONNECTED"));
  } else {
    Serial.println(F("WRONG DISCOVERY"));
  }
}
