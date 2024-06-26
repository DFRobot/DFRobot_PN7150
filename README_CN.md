# DFRobot_PN7150
* [English Version](./README.md)

![产品实物图](./resources/images/PN7150.png)


## 产品链接 (https://www.dfrobot.com.cn/)
    SKU: 


## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述


## 库安装

这里有2种安装方法：

1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_PN7150 库。


## 方法

```C++

  /**
   * @fn begin
   * @brief 初始化函数
   * @param mode nfc 模式
   * @n     指定要配置的模式 (参见 NXPNCI_MODE_xxx 标志)
   * @return bool类型，成功返回true，错误返回false
   */
  virtual bool begin(unsigned char mode) = 0;

  /**********************************************************************/
  /***** 简单 API **************************************************/

  /*!
   * @fn scan
   * @brief 扫描以确定是否存在具有指定 UID 的 NFC 智能卡/标签。
   * @param nfcuid NFC 卡的 UID。
   * @return 布尔类型，操作结果
   * @retval true 找到具有特定 UID 的卡
   * @retval false 未找到具有特定 UID 的卡
   */
  bool  scan(String nfcuid);

  /*!
   * @fn scan
   * @brief 扫描以确定是否存在 NFC 智能卡/标签。
   * @return 布尔类型，操作结果
   * @retval true 找到 MIFARE Classic 卡
   * @retval false 无卡
   */
  bool  scan(void);

  /*!
   * @fn readUid
   * @brief 获取卡的 UID。
   * @return 卡的 UID。
   */
  String  readUid();

   /*!
    * @fn readData
    * @brief 从 MIFARE Classic NFC 智能卡/标签的指定块读取一个字节。
    * @param block 要读取的块号。
    * @param offset 块的偏移量。
    * @return 从卡中读取的一个字节。
    */
  uint8_t readData(int block, uint8_t offset);

  /*!
   * @fn readData
   * @brief 从 MIFARE Classic NFC 智能卡/标签中读取一个块（每个块 16 字节）。
   * @param buffer 读取数据的缓冲区。
   * @param block 要读取的块号。
   * @return 状态码。
   * @retval 1 成功读取数据
   * @retval -1 读取数据失败
   */
  uint8_t readData(uint8_t* buffer, uint8_t block);
  String readData(int page);

  /*!
   * @fn writeData
   * @brief 向 MIFARE Classic NFC 智能卡/标签写入一个字节。
   * @param block 要写入数据的页号。
   * @param num 数据的偏移量。
   * @param data 要写入的字节。
   */
  void writeData(int block, uint8_t num, uint8_t data);

  /*!
   * @fn writeData
   * @brief 向 MIFARE Classic NFC 智能卡/标签写入一个块。
   * @param block 要写入的块号。
   * @param data 要写入的数据的缓冲区。
   */
  bool  writeData(int block, uint8_t data[]);

  /**********************************************************************/

  /***** NFC专用API **********************************************/

  /**
   * @fn NxpNci_Connect
   * @brief 打开与NXP-NCI设备的连接
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_Connect(void);

  /**
   * @fn NxpNci_Disconnect
   * @brief 关闭与NXP-NCI设备的连接
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_Disconnect(void);

  /**
   * @fn NxpNci_GetFwVersion
   * @brief 获取NXP-NCI设备的FW版本（3个字节）
   * @return None
   */
  void NxpNci_GetFwVersion(unsigned char fw[3]);

  /**
   * @fn NxpNci_ConfigureSettings
   * @brief 配置NXP-NCI设备的设置
   * @note 相关设置定义在Nfc_settings.h头文件中
   * @n    在调用NxpNci_Connect()之后和调用NxpNci_ConfigureMode() API之前调用
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ConfigureSettings(void);

  /**
   * @fn NxpNci_ConfigureMode
   * @brief 配置NXP-NCI设备模式
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ConfigureMode(void);

  /**
   * @fn NxpNci_ConfigureParams
   * @brief 配置NXP-NCI设备的参数
   * @param pCmd: NCI CORE_SET_CONFIG_CMD 帧
   * @param CmdSize: NCI CORE_SET_CONFIG_CMD 帧大小
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ConfigureParams(unsigned char* pCmd, unsigned short CmdSize);

  /**
   * @fn NxpNci_StartDiscovery
   * @brief 开始NFC发现循环以检测远程NFC设备
   * @param pTechTab: 要查找的NFC技术列表（参见TECH_xxx_xxx标志）
   * @param TechTabSize: 列表中的项数
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_StartDiscovery(unsigned char* pTechTab, unsigned char TechTabSize);

  /**
   * @fn NxpNci_StopDiscovery
   * @brief 停止NFC发现循环
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_StopDiscovery(void);

  /**
   * @fn NxpNci_WaitForDiscoveryNotification
   * @brief 等待远程NFC设备被发现
   * @param pRfIntf: 填充发现的NFC远程设备属性
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_WaitForDiscoveryNotification(NxpNci_RfIntf_t* pRfIntf);

  /**********************************************************************/

  /***** 读/写专用api ***********************************/
#ifdef RW_SUPPORT
  /**
   * @fn NxpNci_ProcessReaderMode
   * @brief 处理与发现的远程NFC标签标识为参数的操作（函数会阻塞直到操作结束）
   * @param RfIntf: 发现的NFC设备属性
   * @param Operation: 选择与远程NFC标签执行的操作
   * @n     - READ_NDEF: 从标签提取NDEF消息，一旦找到完整的NDEF消息，之前注册的回调函数将被调用。
   * @n     - WRITE_NDEF: 将之前注册的NDEF消息写入标签
   * @n     - PRESENCE_CHECK: 执行存在检查，直到标签被移除（函数会阻塞直到卡片被移除）
   * @return None
   */
  void NxpNci_ProcessReaderMode(NxpNci_RfIntf_t RfIntf, NxpNci_RW_Operation_t Operation);

  /**
   * @fn NxpNci_ReaderTagCmd
   * @brief 对远程标签执行RAW收发操作（先发送后接收）
   * @param pCommand: 指向要发送的命令的指针
   * @param CommandSize: 命令大小
   * @param pAnswer: 指向用于获取响应的缓冲区的指针
   * @param pAnswerSize: 响应大小
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ReaderTagCmd(unsigned char* pCommand, unsigned char CommandSize, unsigned char* pAnswer, unsigned char* pAnswerSize);

  /**
   * @fn NxpNci_ReaderActivateNext
   * @brief 激活下一个标签（在检测到多个标签或多协议标签的情况下）
   * @param pRfIntf: 用于填充发现的NFC远程设备属性
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ReaderActivateNext(NxpNci_RfIntf_t* pRfIntf);

  /**
   * @fn NxpNci_ReaderReActivate
   * @brief 对当前标签执行去激活然后重新激活操作
   * @param pRfIntf: 用于填充发现的NFC远程设备属性
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_ReaderReActivate(NxpNci_RfIntf_t* pRfIntf);
#endif
  /**********************************************************************/

  /***** Card Emulation dedicated APIs **********************************/
#ifdef CARDEMU_SUPPORT

  /**
   * @fn NxpNci_ProcessCardMode
   * @brief 将先前注册的NDEF消息暴露给发现的远程NFC读取器（该函数在远程读取器丢失之前一直阻塞）
   * @param RfIntf: 发现的NFC设备属性
   * @return None
   */
  void NxpNci_ProcessCardMode(NxpNci_RfIntf_t RfIntf);

  /**
   * @fn NxpNci_CardModeReceive
   * @brief 从远程读取器执行RAW数据接收
   * @param pData: 指向用于获取数据的缓冲区的指针
   * @param pDataSize: 接收到的数据大小
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_CardModeReceive(unsigned char* pData, unsigned char* pDataSize);

  /**
   * @fn NxpNci_CardModeSend
   * @brief 执行从远程读取器的RAW数据传输
   * @param Data: 指向要传输的数据的指针
   * @param DataSize: 要传输的数据大小
   * @return NFC_SUCCESS 或 NFC_ERROR
   */
  bool NxpNci_CardModeSend(unsigned char* pData, unsigned char DataSize);
#endif
  /**********************************************************************/

  /***** P2P dedicated APIs *********************************************/
#ifdef P2P_SUPPORT
  /**
   * @fn NxpNci_ProcessP2pMode
   * @brief 处理P2P操作（该函数在远程对等端丢失之前一直阻塞）：
   * @n        SNEP服务器，用于从远程NFC P2P设备接收NDEF消息
   * @n        SNEP客户端，用于发送先前注册的NDEF消息
   * @param RfIntf: 发现的NFC设备属性
   * @return None
   */
  void NxpNci_ProcessP2pMode(NxpNci_RfIntf_t RfIntf);
#endif
  /**********************************************************************/

```


## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## 历史

- 2022/12/30 - 1.0.0 版本


## 创作者

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

