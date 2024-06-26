# DFRobot_PN7150
* [中文版](./README_CN.md)

![Product Photo Show](../../resources/images/PN7150.png)


## Product Link (https://www.dfrobot.com/)
    SKU: SEN0539


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary


## Installation

1. Download the library to Raspberry Pi first before use.<br>

```python
sudo git clone https://github.com/DFRobot/DFRobot_PN7150
pip install smbus2
```

2. Open and run the routine. To execute a routine demo_x.py, enter python demo_x.py in the command line. For example, to execute the routine simpletest.py, you need to enter:<br>

```python
python simpletest.py
or 
python2 simpletest.py
or 
python3 simpletest.py
```


## Methods

```python
    #################### Simple API ########################
    def scan(self, uid=""):
        """!
        @brief Scan to determine whether there is a NFC smart card/tag.
        @param uid - UID of the NFC card.
        @return Boolean type, the result of operation
        """

    def read_uid(self):
        """!
        @brief Obtain the UID of the card .
        @return UID of the card.
        """

    def read_data(self, block, index=None):
        """!
        @brief Read a byte from a specified block of a MIFARE Classic NFC smart card/tag.
        @param block - The number of the block to read from.
        @param index - The offset of the block.
        @return Read from the card.
        """

    def write_index_data(self, block, index, data):
        """!
        @brief Write a byte to a MIFARE Classic NFC smart card/tag.
        @param block - The number of pages you want to writes the data.
        @param index - The offset of the data.
        @param data - The byte to be written.
        @return Boolean type, the result of operation
        """

    def write_data(self, block, data):
        """!
        @brief Write a block to a MIFARE Classic NFC smart card/tag.
        @param block - The number of the block to write to.
        @param data - The buffer of the data to be written.
        @return Boolean type, the result of operation
        """

    def connect(self):
        """!
        @brief Function connect.
        @return Boolean type, the result of operation
        """

    def mode_rw(self):
        """!
        @brief Function mode Read/Write.
        @return Boolean type, the result of operation
        """

    #################### NFC dedicated API ########################
    def start_discovery_rw(self):
        """!
        @brief Function Start Discovery Read/Write.
        @return Boolean type, the result of operation
        """

    def stop_discovery(self):
        """!
        @brief Function stop Discovery.
        @return Boolean type, the result of operation
        """

    def wait_for_card(self):
        """!
        @brief Function wait for Card.
        @return Card information class
        """

    def tag_cmd(self, cmd, conn_id=0):
        """!
        @brief Function tag cmd.
        @param cmd - tag cmd
        @param conn_id - conn_id
        @return Data of the nfc module
        """
```


## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2022/12/30 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

