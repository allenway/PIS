#include "dialogselectannunciator.h"
#include "ui_dialogselectannunciator.h"
#include "rha.h"
#include <QKeyEvent>

DialogSelectAnnunciator::DialogSelectAnnunciator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectAnnunciator)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    installEventFilter(this);
    for(int i = 0;i<8;i++)
    {
        car[i].setParent(this);
        car[i].setGeometry(5+(i%4*120),22+(i/4*125),110,120);
        car[i].setTitle("Car" + QString::number(i+1));
        for(int j = 0;j<4;j++)
        {
            label[i][j].setParent(&car[i]);
            label[i][j].setGeometry(10,20+j*25,90,20);
        }
    }

}

DialogSelectAnnunciator::~DialogSelectAnnunciator()
{
    delete ui;
}

void DialogSelectAnnunciator::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
bool DialogSelectAnnunciator::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug("menu key press:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_MENU:
            qDebug("KEY_MENU");
            this->hide();
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
void DialogSelectAnnunciator::select(uchar *d)
{
    if(this->isActiveWindow())
        return;
    annunciator = d;
    this->move(0,0);
    this->exec();
}

