cmake_minimum_required(VERSION 3.1)
project(SerialPort)

set(CMAKE_CXX_STANDARD 14)

add_executable(SerialPort1 main1.cpp serial_driver.cpp serial_driver.h)

add_executable(SerialPort2 main2.cpp SerialPort.cpp SerialPort.h SerialPortConstants.h)