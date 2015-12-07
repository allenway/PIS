#include "formmenu.h"
#include "ui_formmenu.h"
#include "rha.h"
FormMenu::FormMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMenu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    installEventFilter(this);
    buttonList.append(ui->pushButtonStationSet);
    buttonList.append(ui->pushButtonSysStatus);
    buttonList.append(ui->pushButtonAudio);
    buttonListIndex = 0;
    buttonList.at(buttonListIndex)->setFocus();
    stationSet = new FormStationSet();
    sysStatus = new FormSysStatus();
    audio = new FormAudio();
    connect(stationSet,SIGNAL(stationChanged()),this,SIGNAL(stationChanged()));
}

FormMenu::~FormMenu()
{
    disconnect(stationSet,SIGNAL(stationChanged()),this,SIGNAL(stationChanged()));
    delete ui;
}

void FormMenu::changeEvent(QEvent *e)
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
bool FormMenu::eventFilter(QObject *obj, QEvent *e)
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
void FormMenu::showAudio()
{
    show();
    buttonListIndex = buttonList.indexOf(ui->pushButtonAudio);
    ui->pushButtonAudio->setFocus();
    ui->pushButtonAudio->click();   
}

void FormMenu::on_pushButtonStationSet_clicked()
{
    stationSet->show();
}

void FormMenu::on_pushButtonAudio_clicked()
{
    audio->show();
}

void FormMenu::on_pushButtonSysStatus_clicked()
{
    sysStatus->show();
}
