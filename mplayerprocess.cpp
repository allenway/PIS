#include "mplayerprocess.h"
#include <QFile>
#include <QDebug>
Message *MplayerProcess::msgHandle = NULL;
MplayerProcess *MplayerProcess::mp = new MplayerProcess();
int  MplayerProcess::mode = 0;
bool MplayerProcess::loop = false;
int MplayerProcess::audioListIndex = 0;
QString MplayerProcess::broadcast ;
QStringList MplayerProcess::audioList;

MplayerProcess::MplayerProcess()
{
    process = new QProcess();
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(playFinish()));
}
void MplayerProcess::setMsgHandle(Message *handle)
{
    msgHandle = handle;
}
//播放紧急广播
void MplayerProcess::playBroadcast(QString code)
{
    QString path;
    broadcast = code;
    if(msgHandle!=NULL)
    {
        if(mp->isPlaying())
        {
            if( mode != RHA_Broadcast)
            {
                //发送停止播放背景音消息
                msgHandle->setAudioStat(false);
            }
        }
        //发送开始播放紧急广播消息
        msgHandle->setBroadcastStat(true,code.toInt());
    }
    mode = RHA_Broadcast;
    path = BROADCAST_DIR;
    path += "/";
    path += code;
    path += ".mp3";
    loop = true;
    mp->play(path);
}
//停止播放紧急广播
void MplayerProcess::stopBroadcast()
{
    if(mode !=  RHA_Broadcast)
        return;
    loop = false;
    mp->stop();
    if(msgHandle!=NULL)
    {
        //发送停止播放紧急广播消息
        msgHandle->setBroadcastStat(false);
    }
}
//播放背景音
void MplayerProcess::playAudio(QStringList & list)
{
    if(list.isEmpty())
        return;
    if(msgHandle!=NULL)
    {
        if(mp->isPlaying())
        {
            if( mode != RHA_Audio)
            {
                //发送停止播放紧急广播消息
                msgHandle->setBroadcastStat(false);
            }
        }
        //发送开始播放背景音消息
        msgHandle->setAudioStat(true);
    }
    loop = true;
    audioListIndex = 0;
    audioList = list;
    mode = RHA_Audio;
    mp->play(audioList.at(audioListIndex));
}
//停止播放背景音
void MplayerProcess::stopAudio()
{
    if(mode !=  RHA_Audio)
        return;
    loop = false;
    mp->stop();
    if(msgHandle!=NULL)
    {
        //发送停止播放背景音消息
        msgHandle->setAudioStat(false);
    }
}
bool MplayerProcess::isPlaying()
{
    if(process->pid()!=0)
        return true;
    else
        return false;
}
//开始播放
void MplayerProcess::play(QString path)
{

    QString cmd;
    if(isPlaying())
    {
        cmd  = "load " +  path + "\n";
        process->write(cmd.toUtf8());
    }
    else
    {
        //启动mplayer程序
        //-ao alsa 采用alsa声卡驱动
        //-srate 44100 指定输出采样率为44100，否则有写音乐播放出现稀奇古怪的声音
        //-slave 指定为从机模式
        //-quiet 指定信息输出模式为quiet
        cmd = "mplayer -ao alsa -srate 44100 -slave -quiet " + path;
        //使用arguments参数时，无法启动，故将参数与命令写成一行
        process->start(cmd);
        process->waitForStarted(50);
    }
}
//停止播放
void MplayerProcess::stop()
{
    //退出mplayer程序
    process->write("quit\n");
    process->waitForFinished(50);
}
//播放完成
void MplayerProcess::playFinish()
{
    if(loop==false) //主动停止的播放的，直接退出
        return;
    if(mode==RHA_Audio)
    {
        while(!audioList.isEmpty())
        {
            audioListIndex++;
            audioListIndex = audioListIndex%audioList.count();
            if(QFile::exists(audioList.at(audioListIndex)))
                break;
            else
                audioList.removeAt(audioListIndex);
        }
        if(audioList.isEmpty()) //播放列表为空
        {
            if(msgHandle!=NULL)
            {
                //发送停止播放背景音消息
                msgHandle->setAudioStat(false);
            }
        }
        else
            mp->play(audioList.at(audioListIndex));
    }
    else if(mode==RHA_Broadcast)
    {
        QString path;
        path = BROADCAST_DIR;
        path += "/";
        path += broadcast;
        path += ".mp3";
        if(QFile::exists(path))
            mp->play(path);
        else    //文件不存在
        {
            if(msgHandle!=NULL)
            {
                //发送停止播放紧急广播消息
                msgHandle->setBroadcastStat(false);
            }
        }
    }
    else    //其它状态，直接退出
        return;
}



