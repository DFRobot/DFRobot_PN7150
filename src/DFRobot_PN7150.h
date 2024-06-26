/*!
 * @file  DFRobot_PN7150.h
 * @brief  Basic structure of DFRobot_PN7150 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-12-30
 * @url  https://github.com/DFRobot/DFRobot_PN7150
*/
#ifndef DFRobot_PN7150_H
#define DFRobot_PN7150_H

#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <string.h>
#include <Wire.h>

#include <ndef_helper.h>

#define CARDEMU_SUPPORT
#define P2P_SUPPORT
#define RW_SUPPORT
/********************************** NxpNci.h **********************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CARDEMU_SUPPORT
#include <NdefLibrary/T4T_NDEF_emu.h>   // NdefLibrary
#endif

#ifdef P2P_SUPPORT
#include <NdefLibrary/P2P_NDEF.h>
#endif

#ifdef RW_SUPPORT
#include <NdefLibrary/RW_NDEF.h>
#include <NdefLibrary/RW_NDEF_T3T.h>
#endif

#define NXPNCI_SUCCESS      NFC_SUCCESS
#define NXPNCI_ERROR        NFC_ERROR

// #define NCI_DEBUG
#ifdef NCI_DEBUG
#include <stdio.h>
#define NCI_PRINT(...)        {Serial.println(__VA_ARGS__);}
  extern unsigned short debug_loop;
#define NCI_PRINT_LOOP(x,y)   {for(debug_loop=0; debug_loop<y; debug_loop++) {Serial.print(y[debug_loop], HEX); Serial.print(" ");}}
#ifdef _WIN32
#define NCI_PRINT_BUF(x,y,z)  {Serial.print(x); \
                               for(debug_loop=0;debug_loop<z;debug_loop++) {Serial.print(y[debug_loop], HEX); Serial.print(" ");} \
                               Serial.println(); \
}
#else
#define NCI_PRINT_BUF(x,y,z)  {char tmp[200]; unsigned int loop; sprintf(tmp, x); \
                               for(loop=0;loop<(z<30?z:30);loop++) sprintf(tmp+7+(loop*3), "%.2x ", y[loop]); \
                               if(loop==30) sprintf(tmp+7+(loop*3), "...\n"); \
                               else sprintf(tmp+7+(loop*3), "\n"); \
                               Serial.print(tmp);}
#endif
#else
#define NCI_PRINT(...)
#define NCI_PRINT_LOOP(x,y)
#define NCI_PRINT_BUF(x,y,z)
#endif

#ifdef __cplusplus
}
#endif

// #define ENABLE_DBG   //!< Open this macro and you can see the details of the program
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
// #define DBG(...) { Serial.print(__LINE__); Serial.println(" : ");}
#else
#define DBG(...)
#endif

#define PN7150_ADDR                 uint8_t(0x28)   //!< I2C address

/********************************** tml.h **********************************/
#define TIMEOUT_INFINITE	1000
#if defined(ESP32)
#define TIMEOUT_100MS			1500   // The requestFrom of the SDK of Le Xin esp32 timed out for a long time (1s).
#define TIMEOUT_1S				1500
#define TIMEOUT_2S				2000
#else
#define TIMEOUT_100MS			100
#define TIMEOUT_1S				1000
#define TIMEOUT_2S				2000
#endif
/***** NFC dedicated interface ****************************************/

/*
 * Status code definition used as API returned values
 */
#define NFC_SUCCESS          0
#define NFC_ERROR            1

 /*
  * Flag definition used as Interface values
  */
#define INTF_UNDETERMINED    0x0
#define INTF_FRAME           0x1
#define INTF_ISODEP          0x2
#define INTF_NFCDEP          0x3
#define INTF_TAGCMD          0x80

  /*
   * Flag definition used as Protocol values
   */
