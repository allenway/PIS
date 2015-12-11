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
    QWaitCondition updateCond;  //数据更新条件量
    bool update;    //数据更新标志
    QMutex updateLock;  //数据更新锁
    QList<QByteArray> packets;
};
//DCP过程数据大小
#define DCP_DATA_SIZE   32
//DCP数据包大小
#define DCP_PACKET_SIZE (DCP_DATA_SIZE + 7)
//DataHandle专门负责处理分析数据包,实时的监测最新的状态变化，
//为了确保处理速度，在接收到DCP数据包后，会通过比对当前状态与DCP数据中的变化，如果有状态变化，才产生相应的事件信号
class DataHandle:public QThread{
    Q_OBJECT
public:
    DataHandle();
    ~DataHandle();
    void run();
    bool enable(ResData *d);
signals:
    void ccStatChanged();               //司机对讲状态发送变化
    void annunciatorStatChanged();      //报警器状态发生变化

private:
    ResData *data;  //接收到的原始数据，
    QByteArray dataDCP; //DCP数据，即广播控制盒与中央控制盒之间的通信数据
//    司机对讲状态2    司机对讲状态1
//    报警器状态位2    报警器状态位1
//        0           0             挂断状态（司机对讲/乘客报警通用）
//        0           1             呼叫状态（司机对讲/乘客报警通用）
//        1           0             应答状态（司机对讲/乘客报警通用）
//        1           1             乘客紧急报警挂起
    uchar ccStat;       //司机对将状态
    uchar annunciatorStat[8];  //报警器状态,2bit表示一个报警器，共32个报警器
    bool isMyPacket(const QByteArray & p);    //是发给自己的数据包
    bool isVaildPacket(const QByteArray &p);  //数据包是否有效  
    void updateTrainStat();         //获取列车状态,第8个字节
    void updateAnnunciatorStat();   //获取报警器状态,第9到16字节共8个字节
    void setBellStat(bool enable);  //开启关闭振铃
    void setLEDStat(int num,bool enable);   //开启关闭指定LED灯
    void setVolume();       //设置音量
    void setCSLoadStat(bool enable);
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
signals:
    void ccStatChanged();               //司机对讲状态发送变化
    void annunciatorStatChanged();      //报警器状态发生变化

private:
    ResData *recvData;       //从Uart接收到的数据
    UartHandle *uart;       //专门负责接收和发送Uart原始数据
    DataHandle *dataHandle;  //专门负责处理分析数据包
};

#endif // MESSAGE_H
