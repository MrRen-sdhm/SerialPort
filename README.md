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



### 4、附录

表1 c_iflag参数表

| 键 值   | 说 明                                             |
| ------- | ------------------------------------------------- |
| IGNBRK  | 忽略BREAK键输入                                   |
| BRKINT  | 如果设置了IGNBRK，BREAK键输入将被忽略             |
| IGNPAR  | 忽略奇偶校验错误                                  |
| PARMRK  | 标识奇偶校验错误                                  |
| INPCK   | 允许输入奇偶校验                                  |
| ISTRIP  | 去除字符的第8个比特                               |
| INLCR   | 将输入的NL（换行）转换成CR（回车）                |
| IGNCR   | 忽略输入的回车                                    |
| ICRNL   | 将输入的回车转化成换行（如果IGNCR未设置的情况下） |
| IUCLC   | 将输入的大写字符转换成小写字符（非POSIX）         |
| IXON    | 允许输出时对XON/XOFF流进行控制                    |
| IXANY   | 输入任何字符将重启停止的输出                      |
| IXOFF   | 允许输入时对XON/XOFF流进行控制                    |
| IMAXBEL | 当输入队列满的时候开始响铃                        |

表2 c_oflag参数

| 键 值  | 说 明                                                       |
| ------ | ----------------------------------------------------------- |
| OPOST  | 处理后输出                                                  |
| OLCUC  | 将输出的小写字符转换成大写字符（非POSIX）                   |
| ONLCR  | 将输出的NL（换行）转换成CR（回车）及NL（换行）              |
| OCRNL  | 将输出的CR（回车）转换成NL（换行）                          |
| ONOCR  | 第一行不输出回车符                                          |
| ONLRET | 不输出回车符                                                |
| OFILL  | 发送填充字符以延迟终端输出                                  |
| OFDEL  | 以ASCII码的DEL作为填充字符，如果未设置该参数，填充字符为NUL |
| NLDLY  | 换行输出延时，可以取NL0（不延迟）或NL1（延迟0.1s）          |
| CRDLY  | 回车延迟，取值范围为：CR0、CR1、CR2和 CR3                   |
| TABDLY | 水平制表符输出延迟，取值范围为：TAB0、TAB1、TAB2和TAB3      |
| BSDLY  | 空格输出延迟，可以取BS0或BS1                                |
| VTDLY  | 垂直制表符输出延迟，可以取VT0或VT1                          |
| FFDLY  | 换页延迟，可以取FF0或FF1                                    |

表3 c_cflag参数

| 键 值   | 说 明                                  |
| ------- | -------------------------------------- |
| CBAUD   | 波特率（4+1位）（非POSIX）             |
| CBAUDEX | 附加波特率（1位）（非POSIX）           |
| CSIZE   | 字符长度，取值范围为CS5、CS6、CS7或CS8 |
| CSTOPB  | 设置两个停止位                         |
| CREAD   | 使用接收器                             |
| PARENB  | 使用奇偶校验                           |
| PARODD  | 对输入使用奇偶校验，对输出使用偶校验   |
| HUPCL   | 关闭设备时挂起                         |
| CLOCAL  | 忽略调制解调器线路状态                 |
| CRTSCTS | 使用RTS/CTS流控制                      |

表4 c_lflag参数

| 键 值   | 说 明                                                   |
| ------- | ------------------------------------------------------- |
| ISIG    | 当输入INTR、QUIT、SUSP或DSUSP时，产生相应的信号         |
| ICANON  | 使用标准输入模式                                        |
| XCASE   | 在ICANON和XCASE同时设置的情况下，终端只使用大写         |
| ECHO    | 显示输入字符                                            |
| ECHOE   | 如果ICANON同时设置，ERASE将删除输入的字符               |
| ECHOK   | 如果ICANON同时设置，KILL将删除当前行                    |
| ECHONL  | 如果ICANON同时设置，即使ECHO没有设置依然显示换行符      |
| ECHOPRT | 如果ECHO和ICANON同时设置，将删除打印出的字符（非POSIX） |
| TOSTOP  | 向后台输出发送SIGTTOU信号                               |

表5 c_cc支持的控制字符

| 宏     | 说 明                        |
| ------ | ---------------------------- |
| VINTR  | Interrupt字符                |
| VQUIT  | Quit字符                     |
| VERASE | Erase字符                    |
| VKILL  | Kill字符                     |
| VEOF   | End-of-file字符              |
| VMIN   | 非规范模式读取时的最小字符数 |
| VEOL   | 附加的End-of-file字符        |
| VTIME  | 非规范模式读取时的超时时间   |
| VSTOP  | Stop字符                     |
| VSTART | Start字符                    |
| VSUSP  | Suspend字符                  |



### 5、注意

c_iflag 参数用来控制输入，即串口读取设置。

其中 ISTRIP 位用于去除字符的第8个比特，数据位为8位时需要清除此标志，切勿设置此位！

ISTRIP 位设置后会导致数据第8位丢失，例如发送 0x8E 则会接收到 0x0E ！！！

```
port_settings.c_iflag &= ~ISTRIP ;  // Clear the ISTRIP flag.
```