#define PROT_UNDETERMINED    0x0
#define PROT_T1T             0x1
#define PROT_T2T             0x2
#define PROT_T3T             0x3
#define PROT_ISODEP          0x4
#define PROT_NFCDEP          0x5
#define PROT_T5T             0x6
#define PROT_MIFARE          0x80

   /*
    * Flag definition used as Mode values
    */
#define MODE_POLL            0x00
#define MODE_LISTEN          0x80
#define MODE_MASK            0xF0

    /*
     * Flag definition used as Technologies values
     */
#define TECH_PASSIVE_NFCA    0
#define TECH_PASSIVE_NFCB    1
#define TECH_PASSIVE_NFCF    2
#define TECH_ACTIVE_NFCA     3
#define TECH_ACTIVE_NFCF     5
#define TECH_PASSIVE_15693   6

     /*
      * Flag definition used for NFC library configuration
      */
#define NXPNCI_MODE_CARDEMU    (1<<0)
#define NXPNCI_MODE_P2P        (1<<1)
#define NXPNCI_MODE_RW         (1<<2)

class DFRobot_PN7150
{
public:
  unsigned char _mode;

  /*
   * Definition of operations handled when processing Reader mode
   */
  typedef enum
  {
#ifndef NO_NDEF_SUPPORT
    READ_NDEF,
    WRITE_NDEF,
#endif
    PRESENCE_CHECK
  } NxpNci_RW_Operation_t;

  /*
   * Definition of discovered remote device properties information
   */
   /* POLL passive type A */
  typedef struct
  {
    unsigned char SensRes[2];
    unsigned char NfcIdLen;
    unsigned char NfcId[10];
    unsigned char SelResLen;
    unsigned char SelRes[1];
    unsigned char RatsLen;
    unsigned char Rats[20];
  } NxpNci_RfIntf_info_APP_t;

  /* POLL passive type B */
  typedef struct
  {
    unsigned char SensResLen;
    unsigned char SensRes[12];
    unsigned char AttribResLen;
    unsigned char AttribRes[17];
  } NxpNci_RfIntf_info_BPP_t;

  /* POLL passive type F */
  typedef struct
  {
    unsigned char BitRate;
    unsigned char SensResLen;
    unsigned char SensRes[18];
  } NxpNci_RfIntf_info_FPP_t;

  /* POLL passive type ISO15693 */
  typedef struct
  {
    unsigned char AFI;
    unsigned char DSFID;
    unsigned char ID[8];
  } NxpNci_RfIntf_info_VPP_t;

  typedef union
  {
    NxpNci_RfIntf_info_APP_t NFC_APP;
    NxpNci_RfIntf_info_BPP_t NFC_BPP;
    NxpNci_RfIntf_info_FPP_t NFC_FPP;
    NxpNci_RfIntf_info_VPP_t NFC_VPP;
  } NxpNci_RfIntf_Info_t;

  /*
   * Definition of discovered remote device properties
   */
  typedef struct
  {
    unsigned char Interface;
    unsigned char Protocol;
    unsigned char ModeTech;
    bool MoreTags;
    NxpNci_RfIntf_Info_t Info;
  } NxpNci_RfIntf_t;

public:
  uint8_t nfcUid[4];
  uint8_t blockData[16];

public:
  /**
   * @fn DFRobot_PN7150
   * @brief Constructor
   * @return None
   */
  DFRobot_PN7150();

  /**
   * @fn begin
   * @brief Init function
   * @param mode nfc mode
   * @n     specifies which modes to be configured (see NXPNCI_MODE_xxx flags)
   * @return bool type, true if successful, false if error
   */
  virtual bool begin(unsigned char mode) = 0;

  /**********************************************************************/

  /***** Simple API  **********************************************/

  /*!
   * @fn scan(String nfcuid)
   * @brief Scan to determine whether there is a NFC smart card/tag with the specified UID.
   * @param nfcuid UID of the NFC card.
   * @return Boolean type, the result of operation
   * @retval true Finds a card with a specific UID
   * @retval false The card with a specific UID was not found
   */
  bool  scan(String nfcuid);

