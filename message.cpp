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
//            qDebug()<<"[RHA]select timeout";
//以下为测试代码
//            for(int i=0;i<10;i++)
//            {
//                for(int j=1;j<30;j++)
//                    buf[j+i*31] = i;
//                buf[0+i*31] = 0x7e;
//                buf[30+i*31] =0x7e;
//            }
//            data->addData(buf,31*10);
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
        qDebug()<<"[RHA]DataHandle run()";
        //等待数据更新
        data->waitUpdate();
        //获取数据包
        packets = data->getDataPackets();
        //qDebug("[RHA]recv %d packets",packets.count());
        //分析数据包,只分析最新的有效数据包
        for(int i = packets.count()-1;i>=0;i--)
        {
            const QByteArray & p = packets.at(i);
            if( isMyPacket(p) && isVaildPacket(p) )
            {
                //提取过程数据
                dataDCP = p.mid(6,DCP_DATA_SIZE);
                //获取列车状态,第8个字节
                updateTrainStat();
                //获取报警器状态,第9到16字节共8个字节
                updateAnnunciatorStat();
                //获取故障信息和终点站显示屏状态,第21
                break; //跳出分析流程
            }
        }
    }
}
//是否发给自己的数据包
bool DataHandle::isMyPacket(const QByteArray & p)
{
    //目的网络ID(1byte)
    //目的设备ID(1byte)
    //源网络ID(1byte)
    //源设备ID(1byte)
    //数据类型（1byte）
    //数据长度（1byte）
    //应用层数据（22bytes)
    //CRC(1byte)
    if( p.count()!= DCP_PACKET_SIZE || (uchar)p.at(5)!=DCP_DATA_SIZE )
        return false;
    return true;
}
//数据包是否有效
bool DataHandle::isVaildPacket(const QByteArray & p)
{
    uchar checksum = 0;
    for(int i=0;i<p.count()-1;i++)
        checksum +=(uchar)p.at(i);
    return (checksum==(uchar)p.at(p.count()-1) ? true:false);
}

//获取列车状态,第8个字节
void DataHandle::updateTrainStat()
{}
//获取报警器状态,第9到16字节共8个字节
void DataHandle::updateAnnunciatorStat()
{}


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
    dataLock.lock();
    packets.clear();
    //数据包以0x7e开始和结尾,所以要丢弃不是0x7e开始的数据
    //查找到数据头,以0x7e开始
    while(1)
    {
        int i;
        for(i = 0;i< data.count();i++)
        {
            //找到数据头
            if((uchar)data.at(i)==0x7e)
            {
                data.remove(0,i);
                i = 0;
                break;
            }
        }
        if(i==data.count()) //没有找到数据头
        {
            //清空所以数据
            data.clear();
            //跳出循环
            break;
        }
        //查找数据尾，0x7e结尾
        for(i = 1;i<data.count();i++)
        {
            //查找到数据尾
            if((uchar)data.at(i)==0x7e)
            {
                QByteArray packet;
                uchar t;
                bool byteError = false;//标识是否有数据转码错误
                //对数据包进行逆转码
                //0x7f80->0x7e
                //0x7f81->0x7f
                //0x7f后面不是80或81,表示错误
                for(int j = 1;j<i;j++)
                {
                    t = (uchar)data.at(j);
                    switch(t){
                    case 0x7f:
                        //0x7f必须要有两个字节表示才有意义
                        if((j+1)<i)
                        {
                            j++;
                            t = (uchar)data.at(j);
                            if(t==0x80)
                                packet.append(0x7e);
                            else if(t==0x81)
                                packet.append(0x7f);
                            else    //数据是错误的
                                byteError = true;
                        }
                        else  //数据是错误的
                            byteError = true;
                            break;
                    default:
                        packet.append(t);
                    }
                    if(byteError)
                    {
                        //qDebug()<<"byteError 0x7f";
                        break;
                    }
                }
                //数据没有错误，将数据包保存
                if(!byteError)
                    packets.append(packet);
                //清理掉一个数据包,从0x7e到0x7e之间的数据全部清理掉
                data.remove(0,i+1);
                i = 0;
                break;
            }
        }
        if(i==data.count()) //没有找到数据尾
        {
            //跳出循环
            break;
        }
    }
    update = false;
    dataLock.unlock();
    //返回有效的数据包
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
