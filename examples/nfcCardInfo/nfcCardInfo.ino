/*!
 * @file nfcCardInfo.ino
 * @brief read the basic information of the card
 * @details  This demo runs on the arduino platform.
            Download this demo to read the basic information of the card,
            including UID, manufacturer, storage space, RF technology etc.

            Suported NFC card/tag:
            1.MIFARE Classic S50/S70
            2.NTAG213/215/216
            3.MIFARE Ultralight
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT license (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2024-01-29
 * @url https://github.com/DFRobot/DFRobot_PN7150
*/
#include "DFRobot_PN7150.h"

/* Discovery loop configuration according to the targeted modes of operation */
unsigned char DiscoveryTechnologies[] = {
    MODE_POLL | TECH_PASSIVE_NFCA,
    MODE_POLL | TECH_PASSIVE_NFCF,
    MODE_POLL | TECH_PASSIVE_NFCB,
    MODE_POLL | TECH_PASSIVE_15693,
};

/* Mode configuration according to the targeted modes of operation */
unsigned char mode = NXPNCI_MODE_RW;

// #define PRINT_BUF(x,y,z)  {unsigned int loop; printf(x); for(loop=0;loop<z;loop++) printf("%.2x ", y[loop]); printf("\n");}
#define PRINT_BUF(x,y,z)  {Serial.print(x); for(unsigned int loop=0; loop<z; loop++) { \
                            Serial.print(y[loop], HEX); Serial.print(F(" ")); } Serial.println(); }
char tmpPrint[60];

DFRobot_PN7150_I2C PN7150;
DFRobot_PN7150_I2C::NxpNci_RfIntf_t RfInterface;

void setup()
{
  Serial.begin(115200);
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

  if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL) {
    task_nfc_reader(RfInterface);
  } else {
    Serial.println(F("WRONG DISCOVERY"));
  }
}

void displayCardInfo(DFRobot_PN7150_I2C::NxpNci_RfIntf_t RfIntf)
{
  switch (RfIntf.Protocol) {
  case PROT_T1T:
  case PROT_T2T:
  case PROT_T3T:
  case PROT_ISODEP:
    Serial.print(F(" - POLL MODE: Remote T"));
    Serial.print(RfIntf.Protocol);
    Serial.println(F("T card activated"));
    break;
  case PROT_T5T:
    Serial.println(F(" - POLL MODE: Remote T5T card activated"));
    break;
  case PROT_MIFARE:
    Serial.println(F(" - POLL MODE: Remote MIFARE card activated"));
    break;
  default:
    Serial.println(F(" - POLL MODE: Undetermined target"));
    return;
  }

  switch (RfIntf.ModeTech) {
  case (MODE_POLL | TECH_PASSIVE_NFCA):
    memset(tmpPrint, 0, sizeof(tmpPrint));
    sprintf(tmpPrint, "\tSENS_RES = 0x%.2x 0x%.2x", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
    Serial.println(tmpPrint);
    PRINT_BUF("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
    if (RfIntf.Info.NFC_APP.SelResLen != 0) {
      memset(tmpPrint, 0, sizeof(tmpPrint));
      sprintf(tmpPrint, "\tSEL_RES = 0x%.2x", RfIntf.Info.NFC_APP.SelRes[0]);
      Serial.println(tmpPrint);
    }
    break;

  case (MODE_POLL | TECH_PASSIVE_NFCB):
    if (RfIntf.Info.NFC_BPP.SensResLen != 0) PRINT_BUF("\tSENS_RES = ", RfIntf.Info.NFC_BPP.SensRes, RfIntf.Info.NFC_BPP.SensResLen);
    break;

  case (MODE_POLL | TECH_PASSIVE_NFCF):
    memset(tmpPrint, 0, sizeof(tmpPrint));
    sprintf(tmpPrint, "\tBitrate = %s", (RfIntf.Info.NFC_FPP.BitRate == 1) ? "212" : "424");
    Serial.println(tmpPrint);
    if (RfIntf.Info.NFC_FPP.SensResLen != 0) PRINT_BUF("\tSENS_RES = ", RfIntf.Info.NFC_FPP.SensRes, RfIntf.Info.NFC_FPP.SensResLen);
    break;

  case (MODE_POLL | TECH_PASSIVE_15693):
    PRINT_BUF("\tID = ", RfIntf.Info.NFC_VPP.ID, sizeof(RfIntf.Info.NFC_VPP.ID));
    memset(tmpPrint, 0, sizeof(tmpPrint));
    sprintf(tmpPrint, "\tAFI = 0x%.2x\n\tDSFID = 0x%.2x", RfIntf.Info.NFC_VPP.AFI, RfIntf.Info.NFC_VPP.DSFID);
    Serial.println(tmpPrint);
    break;

  default:
    break;
  }
}

void task_nfc_reader(DFRobot_PN7150_I2C::NxpNci_RfIntf_t RfIntf)
{
  /* For each discovered cards */
  while (1) {
    /* Display detected card information */
    displayCardInfo(RfIntf);

    /* If more cards (or multi-protocol card) were discovered (only same technology are supported) select next one */
    if (RfIntf.MoreTags) {
      if (PN7150.NxpNci_ReaderActivateNext(&RfIntf) == NFC_ERROR) break;
    }
    /* Otherwise leave */
    else break;
  }

  /* Wait for card removal */
  PN7150.NxpNci_ProcessReaderMode(RfIntf, PN7150.PRESENCE_CHECK);

  Serial.println(F("CARD REMOVED"));

  /* Restart discovery loop */
  PN7150.NxpNci_StopDiscovery();
  while (PN7150.NxpNci_StartDiscovery(DiscoveryTechnologies, sizeof(DiscoveryTechnologies)));
}