  /*!
   * @fn scan(void)
   * @brief Scan to determine whether there is a NFC smart card/tag.
   * @return Boolean type, the result of operation
   * @retval true means find out a MIFARE Classic card.
   * @retval false no card
   */
  bool  scan(void);

  /*!
   * @fn readUid
   * @brief Obtain the UID of the card .
   * @return UID of the card.
   */
  String  readUid();

   /*!
    * @fn readData(int block, uint8_t offset)
    * @brief Read a byte from a specified block of a MIFARE Classic NFC smart card/tag.
    * @param block The number of the block to read from.
    * @param offset The offset of the block.
    * @return A byte read from the card.
    */
  uint8_t readData(int block, uint8_t offset);

  /*!
   * @fn readData(uint8_t* buffer, uint8_t block)
   * @brief Read a block from a MIFARE Classic NFC smart card/tag (16 bytes each block).
   * @param buffer The buffer of the read data.
   * @param block The number of the block to read from.
   * @return Status code.
   * @retval 1 successfully read data
   * @retval -1 Failed to read data
   */
  uint8_t readData(uint8_t* buffer, uint8_t block);
  String readData(int page);

  /*!
   * @fn writeData(int block, uint8_t num, uint8_t data)
   * @brief Write a byte to a MIFARE Classic NFC smart card/tag.
   * @param block The number of pages you want to writes the data.
   * @param num The offset of the data.
   * @param data The byte to be written.
   */
  void writeData(int block, uint8_t num, uint8_t data);

  /*!
   * @fn writeData(int block, uint8_t data[])
   * @brief Write a block to a MIFARE Classic NFC smart card/tag..
   * @param block The number of the block to write to.
   * @param data The buffer of the data to be written.
   */
  bool  writeData(int block, uint8_t data[]);

  /**********************************************************************/

  /***** NFC dedicated API **********************************************/

  /**
   * @fn NxpNci_Connect
   * @brief Open connection to the NXP-NCI device
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_Connect(void);

  /**
   * @fn NxpNci_Disconnect
   * @brief Close connection to the NXP-NCI device
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_Disconnect(void);

  /**
   * @fn NxpNci_GetFwVersion
   * @brief Get NXP-NCI device FW version (3 bytes)
   * @return None
   */
  void NxpNci_GetFwVersion(unsigned char fw[3]);

  /**
   * @fn NxpNci_ConfigureSettings
   * @brief Configure NXP-NCI device settings
   * @note Related settings are defined in Nfc_settings.h header file
   * @n    To be called after NxpNci_Connect() and prior to NxpNci_ConfigureMode() APIs
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ConfigureSettings(void);

  /**
   * @fn NxpNci_ConfigureMode
   * @brief Configure NXP-NCI device mode
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ConfigureMode(void);

  /**
   * @fn NxpNci_ConfigureParams
   * @brief Configure NXP-NCI device parameters
   * @param pCmd: NCI CORE_SET_CONFIG_CMD frame
   * @param CmdSize: NCI CORE_SET_CONFIG_CMD frame size
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ConfigureParams(unsigned char* pCmd, unsigned short CmdSize);

  /**
   * @fn NxpNci_StartDiscovery
   * @brief Start NFC Discovery loop for remote NFC device detection
   * @param pTechTab: list of NFC technologies to look for (see TECH_xxx_xxx flags)
   * @param TechTabSize: number of items in the list
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_StartDiscovery(unsigned char* pTechTab, unsigned char TechTabSize);

  /**
   * @fn NxpNci_StopDiscovery
   * @brief Stop NFC Discovery loop
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_StopDiscovery(void);

  /**
   * @fn NxpNci_WaitForDiscoveryNotification
   * @brief Wait until remote NFC device is discovered
   * @param pRfIntf: filled with discovered NFC remote device properties
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_WaitForDiscoveryNotification(NxpNci_RfIntf_t* pRfIntf);

  /**********************************************************************/

