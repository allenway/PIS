#include "formsysstatus.h"
#include "ui_formsysstatus.h"
#include "rha.h"
FormSysStatus::FormSysStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSysStatus)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    installEventFilter(this);
}

FormSysStatus::~FormSysStatus()
{
    delete ui;
}

void FormSysStatus::changeEvent(QEvent *e)
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
bool FormSysStatus::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug("menu key press:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_MENU:
            qDebug("KEY_MENU");
            break;
        case RHA_KEY_UP:
            qDebug("KEY_UP");
            break;
        case RHA_KEY_DN:
            qDebug("KEY_DN");
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
