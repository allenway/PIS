#include "message.h"
#include "rha.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <QDebug>
#include <QSettings>

Message::Message()
{
    recvData = new ResData();
    dataHandle = new DataHandle();
    dataHandle->enable(recvData);
    uart = NULL;
    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    if(settings.value("Uart/Enable").toBool())
    {
        uart = new UartHandle();
        uart->enable(settings.value("Uart/Path").toByteArray().constData(),
                   settings.value("Uart/Baudrate").toInt(),
                   recvData);
    }

}
Message::~Message()
{
    if(uart)
        delete uart;
    delete dataHandle;
    delete recvData;
}
//UartHanle
UartHandle::UartHandle()
{
    fd = -1;
}
UartHandle::~UartHandle()
{
    if(fd >=0 )
        close(fd);
}

bool UartHandle::enable(const char *path,int baudrate,ResData *d)
{
    data = d;
    if(data==NULL)
        return false;
    fd = open(path, O_RDWR | O_NOCTTY );
    if(fd<0)
    {
        qDebug("open %s :%s\n",path,strerror(errno));
        return false;
    }

    struct termios options;
    //1. tcgetattr函数用于获取与终端相关的参数。
    //参数fd为终端的文件描述符，返回的结果保存在termios结构体中

    tcgetattr(fd, &options);
    cfmakeraw(&options);
    //2.修改所获得的参数
    options.c_cflag |= (CLOCAL | CREAD);//设置控制模式状态，本地连接，接收使能
    options.c_cflag &= ~CSIZE;//字符长度，设置数据位之前一定要屏掉这个位
    options.c_cflag |= CS8;//8位数据长度
    options.c_cflag &= ~CRTSCTS;//无硬件流控
    options.c_cflag &= ~CSTOPB;//1位停止位
    options.c_iflag |= IGNPAR;//无奇偶检验位
    //options.c_oflag = 0; //输出模式
    //options.c_lflag = 0; //不激活终端模式
    //设置波特率
    switch(baudrate){
    case 50:
        cfsetospeed(&options, B50);
        break;
    case 75:
        cfsetospeed(&options, B75);
        break;
    case 110:
        cfsetospeed(&options, B110);
        break;
    case 134:
        cfsetospeed(&options, B134);
        break;
    case 150:
        cfsetospeed(&options, B150);
        break;
    case 200:
        cfsetospeed(&options, B200);
        break;
    case 300:
        cfsetospeed(&options, B300);
        break;
    case 600:
        cfsetospeed(&options, B600);
        break;
    case 1200:
        cfsetospeed(&options, B1200);
        break;
    case 1800:
        cfsetospeed(&options, B1800);
        break;
    case 2400:
        cfsetospeed(&options, B2400);
        break;
    case 4800:
        cfsetospeed(&options, B4800);
        break;
    case 9600:
        cfsetospeed(&options, B9600);
        break;
    case 19200:
        cfsetospeed(&options, B19200);
        break;
    case 38400:
        cfsetospeed(&options, B38400);
        break;
    case 57600:
        cfsetospeed(&options, B57600);
        break;
    case 115200:
        cfsetospeed(&options, B115200);
        break;
    case 230400:
        cfsetospeed(&options, B230400);
        break;
    default:
        cfsetospeed(&options, B9600);
    }
    //3. 设置新属性，TCSANOW：所有改变立即生效
    tcsetattr(fd, TCSANOW, &options);
    tcflush(fd, TCIOFLUSH); //刷新数据
    start();
    return true;
}
void UartHandle::run()
{
    //qDebug()<<"UartHandle ...";
    int len=0, ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
    char buf[1024];
    while(fd>=0)
    {
        FD_ZERO(&fs_read);
        FD_SET(fd, &fs_read);
        tv_timeout.tv_sec  = (5);
        tv_timeout.tv_usec = 0;
        ret = select(fd+1, &fs_read, NULL, NULL, &tv_timeout);
        if(ret>0)
        {
            len = read(fd,buf,1023);
            if(len<0)
            {
                qDebug()<<"[RHA][ERROR] read:"<<strerror(errno);
            }
            else
            {
                data->addData(buf,len);  //保存数据
                //qDebug("[RHA]receive %d byte:%s\n",len,data);
                //write(fd,data,sprintf(data,"[RHA]receive %d byte",len));
            }
        }
        else if(ret==0)
        {
            //qDebug()<<"[RHA]select timeout";
        }
        else
        {
            qDebug()<<"[RHA][ERROR] select:"<<strerror(errno);
        }
    }
    qDebug()<<"[RHA][ERROR] UartHandle::run() exit";
}
//DataHandle
DataHandle::DataHandle()
{}
DataHandle::~DataHandle()
{}
//启动数据分析线程
bool DataHandle::enable(ResData *d)
{
    data = d;
    if(data==NULL)
        return false;
    this->start();
    return true;
}
void DataHandle::run()
{
    QList<QByteArray> packets;
    while(1)
    {
        //等待数据更新
        data->waitUpdate();
        //获取数据包
        packets = data->getDataPackets();
        //分析数据包
    }
}

//ResData
ResData::ResData()
{
    update = false;
}
ResData::~ResData()
{}
//添加接收到的数据
void ResData::addData(char *d,int len)
{
    dataLock.lock();
    data.append(d,len);
    dataLock.unlock();
    update = true;
    updateCond.wakeAll();
}
//从现有数据中提取数据包
QList<QByteArray> & ResData::getDataPackets()
{
    QList<QByteArray> packets;
    dataLock.lock();
    update = false;

    dataLock.unlock();
    return packets;
}
//等待数据更新，如果数据没有更新，会使调用线程一直出现休眠状态，直到有数据更新
void ResData::waitUpdate()
{
    if(update)  //数据已经更新
        return;
    updateLock.lock();
    updateCond.wait(&updateLock);   //等待数据更新
    updateLock.unlock();
}