  /***** Reader/writer dedicated APIs ***********************************/
#ifdef RW_SUPPORT
  /**
   * @fn NxpNci_ProcessReaderMode
   * @brief Process the operation identified as parameter with discovered remote NFC tag (function is blocking until the end of the operation)
   * @param RfIntf: discovered NFC device properties
   * @param Operation: select operation to be done with the remote NFC tag
   * @n     - READ_NDEF: extract NDEF message from the tag, previously registered callback function will be called whenever complete NDEF message is found.
   * @n     - WRITE_NDEF: write previously registered NDEF message to the tag
   * @n     - PRESENCE_CHECK: perform presence check until tag has been removed (function is blocking until card is removed)
   * @return None
   */
  void NxpNci_ProcessReaderMode(NxpNci_RfIntf_t RfIntf, NxpNci_RW_Operation_t Operation);

  /**
   * @fn NxpNci_ReaderTagCmd
   * @brief Perform RAW transceive operation (send then receive) with the remote tag
   * @param pCommand: pointer to the command to send
   * @param CommandSize: command size
   * @param pAnswer: pointer to buffer for getting the response
   * @param pAnswerSize: response size
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ReaderTagCmd(unsigned char* pCommand, unsigned char CommandSize, unsigned char* pAnswer, unsigned char* pAnswerSize);

  /**
   * @fn NxpNci_ReaderActivateNext
   * @brief Perform activation of the next tag (in case of multiple tag detection or multi-protocol tag)
   * @param pRfIntf: filled with discovered NFC remote device properties
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ReaderActivateNext(NxpNci_RfIntf_t* pRfIntf);

  /**
   * @fn NxpNci_ReaderReActivate
   * @brief Perform deactivation then reactivation of the current tag
   * @param pRfIntf: filled with discovered NFC remote device properties
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_ReaderReActivate(NxpNci_RfIntf_t* pRfIntf);
#endif
  /**********************************************************************/

  /***** Card Emulation dedicated APIs **********************************/
#ifdef CARDEMU_SUPPORT

  /**
   * @fn NxpNci_ProcessCardMode
   * @brief Expose the previously registered NDEF message to discovered remote NFC reader (function is blocking until the remote reader is lost):
   * @param RfIntf: discovered NFC device properties
   * @return None
   */
  void NxpNci_ProcessCardMode(NxpNci_RfIntf_t RfIntf);

  /**
   * @fn NxpNci_CardModeReceive
   * @brief Perform RAW reception of data from the remote reader
   * @param pData: pointer to buffer for getting the data
   * @param pDataSize: received data size
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_CardModeReceive(unsigned char* pData, unsigned char* pDataSize);

  /**
   * @fn NxpNci_CardModeSend
   * @brief Perform RAW transmission of data from the remote reader
   * @param pData: pointer to data to transmit
   * @param DataSize: size of data to transmit
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_CardModeSend(unsigned char* pData, unsigned char DataSize);
#endif
  /**********************************************************************/

  /***** P2P dedicated APIs *********************************************/
#ifdef P2P_SUPPORT
  /**
   * @fn NxpNci_ProcessP2pMode
   * @brief Process P2P operation (function is blocking until the remote peer is lost):
   * @n        SNEP server to allow receiving NDEF message from remote NFC P2P device
   * @n        SNEP client to send previously registered NDEF message
   * @param RfIntf: discovered NFC device properties
   * @return None
   */
  void NxpNci_ProcessP2pMode(NxpNci_RfIntf_t RfIntf);
#endif
  /**********************************************************************/

protected:
  /***** Factory Test dedicated APIs *********************************************/
#ifdef NFC_FACTORY_TEST

/*
 * Definition of technology types
 */
  typedef enum
  {
    NFC_A,
    NFC_B,
    NFC_F
  } NxpNci_TechType_t;

  /*
   * Definition of bitrate
   */
  typedef enum
  {
    BR_106,
    BR_212,
    BR_424,
    BR_848
  } NxpNci_Bitrate_t;

