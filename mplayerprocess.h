#ifndef MPLAYERPROCESS_H
#define MPLAYERPROCESS_H
#include <QObject>
#include <QProcess>
#include <QStringList>
#include "message.h"
#define BROADCAST_DIR   "./broadcast"
#define RHA_Broadcast  1
#define RHA_Audio 2
class MplayerProcess:QObject{
    Q_OBJECT
public:
    MplayerProcess();
    static void playBroadcast(QString code);    //播放紧急广播
    static void stopBroadcast();                //停止播放紧急广播
    static void playAudio(QStringList & list);    //播放背景音
    static void stopAudio();                    //停止播放背景音
    static void setMsgHandle(Message *handle);  //设置消息处理器

private:
    QProcess *process;
    static Message *msgHandle;
    static MplayerProcess *mp;
    static int mode;
    static QString broadcast;
    static QStringList audioList;
    static int audioListIndex;
    static bool loop;      //循环标志
    bool isPlaying();       //检查播放状态
    void play(QString path);     //开始播放
    void stop();     //停止播放
private slots:
    void playFinish();
};

#endif // MPLAYERPROCESS_H
