#include "formaudio.h"
#include "ui_formaudio.h"
#include "rha.h"
#include "mplayerprocess.h"
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
    QStringList list;
    int i_s,i_c,i_e;
    i_s = ui->listWidget->currentRow();
    i_c = ui->listWidget->count();
    i_e = i_s + i_c;
    for(int i = i_s;i<i_e;i++)
    {
        path = MUSIC_DIR;
        path += "/";
        path +=ui->listWidget->item(i%i_c)->text();
        list.append(path);
    }
    MplayerProcess::playAudio(list);
}

void FormAudio::on_pushButtonStop_clicked()
{
    //退出mplayer程序
    MplayerProcess::stopAudio();
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
