# SerialPort

### 1、介绍

此存储库包含两个Linux C++串口驱动实现：

- 简洁版本，基于C++11
- 易用版本，基于C++14，提取自[libserial](https://github.com/crayzeewulf/libserial)



### 2、编译

```
# 克隆存储库
git clone https://github.com/MrRen-sdhm/SerialPort.git

# 编译
mkdir build
cd build
cmake ..
make -j8
```



### 3、测试

1\. 使用软件模拟串口

```
# 安装socat
sudo apt-get install socat
# 设置/dev/ttyS0和/dev/ttyS1为测试串口
sudo socat -d -d pty,raw,echo=0,link=/dev/ttyS0 pty,raw,echo=0,link=/dev/ttyS1
```

2\. 安装cutecom

```
sudo apt-get install cutecom
```

3\. 测试串口收发

串口配置：波特率115200, 数据位8位, 偶校验, 1位停止位。

测试程序会先发送数据到/dev/ttyS1，可以在cutecom中查看收到的数据。接下来在cutecom中发送数据，终端输出接收到的数据后退出。

```
# 以管理员身份打开cutecom，并打开串口/dev/ttyS1，配置好串口
sudo cutecom

# 测试简易版本串口收发程序
sudo ./SerialPort1

# 测试易用版本串口收发程序
sudo ./SerialPort2
```