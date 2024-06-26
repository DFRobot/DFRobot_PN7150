# DFRobot_PN7150
* [English Version](./README.md)

![产品实物图](../../resources/images/PN7150.png)


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

1. 下载库至树莓派，要使用这个库，首先要将库下载到Raspberry Pi，命令下载方法如下:<br>
```python
sudo git clone https://github.com/DFRobot/DFRobot_PN7150
pip install smbus2
```
2. 打开并运行例程，要执行一个例程demo_x.py，请在命令行中输入python demo_x.py。例如，要执行 simpletest.py例程，你需要输入:<br>

```python
python simpletest.py 
或 
python2 simpletest.py 
或 
python3 simpletest.py
```


## 方法

```python
    #################### 简单 API ########################
    def scan(self, uid=""):
        """!
        @brief 扫描以确定是否存在 NFC 智能卡/标签。
        @param uid - NFC 卡的 UID。
        @return 布尔类型，操作结果
        """

    def read_uid(self):
        """!
        @brief 获取卡的 UID。
        @return 卡的 UID。
        """

    def read_data(self, block, index=None):
        """!
        @brief 从 MIFARE Classic NFC 智能卡/标签的指定块读取一个字节。
        @param block - 要读取的块号。
        @param index - 块的偏移量。
        @return 从卡中读取的一个字节。
        """

    def write_index_data(self, block, index, data):
        """!
        @brief 向 MIFARE Classic NFC 智能卡/标签写入一个字节。
        @param block - 要写入数据的页号。
        @param index - 数据的偏移量。
        @param data - 要写入的字节。
        @return 布尔类型，操作结果
        """

    def write_data(self, block, data):
        """!
        @brief 向 MIFARE Classic NFC 智能卡/标签写入一个块。
        @param block - 要写入的块号。
        @param data - 要写入的数据的缓冲区。
        @return 布尔类型，操作结果
        """

    def connect(self):
        """!
        @brief 连接功能。
        @return 布尔类型，操作结果
        """

    def mode_rw(self):
        """!
        @brief 模式读/写功能。
        @return 布尔类型，操作结果
        """

    #################### NFC 专用 API ########################
    def start_discovery_rw(self):
        """!
        @brief 开始发现读/写功能。
        @return 布尔类型，操作结果
        """

    def stop_discovery(self):
        """!
        @brief 停止发现功能。
        @return 布尔类型，操作结果
        """

    def wait_for_card(self):
        """!
        @brief 等待卡功能。
        @return 卡信息类
        """

    def tag_cmd(self, cmd, conn_id=0):
        """!
        @brief 标签命令功能。
        @param cmd - 标签命令
        @param conn_id - 连接 ID
        @return NFC 模块的数据
        """

```


## 兼容性

* RaspberryPi 版本

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python 版本

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2022/12/30 - 1.0.0 版本


## 创作者

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

