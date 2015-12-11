#include "formaudio.h"
#include "ui_formaudio.h"
#include "rha.h"
#include <QDebug>
FormAudio::FormAudio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAudio)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    installEventFilter(this);
    buttonList.append(ui->pushButtonPlay);
    buttonList.append(ui->pushButtonStop);
    buttonList.append(ui->pushButtonPrev);
    buttonList.append(ui->pushButtonNext);
    buttonListIndex = 0;
    buttonList.at(buttonListIndex)->setFocus();
    mplayerProcess = new QProcess();
    loadMusicFile();
}

FormAudio::~FormAudio()
{
    delete mplayerProcess;
    delete ui;
}

void FormAudio::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
bool FormAudio::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug("menu key press:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_MENU:
            qDebug("KEY_MENU");
            buttonList.at(buttonListIndex)->click();
            break;
        case RHA_KEY_UP:
            qDebug("KEY_UP");
            buttonListIndex > 0 ?buttonListIndex--:buttonListIndex=buttonList.count()-1;
            buttonList.at(buttonListIndex)->setFocus();
            break;
        case RHA_KEY_DN:
            qDebug("KEY_DN");
            buttonListIndex < buttonList.count()-1 ?buttonListIndex++:buttonListIndex=0;
            buttonList.at(buttonListIndex)->setFocus();
            break;
        case RHA_KEY_BACK:
            qDebug("KEY_BACK");
            this->hide();
            break;
        }
        return true;
    }
    else
        return QObject::eventFilter(obj, e);
}
void FormAudio::loadMusicFile()
{
    QDir dir(MUSIC_DIR);
    QStringList list;
    QStringList nameFilter;
    nameFilter << "*.mp3" ;
    dir.setNameFilters(nameFilter);
    dir.setFilter(QDir::Files);
    list = dir.entryList();
    ui->listWidget->clear();
    if(list.isEmpty())
        return;
    ui->listWidget->addItems(list);
    //ui->listWidget->item(0)->setSelected(true);
    ui->listWidget->setCurrentRow(0);
}

void FormAudio::on_pushButtonPlay_clicked()
{

    QString path;
    QString cmd;
    path = MUSIC_DIR;
    path += "/";
    path +=ui->listWidget->currentItem()->text();
    if(!QFile::exists(path))
    {
        ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
        return;
    }

    if(mplayerProcess->pid()!=0)
    {
        cmd  = "load " +  path + "\n";
        mplayerProcess->write(cmd.toUtf8());
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
        mplayerProcess->start(cmd);
        mplayerProcess->waitForStarted(50);
    }
}

void FormAudio::on_pushButtonStop_clicked()
{
    //退出mplayer程序
    mplayerProcess->write("quit\n");
    mplayerProcess->waitForFinished(50);
}

void FormAudio::on_pushButtonPrev_clicked()
{
    int index,sum;
    sum = ui->listWidget->count();
    if(sum<=0)
        return;
    index = ui->listWidget->currentRow();
    index>0? index--: index = sum-1;
    ui->listWidget->setCurrentRow(index);
}

void FormAudio::on_pushButtonNext_clicked()
{
    int index,sum;
    sum = ui->listWidget->count();
    if(sum<=0)
        return;
    index = ui->listWidget->currentRow();
    index<sum-1? index++:index = 0;
    ui->listWidget->setCurrentRow(index);
}
