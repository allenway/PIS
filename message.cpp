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
    uart = NULL;
    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    if(settings.value("Uart/Enable").toBool())
    {
        uart = new UartHandle();
        uart->enable(settings.value("Uart/Path").toByteArray().constData(),
                   settings.value("Uart/Baudrate").toInt());
    }
    if(uart!=NULL)
    {
        dataHandle = new DataHandle();
        dataHandle->enable(uart);
    }
    connect(dataHandle,SIGNAL(ccStatChanged()),this,SIGNAL(ccStatChanged()));
    connect(dataHandle,SIGNAL(annunciatorStatChanged()),this,SIGNAL(annunciatorStatChanged()));
}
Message::~Message()
{
    disconnect(dataHandle,SIGNAL(ccStatChanged()),this,SIGNAL(ccStatChanged()));
    disconnect(dataHandle,SIGNAL(annunciatorStatChanged()),this,SIGNAL(annunciatorStatChanged()));
    if(uart)
        delete uart;
    delete dataHandle;
}
//启动
void Message::start()
{
    dataHandle->start();
}
//口播，司机对整列车进行讲话广播
void Message::pa()
{
    dataHandle->pa();
}
//紧急对讲应答，司机对报警进行应答
void Message::pc()
{
    dataHandle->pc();
}
//司机与司机之间进行对讲
void Message::cc()
{
    dataHandle->cc();
}
//音量调节
void Message::sp()
{
    dataHandle->sp();
}
//监听
void Message::mo()
{
    dataHandle->mo();
}
//push to talk，按下时讲话，松开时听话
void Message::ptt(bool push)
{
    dataHandle->ptt(push);
}

//UartHanle
UartHandle::UartHandle()
{
    fd = -1;
    data = new ResData();
}
UartHandle::~UartHandle()
{
    if(data!=NULL)
        delete data;
    if(fd >=0 )
        close(fd);
}
ResData *UartHandle::getResData()
{
    return data;
}
bool UartHandle::enable(const char *path,int baudrate)
{
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
                QThread::msleep(20);
                //qDebug("[RHA]receive %d byte\n",len);
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
void UartHandle::sendData(const QByteArray & dat)
{
    QByteArray p;
    uchar d;
    p.append(0x7e);

    for(int i = 0;i<dat.count();i++)
    {
        d = (uchar)dat.at(i);
        switch(d){
        case 0x7e:
            p.append(0x7f);
            p.append(0x80);
            break;
        case 0x7f:
            p.append(0x7f);
            p.append(0x81);
            break;
        default:
            p.append(d);
        }
    }
    p.append(0x7e);
    writeLock.lock();
    write(fd,p.constData(),p.count());
    writeLock.unlock();
}

//DataHandle
DataHandle::DataHandle()
{
    ccStat = 0;
    for(int i=0;i<8;i++)
        annunciatorStat[i] = 0;
    uart = NULL;
}
DataHandle::~DataHandle()
{}
//启动数据分析线程
bool DataHandle::enable(UartHandle *handle)
{
    uart = handle;
    if(handle==NULL)
        return false;
    data = handle->getResData();
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
        //qDebug()<<"[RHA]DataHandle run()";
        //等待数据更新
        data->waitUpdate();
        //获取数据包
        packets = data->getDataPackets();
        //qDebug("[RHA]recv %d packets",packets.count());
        //分析数据包,只分析最新的有效数据包
        for(int i = packets.count()-1;i>=0;i--)
        {
            const QByteArray & p = packets.at(i);
//            qDebug("packet:");
//            for(int j=0;j<p.count();j++)
//            {
//                qDebug("0x%x",(uchar)p.at(j));
//            }
//            qDebug("End packet\n");
//            uart->sendData(p);
            if( isMyPacket(p) && isVaildPacket(p) )
            {
                //提取过程数据
                dataDCP = p.mid(6,DCP_DATA_SIZE);
//                qDebug("dcp:");
//                for(int j=0;j<dataDCP.count();j++)
//                {
//                    qDebug("0x%x",(uchar)dataDCP.at(j));
//                }
//                qDebug("End dcp\n");
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
    checksum = 0x55 -checksum;
    return (checksum==(uchar)p.at(p.count()-1) ? true:false);
}
void DataHandle::sendData()
{
    QByteArray p;
    QByteArray dcp;
    uchar sum = 0;
    //目的车厢号
    p.append(0x01);
    //目的设备号
    p.append(0x01);
    //源车厢号
    p.append((char)0x0);
    //源设备号
    p.append((char)0x0);
    //CMD
    p.append((char)0x0);
    //应用层数据长度
    p.append(22);  //22个字节
    //应用层数据内容
    dcp = dataDCP;
   p.append(dcp);
    //校验和
   for(int i = 0;i<p.count();i++)
       sum+=(uchar)p.at(i);
   p.append(sum);
   uart->sendData(p);
}
//获取列车状态,第8个字节,并作相应的处理
void DataHandle::updateTrainStat()
{
    if(dataDCP.count() != DCP_DATA_SIZE)
        return;
    uchar d = dataDCP.at(7); 
    //检查司机对讲状态的变化
    if( d&0x3 != ccStat )
    {
        ccStat = d&0x3;
        //发出状态变化信号
        emit this->ccStatChanged();
        setLEDStat(LED_CC,d&0x3);
    }
}
//获取报警器状态,第9到16字节共8个字节，并作相应的处理
void DataHandle::updateAnnunciatorStat()
{
    if(dataDCP.count() != DCP_DATA_SIZE)
        return;
    bool have,changed;
    have = false;
    changed = false;
    for(int i=0;i<8;i++)
    {
        uchar d = dataDCP.at(8+i);
        if( d != annunciatorStat[i] )
        {
            annunciatorStat[i] = d;
            changed = true;
        }
    }
    //如果状态发生了改变，发送状态变化信号
    if(changed)
    {
        emit this->annunciatorStatChanged();
        setBellStat(have);
        setLEDStat(LED_ANNUNCIATOR,have);
    }
}
//开启关闭振铃
void DataHandle::setBellStat(bool enable)
{}
//开启关闭指定LED灯
void DataHandle::setLEDStat(int num,bool enable)
{}
//设置音量
void DataHandle::setVolume()
{}
//声音使能
void DataHandle::setCSLoadStat(bool enable)
{}
//音量调节
void DataHandle::sp()
{

}
//push to talk，按下时讲话，松开时听话
void DataHandle::ptt(bool push)
{
    setCSLoadStat(push);
}
//启动
void DataHandle::start()
{
     sendData();
}
//口播，司机对整列车进行讲话广播
void DataHandle::pa()
{
    paStat ^= 0x1;
    sendData();
}
//紧急对讲应答，司机对报警进行应答
void DataHandle::pc()
{
     sendData();
}
//司机与司机之间进行对讲
void DataHandle::cc()
{
    switch(ccStat&0x3){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    }
    sendData();
}
//监听
void DataHandle::mo()
{
     sendData();
}


//ResData
ResData::ResData()
{
    update = false;     //初始化update,表示没有更新
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
                {
                    //如果数据的长度为0，说明数据头位置检测不对，需要修正数据头的位置，故只去除一个0x7e
                    if(packet.count()==0)
                    {
                       data.remove(0,1); //清理掉一个0x7e
                    }
                    else
                    {
                        packets.append(packet);
                        data.remove(0,i+1); //清理掉一个数据包,从0x7e到0x7e之间的数据全部清理掉
                    }
                }
                else
                    data.remove(0,i+1); //清理掉一个数据包,从0x7e到0x7e之间的数据全部清理掉
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
