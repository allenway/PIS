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
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

DialogSelectAnnunciator::~DialogSelectAnnunciator()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    delete timer;
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
            timer->stop();
            if(selectCar>=0 && selectCar<8 && selectIndex>=0 && selectIndex<4)
            {
                if(((annunciator[selectCar]>>((3-selectIndex)*2))&0x3)==0x1)  //不处于呼叫模式
                {
                    annunciator[selectCar] =
                            (annunciator[selectCar]&(~(0x3<<((3-selectIndex)*2))))|(0x2<<((3-selectIndex)*2));
                }
            }
            hide();
            break;
        case RHA_KEY_UP:
            qDebug("KEY_UP");
            selectPrev();   //选择上一个
            break;
        case RHA_KEY_DN:
            qDebug("KEY_DN");
            selectNext();   //选择下一个
            break;
        case RHA_KEY_BACK:
            qDebug("KEY_BACK");
            timer->stop();
            hide();
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
    selectCar = -1;
    selectIndex = -1;
    move(0,0);
    //每200ms显示一次
    timer->start(200);
    exec();
}
//光标选择上一个
void DialogSelectAnnunciator::selectPrev()
{
    int i;
    int i_s,i_e;
    if(selectCar>=0 && selectCar<8 && selectIndex>=0 && selectIndex<4)
    {
        i_s = (selectCar*4+selectIndex+31)%32+32;
        i_e = i_s - 32;
    }
    else
    {
        i_s = 32;
        i_e = 0;
    }
    int car,index;
    for(i=i_s;i>i_e;i--)
    {
        car = (i/4)%8;
        index = i%4;
        if(((annunciator[car]>>((3-index)*2))&0x3)==0x1)  //呼叫模式
        {
            selectCar = car;
            selectIndex = index;
            label[selectCar][selectIndex].setFocus();
            return;
        }
    }
}
//光标选择下一个
void DialogSelectAnnunciator::selectNext()
{
    int i;
    int i_s,i_e;
    if(selectCar>=0 && selectCar<8 && selectIndex>=0 && selectIndex<4)
    {
        i_s = (selectCar*4+selectIndex+1)%32;
        i_e = i_s + 32;

    }
    else
    {
        i_s = 0;
        i_e = 32;
    }
    int car,index;
    for(i=i_s;i<i_e;i++)       
    {
        car = (i/4)%8;
        index = i%4;
        if(((annunciator[car]>>((3-index)*2))&0x3)==0x1)  //呼叫模式
        {
            selectCar = car;
            selectIndex = index;
            label[selectCar][selectIndex].setFocus();
            return;
        }
    }
}

//将处于呼叫状态的警报器闪动显示标识出来
void DialogSelectAnnunciator::timeout()
{
    static bool v;
    bool have = false;
    v = !v;
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
        {
            if(((annunciator[i]>>((3-j)*2))&0x3)==0x1)  //呼叫模式
            {
                label[i][j].setVisible(v);
                have = true;
            }
            else
            {
                label[i][j].setVisible(true);
            }
        }
    if(selectCar>=0 && selectCar<8 && selectIndex>=0 && selectIndex<4)
    {
        if(have)    //有处于呼叫状态的警报器
        {
            if(((annunciator[selectCar]>>((3-selectIndex)*2))&0x3)!=0x1)  //不处于呼叫模式
            {
                selectNext();   //将光标偏移到下一个警报器
            }
        }
        else    //没有处于呼叫状态的警报器
        {
            label[selectCar][selectIndex].clearFocus();
            selectCar = -1;
            selectIndex = -1;
        }
    }
    else    //当前没有选择警报器
    {
        if(have)     //有处于呼叫状态的警报器
            selectNext();
    }
}