  /**
   * @fn NxpNci_FactoryTest_Prbs
   * @brief Set the NFC Controller in continuous modulated field mode
   * @param type: modulation type
   * @param bitrate: modulation bitrate
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_FactoryTest_Prbs(NxpNci_TechType_t type, NxpNci_Bitrate_t bitrate);

  /**
   * @fn NxpNci_FactoryTest_RfOn
   * @brief Set the NFC Controller in continuous unmodulated field mode
   * @return NFC_SUCCESS or NFC_ERROR
   */
  bool NxpNci_FactoryTest_RfOn(void);

#endif
  /********************************************************************************/

protected:

  virtual void tml_Connect(void) = 0;
  virtual void tml_Disconnect(void) = 0;
  virtual void tml_Send(uint8_t* pBuffer, uint16_t BufferLen, uint16_t* pBytesSent) = 0;
  virtual void tml_Receive(uint8_t* pBuffer, uint16_t BufferLen, uint16_t* pBytes, uint16_t timeout) = 0;

private:
  bool NxpNci_CheckDevPres(void);
  bool NxpNci_WaitForReception(uint8_t* pRBuff, uint16_t RBuffSize, uint16_t* pBytesread, uint16_t timeout);
  bool NxpNci_HostTransceive(uint8_t* pTBuff, uint16_t TbuffLen, uint8_t* pRBuff, uint16_t RBuffSize, uint16_t* pBytesread);
  void NxpNci_FillInterfaceInfo(NxpNci_RfIntf_t* pRfIntf, uint8_t* pBuf);
#ifdef RW_SUPPORT
#ifndef NO_NDEF_SUPPORT
  void NxpNci_ReadNdef(NxpNci_RfIntf_t RfIntf);
  void NxpNci_WriteNdef(NxpNci_RfIntf_t RfIntf);
#endif
  void NxpNci_PresenceCheck(NxpNci_RfIntf_t RfIntf);
#endif
};

/**************************************************************************
                          Subclass using I2C interface for communication
 **************************************************************************/

class DFRobot_PN7150_I2C : public DFRobot_PN7150
{
public:
  typedef enum { ERROR = 0, SUCCESS = !ERROR } Status;
  typedef int32_t status_t;

public:
  /**
   * @fn DFRobot_PN7150_I2C
   * @brief Constructor
   * @param pWire I2C bus pointer object, construct the device. You can pass a parameter to it or not, default to be Wire
   * @param i2cAddr 7bits I2C address, the first three bits determine the value of the address, default to 0x50
   * @return None
   */
  DFRobot_PN7150_I2C(TwoWire* pWire = &Wire, uint8_t i2cAddr = PN7150_ADDR);

  /**
   * @fn begin
   * @brief Subclass init function
   * @param mode nfc mode
   * @return Bool type, true for success, false for failure
   */
  virtual bool begin(unsigned char mode = NXPNCI_MODE_RW);

protected:
  void tml_Connect(void);
  void tml_Disconnect(void);
  void tml_Send(uint8_t* pBuffer, uint16_t BufferLen, uint16_t* pBytesSent);
  void tml_Receive(uint8_t* pBuffer, uint16_t BufferLen, uint16_t* pBytes, uint16_t timeout);

private:
  status_t I2C_WRITE(uint8_t* pBuff, uint16_t buffLen);
  status_t I2C_READ(uint8_t* pBuff, uint16_t buffLen);
  Status tml_Init(void);
  Status tml_DeInit(void);
  Status tml_Reset(void);
  Status tml_Tx(uint8_t* pBuff, uint16_t buffLen);
  Status tml_Rx(uint8_t* pBuff, uint16_t buffLen, uint16_t* pBytesRead);
  Status tml_WaitForRx(uint32_t timeout);

private:
#define  _PN7150_IRQ      (27)
  TwoWire* _pWire;   // Pointer to I2C communication method
  uint8_t _deviceAddr;   // Address of the device for I2C communication
};

#endif
