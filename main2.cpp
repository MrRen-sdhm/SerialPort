#include "SerialPort.h"
#include <unistd.h>

using namespace std;
using namespace LibSerial;

int main(int argc, char** argv )
{
    std::string serialDeviceName_ = "/dev/ttyS0";

    // 波特率115200, 数据位8位, 偶校验, 一位停止位
    SerialPort* serialPort;
    try {
        serialPort = new SerialPort(serialDeviceName_, BaudRate::BAUD_9600, CharacterSize::CHAR_SIZE_8,
                                      FlowControl::FLOW_CONTROL_NONE, Parity::PARITY_EVEN, StopBits::STOP_BITS_1);
    }
    catch  (const OpenFailed&) {
        throw std::runtime_error("Open serial of lift failed!\n");
    }

    DataBuffer writeData = {0xFF, 0xFF, 0x01, 0x04, 0x02, 0x3F};

    serialPort->Write(writeData);



    DataBuffer read_buffer ; // 接收缓冲区
    size_t ms_timeout = 250 ; // 接收超时，即获取超时时间内的数据

    while (true) {
        try {
            serialPort->Read(read_buffer, 0, ms_timeout) ; // 0表示在超时时间内尽可能多的读取数据
        }
        catch (const ReadTimeout&) { // 超时即触发异常，注意此处的超时并不是错误
            for (int i = 0; i < read_buffer.size(); i++)
                printf("%.2X ", read_buffer[i]);
        }

        if(!read_buffer.empty()) {
            puts("");
            break;
        }

        usleep(1000 * 50);
    }

    serialPort->Close();
}