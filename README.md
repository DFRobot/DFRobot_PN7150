# DFRobot_PN7150
* [中文版](./README_CN.md)

![Product Image](./resources/images/PN7150.png)


## Product Link (https://www.dfrobot.com/)
    SKU: 


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary



## Installation

There two methods:

1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_GP8302 library from the Arduino Software Library Manager and download it.


## Methods

```C++

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
   * @fn scan
   * @brief Scan to determine whether there is a NFC smart card/tag with the specified UID.
   * @param nfcuid UID of the NFC card.
   * @return Boolean type, the result of operation
   * @retval true Finds a card with a specific UID
   * @retval false The card with a specific UID was not found
   */
  bool  scan(String nfcuid);

  /*!
   * @fn scan
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
    * @fn readData
    * @brief Read a byte from a specified block of a MIFARE Classic NFC smart card/tag.
    * @param block The number of the block to read from.
    * @param offset The offset of the block.
    * @return A byte read from the card.
    */
  uint8_t readData(int block, uint8_t offset);

  /*!
   * @fn readData
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
   * @fn writeData
   * @brief Write a byte to a MIFARE Classic NFC smart card/tag.
   * @param block The number of pages you want to writes the data.
   * @param num The offset of the data.
   * @param data The byte to be written.
   */
  void writeData(int block, uint8_t num, uint8_t data);

  /*!
   * @fn writeData
   * @brief Write a block to a MIFARE Classic NFC smart card/tag.
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
   * @param Data: pointer to data to transmit
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

```


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## History

- 2022/12/30 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

