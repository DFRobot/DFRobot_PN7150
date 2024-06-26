# -*- coding: utf-8 -*
""" 
  @file  simpletest.py
  @brief  Read the basic information of the card and read and write the card memory
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence  The MIT License (MIT)
  @author  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2024-03-14
  @url https://github.com/DFRobot/DFRobot_PN7150
"""
from __future__ import print_function
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))

from DFRobot_PN7150 import *
from time import sleep

"""
  @brief Module I2C communication init
  @param i2c_addr - I2C communication address
  @param bus - I2C bus
"""
PN7150 = DFRobot_PN7150()


def setup():
    assert PN7150.connect()
    print("Connected.")

    assert PN7150.mode_rw()
    print("Switched to read/write mode.")


def loop():
    PN7150.write_index_data(1, 1, 200)
    print(PN7150.read_data(1))
    print(PN7150.read_data(1, 1))
    print(PN7150.read_uid())
    print(PN7150.scan("acee50e3"))
    print(PN7150.scan())
    print("---------------------")


if __name__ == "__main__":
    setup()
    while True:
        loop()
