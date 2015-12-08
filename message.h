#ifndef MESSAGE_H
#define MESSAGE_H
#include<QReadWriteLock>
#include<QMutex>
#include<QWaitCondition>
#include<QThread>
#include<QByteArray>

//共享资源数据，实现多线程保护
class ResData{
public:
    ResData();
    ~ResData();
    void addData(char *d,int len);
    void waitUpdate();
    QList<QByteArray> & getDataPackets();
private:
    QByteArray data;
    QMutex dataLock;
    QWaitCondition updateCond;
    bool update;
    QMutex updateLock;
    QList<QByteArray> packets;
};


//DataHandle专门负责处理分析数据包
class DataHandle:public QThread{
    Q_OBJECT
public:
    DataHandle();
    ~DataHandle();
    void run();
    bool enable(ResData *d);
private:
    ResData *data;
    bool isMyPacket(const QByteArray & p);    //是发给自己的数据包
    bool isVaildPacket(const QByteArray &p);  //数据包是否有效

};

//UartHandle专门负责接收和发送Uart原始数据
class UartHandle:public QThread{
    Q_OBJECT
public:
    UartHandle();
    ~UartHandle();
    void run();
    bool enable(const char *path,int baudrate,ResData *d);
private:
    int fd;
    ResData *data;

};

class Message:public QObject{
    Q_OBJECT
public:
    Message();
    ~Message();   
private:
    ResData *recvData;       //从Uart接收到的数据
    UartHandle *uart;       //专门负责接收和发送Uart原始数据
    DataHandle *dataHandle;  //专门负责处理分析数据包


};

#endif // MESSAGE_H
