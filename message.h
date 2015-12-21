#ifndef MESSAGE_H
#define MESSAGE_H
#include<QReadWriteLock>
#include<QMutex>
#include<QWaitCondition>
#include<QThread>
#include<QByteArray>
#include<QTimer>
#include "rha.h"

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
//UartHandle专门负责接收和发送Uart原始数据
class UartHandle:public QThread{
    Q_OBJECT
public:
    UartHandle();
    ~UartHandle();
    void run();
    bool enable(const char *path,int baudrate);
    void sendData(const QByteArray & p);
    ResData *getResData();
private:
    int fd;
    ResData *data;
    QMutex writeLock;
};

//DCP过程数据大小
#define DCP_DATA_SIZE   22
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
    bool enable(UartHandle *handle);
    void startDCP();   //启动?
    void pa();      //口播，司机对整列车进行讲话广播
    void pc();      //紧急对讲应答，司机对报警进行应答？
    void cc();      //司机与司机之间进行对讲
    void sp();      //音量调节
    void mo();      //监听
    void ptt(bool push);     //push to talk，按下时讲话，松开时听话
    //设置起始站 设置终点站 设置当前站 设置下一站
    void setStation(uchar f,uchar l,uchar c,uchar n);

signals:
    //void ccStatChanged();               //司机对讲状态发送变化
    //void annunciatorStatChanged();      //报警器状态发生变化

private:
    QTimer *timer;  //定时器,100ms出发一次，用于维护广播控制盒的状态，如LED亮／灭／闪、蜂鸣器、音量控制
    ResData *data;  //接收到的原始数据
    UartHandle *uart;       //专门负责接收和发送Uart原始数据
    QByteArray dataDCP; //DCP数据，即广播控制盒与中央控制盒之间的通信数据
    bool moStat;        //MO监听状态
    uchar spStat;      //音量状态
    uchar firstStation;     //起始站
    uchar lastStation;      //终点站
    uchar currentStation;       //当前站
    uchar nextStation;      //下一站
    uchar skipStation;      //越站
    uchar broadcastCode;    //紧急广播代码
    //bit7        bit6   bit5       bit4        bit3        bit2           bit1         bit0
    //停止报站广播  -     正在口播    口播申请    紧急广播触发  越站广播触发	到站广播触发      预报广播触发
    uchar broadcastStat;    //广播状态

//    司机对讲状态2    司机对讲状态1
//    报警器状态位2    报警器状态位1
//        0           0             挂断状态（司机对讲/乘客报警通用）
//        0           1             呼叫状态（司机对讲/乘客报警通用）
//        1           0             应答状态（司机对讲/乘客报警通用）
//        1           1             乘客紧急报警挂起
    //司机对讲状态ccStat附加设定bit2［1:本机主叫0:客机主叫］,但是不用于DCP数据传输，只作内部标识
    uchar ccStat;       //司机对将状态
    uchar annunciatorStat[8];  //报警器状态,2bit表示一个报警器，共32个报警器
    bool isMyPacket(const QByteArray & p);    //是发给自己的数据包
    bool isVaildPacket(const QByteArray &p);  //数据包是否有效
    void sendData();
    void updateTrainStat();         //获取列车状态,第8个字节
    void updateAnnunciatorStat();   //获取报警器状态,第9到16字节共8个字节
    void setBellStat(bool enable);  //开启关闭振铃
    void setLEDStat(int num,bool enable);   //开启关闭指定LED灯
    void setVolume(int v);       //设置音量
    void setCSLoadStat(bool enable);    //MIC使能

private slots:
    void timerHandle(); //定时器,100ms出发一次，用于维护广播控制盒的状态，如LED亮／灭／闪、蜂鸣器、音量控制
};


class Message:public QObject{
    Q_OBJECT
public:
    Message();
    ~Message();
    void startDCP();   //启动
    void pa();      //口播，司机对整列车进行讲话广播
    void pc();      //紧急对讲应答，司机对报警进行应答
    void cc();      //司机与司机之间进行对讲
    void sp();      //音量调节
    void mo();      //监听
    void ptt(bool push);     //push to talk，按下时讲话，松开时听话
    //设置起始站 设置终点站 设置当前站 设置下一站
    void setStation(uchar f,uchar l,uchar c,uchar n);

signals:
    //void ccStatChanged();               //司机对讲状态发送变化
    //void annunciatorStatChanged();      //报警器状态发生变化

private:
    UartHandle *uart;       //专门负责接收和发送Uart原始数据
    DataHandle *dataHandle;  //专门负责处理分析数据包
};

#endif // MESSAGE_H
