//
// Created by MrRen-sdhm on 20-05-30.
//

#include "serial_driver.h"

SerialDriver::SerialDriver()
{

}

SerialDriver::~SerialDriver()
{

}

bool SerialDriver::OpenPort(const std::string &_port, int _baudrate, DataBits _dbits, Parity _parity, StopBits _stopbits)
{
	char parity;
	int databits, stopbits;
	const char *port = _port.c_str();
    PortState = false;
    PortName = "";
	switch(_dbits)
	{
		case Data7: databits = 7;break;
		case Data8: databits = 8;break;
		default: databits = 8;break;
	}

	switch(_parity)
	{
		case Even: parity = 'E';break;
		case Odd: parity = 'O';break;
		case None: parity = 'N';break;
		default: parity = 'N';break;
	}

	switch(_stopbits)
	{
		case Stop1_0: stopbits = 1;break;
		case Stop2_0: stopbits = 2;break;
		default: stopbits = 1;break;
	}

    fd = -1;
    fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd < 0)
    {
        //perror("Can't Open Serial Port !");
        return false;
    }
    else
    {
        //printf("Open ttyS%d ......\n",iPortNumber-1);
    }

    if(flock(fd,LOCK_EX|LOCK_NB)==0)
    {
        //printf("the file was not locked.\n");
    }
    else
    {
        //printf("the file was locked.\n");
        close(fd);
        return false;
    }
          
    if(fcntl(fd, F_SETFL, 0) < 0)/*恢复串口的状态为阻塞状态，用于等待串口数据的读入*/
    {
        //printf("fcntl failed !\n");
        return false;
    }
    else
    {
        //printf("fcntl = %d !\n",fcntl(fd,F_SETFL,0));
    }
          
    /*测试打开的文件描述符是否应用一个终端设备，以进一步确认串口是否正确打开*/
    if(!isatty(fd))
    {
        //printf("Standard input isn't a terminal device !\n");
        return false;
    }
    else
    {
        //printf("It's a serial terminal device!\n");
    }

    //printf("open_port file ID = %d !\n",fd);
    int res = SetPort(_baudrate, databits, parity, stopbits);
	if(res == -1)
	{
		printf("set_port:Can't Open Serial Port %d, %d, %c, %d!\n", _baudrate, databits, parity, stopbits);
		return false;
	}
    PortState = true;
    PortName = _port;
    return true;
          
}
      
int SerialDriver::SetPort(int iBaudRate, int iDataSize, char cParity, int iStopBit)
{
    int iResult = 0;
    struct termios oldtio,newtio;
          
          
    iResult = tcgetattr(fd, &oldtio);/*保存原先串口配置*/
    if(iResult)
    {
        //perror("Can't get old terminal description !");
        return (-1);
    }
          
          
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;/*设置本地连接和接收使用*/
          
    /*设置输入输出波特率*/
    switch(iBaudRate)
    {
        case 2400:
            cfsetispeed(&newtio,B2400);
            cfsetospeed(&newtio,B2400);
            break;
        case 4800:
            cfsetispeed(&newtio,B4800);
            cfsetospeed(&newtio,B4800);
            break;
        case 9600:
            cfsetispeed(&newtio,B9600);
            cfsetospeed(&newtio,B9600);
            break;
        case 19200:
            cfsetispeed(&newtio,B19200);
            cfsetospeed(&newtio,B19200);
            break;
        case 38400:
            cfsetispeed(&newtio,B38400);
            cfsetospeed(&newtio,B38400);
            break;
        case 57600:
            cfsetispeed(&newtio,B57600);
            cfsetospeed(&newtio,B57600);
            break;
        case 115200:
            cfsetispeed(&newtio,B115200);
            cfsetospeed(&newtio,B115200);
            break;
        case 230400:
            cfsetispeed(&newtio,B230400);
            cfsetospeed(&newtio,B230400);
            break;
        case 460800:
            cfsetispeed(&newtio,B460800);
            cfsetospeed(&newtio,B460800);
            break;
        default:
            /*perror("Don't exist iBaudRate !");*/
            //printf("Don't exist iBaudRate %d !\n",iBaudRate);
            return (-1);
    }

    /*设置数据位*/
    newtio.c_cflag &= (~CSIZE);
    switch(iDataSize)
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
        default:
            /*perror("Don't exist iDataSize !");*/
            //printf("Don't exist iDataSize %d !\n",iDataSize);
            return (-1);
    }
          
    /*设置校验位*/
    switch(cParity)
    {
        case 'N':                   /*无校验*/
            newtio.c_cflag &= (~PARENB);
            break;
        case 'O':                    /*奇校验*/
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= INPCK; // |= (INPCK | ISTRIP) —— 设置ISTRIP会忽略第8位！！！
            break;
        case 'E':                    /*偶校验*/
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            newtio.c_iflag |= INPCK; // |= (INPCK | ISTRIP) —— 设置ISTRIP会忽略第8位！！！
            break;
        default:
            /*perror("Don't exist cParity  !");*/
            //printf("Don't exist cParity %c !\n", cParity);
            return (-1);
    }
          
    /*设置停止位*/
    switch(iStopBit)
    {
        case 1:
            newtio.c_cflag &= (~CSTOPB);
            break;
        case 2:
            newtio.c_cflag |= CSTOPB;
            break;
        default:
            /*perror("Don't exist iStopBit !");*/
            //printf("Don't exist iStopBit %d !\n", iStopBit);
            return (-1);
    }
          
    newtio.c_cc[VTIME] = 0; /*设置等待时间*/
    newtio.c_cc[VMIN] = 0;  /*设置最小字符*/
    tcflush(fd,TCIFLUSH);       /*刷新输入队列(TCIOFLUSH为刷新输入输出队列)*/
    iResult = tcsetattr(fd, TCSANOW, &newtio);    /*激活新的设置使之生效,参数TCSANOW表示更改立即发生*/
      
    if(iResult)
    {
        //perror("Set new terminal description error !");
        return (-1);
    }
          
    //printf("set_port success !\n");
          
    return 0;
}
      
int SerialDriver::Read(void *buf, int iByte)
{
    int iLen = 0;
    if(!iByte)
    {
       //printf("Read byte number error !\n");
       return iLen;
    }
          
    iLen = (int)read(fd, buf, (size_t)iByte);

    return iLen;
}
      
bool SerialDriver::Write(const void *buf, int iByte)
{
    int iLen = 0;
    if(!iByte)
    {
        //printf("Write byte number error !\n");
        return false;
    }

    unsigned char *_buf = (unsigned char *)buf;
//    printf("write data: ");
//    for(int ii=0;ii<iByte;ii++) printf("%d ", _buf[ii]);
//    printf("\n");
    iLen = (int)write(fd, buf, (size_t)iByte);

	if(iLen == iByte) return true;
          
    return false;
}
      
      
int SerialDriver::ClosePort()
{
    int iResult = -1;
    if(fd == 0) return 0;
    iResult = close(fd);
    PortState = false;
    PortName = "";
    return iResult;
}

int SerialDriver::GetComListFromReg(std::vector<std::string> &_PortList)
{
	std::string FilePrefix = "/dev/ttyUSB";
	int n = 0;
	_PortList.clear();
	for(int i=0;i<256;i++)
	{
		std::string FileName = std::to_string(i);
		//FileName.to_string(i);
		FileName = FilePrefix+FileName;
		int res = access(FileName.data(), R_OK | W_OK | F_OK);
		if(res == 0)
		{
			_PortList.push_back(FileName);
			n++;
		}
		else
		{
			//printf("file not exists\n");
		}
	}
	return n;
}





