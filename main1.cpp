#include "serial_driver.h"

using namespace std;

int main(int argc, char** argv )
{
    std::string serialDeviceName_ = "/dev/ttyS0";

    // 波特率115200, 数据位8位, 偶校验, 一位停止位
    SerialDriver serialPort;
    bool ret = serialPort.OpenPort(serialDeviceName_, 9600, SerialDriver::DataBits::Data8,
                                       SerialDriver::Parity::Even, SerialDriver::StopBits::Stop1_0);
    if(!ret) printf("Open serial port failed!\n");

    unsigned char writeData[10] = {0};
    writeData[0] = 0xFF;
    writeData[1] = 0xFF;
    writeData[2] = 0x01;
    writeData[3] = 0x04;
    writeData[4] = 0x02;
    writeData[5] = 0x3F;

    serialPort.Write(writeData, 6);

    while (true) {
        unsigned char readData[255] = {0};
        int len = serialPort.Read(readData, 255);
        for (int i = 0; i < len; i++) {
            printf("%02X ", readData[i]);
        }

        if (len > 0) {
            puts("");
            break;
        }

        usleep(1000 * 50);
    }

    serialPort.ClosePort();
}