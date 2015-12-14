#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formstationset.h"
#include "rha.h"
#include <QSettings>
#include <QtDebug>
#include <QEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    //加载站台地图
    timerFlash = new QTimer(this);
    loadMap();
    //初始化菜单节目
    menu = new FormMenu(this);
    menu->move(0,0);
    menu->hide();
    //添加消息处理中心
    msgHandle = new Message();

    connect(menu,SIGNAL(stationChanged()),this,SLOT(stationUpdate()));
    connect(timerFlash,SIGNAL(timeout()),this,SLOT(flashShowStation()));
    connect(msgHandle,SIGNAL(ccStatChanged()),this,SLOT(ccStatUpdate()));
    connect(msgHandle,SIGNAL(annunciatorStatChanged()),this,SLOT(annunciatorStatUpdate()));
}

MainWindow::~MainWindow()
{
    disconnect(menu,SIGNAL(stationChanged()),this,SLOT(stationUpdate()));
    disconnect(timerFlash,SIGNAL(timeout()),this,SLOT(flashShowStation()));
    disconnect(msgHandle,SIGNAL(ccStatChanged()),this,SLOT(ccStatUpdate()));
    disconnect(msgHandle,SIGNAL(annunciatorStatChanged()),this,SLOT(annunciatorStatUpdate()));
    delete msgHandle;
    delete labelDirection;
    delete labelStationName;
    delete labelStationPix;
    delete stationState;
    delete menu;
    delete timerFlash;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::keyPressEvent ( QKeyEvent *e )
{
    switch(e->key()){
    case RHA_KEY_AUDIO:
        qDebug("KEY_AUDIO");
        menu->showAudio();
        break;
    case RHA_KEY_MENU:
        qDebug("KEY_MENU");
        menu->show();
        break;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug()<<obj->objectName();
        //qDebug("main key press:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_START:
            qDebug("KEY_START");
            this->start();
            return true;
        case RHA_KEY_PA:
            qDebug("KEY_PA");
            this->pa();
            return true;
        case RHA_KEY_PC:
            qDebug("KEY_PC");
            this->pc();
            return true;
        case RHA_KEY_CC:
            qDebug("KEY_CC");
            this->cc();
            return true;
        case RHA_KEY_SP:
            qDebug("KEY_SP");
            this->sp();
            return true;
        case RHA_KEY_MO:
            qDebug("KEY_MO");
            this->mo();
            return true;
        case RHA_KEY_PTT:
            qDebug("KEY_PTT");
            this->ptt(true);
            return true;
        case RHA_KEY_NEXT:
            qDebug("KEY_NEXT");
            this->nextStation();
            return true;
        case RHA_KEY_PREV:
            qDebug("KEY_PREV");
            this->prevStation();
           return true;
        case RHA_KEY_LEAVE:
            qDebug("KEY_LEAVE");
            this->leaveStation();
           return true;
        case RHA_KEY_ARRIVE:
            qDebug("KEY_ARRIVE");
            this->arriveStation();
            return true;
        }
        return QObject::eventFilter(obj, e);
    }
    else if(e->type()== QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug("main key release:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_START:
            qDebug("KEY_START");
            return true;
        case RHA_KEY_PA:
            qDebug("KEY_PA");
            return true;
        case RHA_KEY_PC:
            qDebug("KEY_PC");
            return true;
        case RHA_KEY_CC:
            qDebug("KEY_CC");
            return true;
        case RHA_KEY_SP:
            qDebug("KEY_SP");
            return true;
        case RHA_KEY_MO:
            qDebug("KEY_MO");
            return true;
        case RHA_KEY_PTT:
            qDebug("KEY_PTT");
            this->ptt(false);
            return true;
        case RHA_KEY_NEXT:
            qDebug("KEY_NEXT");
            return true;
        case RHA_KEY_PREV:
            qDebug("KEY_PREV");
            return true;
        case RHA_KEY_LEAVE:
            qDebug("KEY_LEAVE");
            return true;
        case RHA_KEY_ARRIVE:
            qDebug("KEY_ARRIVE");
            return true;
        }
        return QObject::eventFilter(obj, e);
    }
    else
        return QObject::eventFilter(obj, e);
}

//加载站台地图信息
void MainWindow::loadMap()
{
    //加载地图
    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    stationsNum = settings.value("StationName/Count").toInt();
    qDebug("Will load %d stations\n",stationsNum);
    isArrive = true;    //初始化为已到站状态
    labelStationName = new QLabel[stationsNum];
    labelStationPix = new QLabel[stationsNum];
    stationState = new StationState[stationsNum];
    labelDirection = new QLabel();
    labelDirection->setParent(this->ui->centralWidget);
    labelDirection->setPixmap(QPixmap(QString::fromUtf8("image/Direction.png")));
    labelDirection->setScaledContents(true);
    QPoint p1(20,76),p2(460,76),p3(20,225),p4(460,225);
    QSize nameSize(100,16),pixSize(30,30);
    int d1,d2;
    int n1,n2;
    if(stationsNum%2==0)
    {
        if(stationsNum>9)
            n2 = 2;
        else
            n2 = 0;
    }
    else
        n2 = 1;
    n1 = (stationsNum-n2)/2;
    d1 = (p2.x()-p1.x())/(n1-1);
    d2 = (p4.y()-p2.y())/(n2+1);
    for(int i=0;i<stationsNum;i++)
    {
        QString str;
        stationState[i] = RHA_Normal;
        labelStationName[i].setParent(this->ui->centralWidget);
        str = "StationName/" + QString::number(i);
        labelStationName[i].setText(settings.value(str).toString());
        labelStationPix[i].setParent(this->ui->centralWidget);      
        labelStationPix[i].setScaledContents(true);
        labelStationPix[i].setAlignment(Qt::AlignCenter);
        if(i<n1)
        {
            this->labelStationPix[i].setGeometry(p1.x()-pixSize.width()/2+i*d1,
                                                 p1.y()-pixSize.height()/2,
                                                 pixSize.width(),
                                                 pixSize.height());

            this->labelStationName[i].setGeometry(15+p1.x()-nameSize.width()+i*d1,
                                                  (n1-i-1)%2 ? p1.y()+pixSize.height()/2+nameSize.height()/4:p1.y()- pixSize.height()/2-5*nameSize.height()/4,
                                                  nameSize.width(),nameSize.height());

        }
        else if( i>=n1 && i< n1+n2 )
        {
           this->labelStationPix[i].setGeometry(p2.x()-pixSize.width()/2,
                                                p2.y()-pixSize.height()/2 +(i-n1 + 1)*d2,
                                                pixSize.width(),
                                                pixSize.height());
           this->labelStationName[i].setGeometry(p2.x()-nameSize.width()-pixSize.width(),
                                                 p2.y()+(i+1-n1)*d2-pixSize.height()/2,
                                                 nameSize.width(),nameSize.height());
        }
        else
        {
            this->labelStationPix[i].setGeometry(p3.x()-pixSize.width()/2+(stationsNum - 1- i)*d1,
                                                 p3.y()-pixSize.height()/2,
                                                 pixSize.width(),
                                                 pixSize.height());


            this->labelStationName[i].setGeometry(15+p3.x()-nameSize.width()+(stationsNum - 1- i)*d1,
                                                  (i-n1-n2)%2 ? p3.y()- pixSize.height()/2-5*nameSize.height()/4 : p3.y()+pixSize.height()/2+nameSize.height()/4,
                                                  nameSize.width(),nameSize.height());
        }
        if( i == 0 || i == stationsNum-1 )
        {
            this->labelStationName[i].setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
            QRect rect = this->labelStationName[i].geometry();
            this->labelStationName[i].setGeometry(2,rect.y(),rect.width(),rect.height());
        }
        else
            this->labelStationName[i].setAlignment(Qt::AlignLeading|Qt::AlignRight|Qt::AlignVCenter);

    }
    stationUpdate();
}


void MainWindow::stationUpdate()
{
    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    //显示列车运行方向
    isReverse = settings.value("StationName/Reverse").toBool();
    if(isReverse)
    {
        labelDirection->setGeometry(10,labelStationName[stationsNum-1].y()-10, 60, 10);
    }
    else
    {
        labelDirection->setGeometry(10,labelStationName[0].y()+labelStationName[0].height(), 60, 10);
    }
    //设置车站状态信息（经过、不经过、已经经过）
    QStringList ignorelist;
    QString str;
    ignorelist = settings.value("StationName/Ignore").toString().split(",");

    //设置不经过站台
    for(int i=0;i<stationsNum;i++)
    {
        str = "StationName/" + QString::number(i);
        if(ignorelist.contains(QString::number(i)))
        {
            stationState[i] = RHA_NoPass;
        }
        else if(stationState[i]==RHA_NoPass)
        {
            stationState[i] = RHA_Unknow;
        }
    }
    //设置经过、已经经过站台信息
    if(isReverse)
    {
        StationState state = RHA_Normal;
        for(int i = 0;i<stationsNum;i++)
        {
            switch(stationState[i]){
            case RHA_Unknow:
                stationState[i] = state;
                break;
            case RHA_Normal:
            case RHA_Pass:
                state = stationState[i];
                break;
            }
        }
        //检查列车方向是否发生了变化
        //如果列车运行方向发生了变化,那么重置所有站台
        for(int i = 0;i<stationsNum;i++)
        {
            if(stationState[i]!=RHA_NoPass)
            {
                if(stationState[i]==RHA_Pass)
                {
                    //重置所有站台
                    for(int j = stationsNum-1;j>=0;j--)
                    {
                        switch(stationState[j]){
                        case RHA_Normal:
                        case RHA_Pass:
                            stationState[j] = RHA_Normal;
                            break;
                        }
                    }
                }
                break;
            }
        }
        //设置首发站
        for(int i = stationsNum-1;i>=0;i--)
        {
            if(stationState[i]!=RHA_NoPass)
            {
                stationState[i] = RHA_Pass;
                break;
            }
        }
    }
    else
    {
        StationState state = RHA_Normal;
        for(int i = stationsNum-1;i>=0;i--)
        {
            switch(stationState[i]){
            case RHA_Unknow:
                stationState[i] = state;
                break;
            case RHA_Normal:
            case RHA_Pass:
                state = stationState[i];
                break;
            }
        }
        //检查列车方向是否发生了变化
        //如果列车运行方向发生了变化,那么重置所有站台
        for(int i = stationsNum-1;i>=0;i--)
        {
            if(stationState[i]!=RHA_NoPass)
            {
                if(stationState[i]==RHA_Pass)
                {
                    //重置所有站台
                    for(int j = 0;j < stationsNum;j++)
                    {
                        switch(stationState[j]){
                        case RHA_Normal:
                        case RHA_Pass:
                            stationState[j] = RHA_Normal;
                            break;
                        }
                    }
                }
                break;
            }
        }
        //设置首发站
        for(int i = 0;i<stationsNum;i++)
        {
            if(stationState[i]!=RHA_NoPass)
            {
                stationState[i] = RHA_Pass;
                break;
            }
        }
    }


    //显示站台图标
    for(int i=0;i<stationsNum;i++)
    {
        switch(stationState[i]){
        case RHA_NoPass:
            labelStationPix[i].setPixmap(QPixmap(QString::fromUtf8("image/NoPassStation.png")));
            break;
        case RHA_Normal:
            labelStationPix[i].setPixmap(QPixmap(QString::fromUtf8("image/NormalStation.png")));
            break;
        case RHA_Pass:
            labelStationPix[i].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
            break;
        }
    }
    //查询当前车站
    currentStationIndex = -1;
    if(isReverse)
    {
        //查找最后一个已经到的站
        for(int i=0;i<stationsNum;i++)
        {
            if(stationState[i]==RHA_Pass)
            {
                currentStationIndex = i;
                break;
            }
        }
        //如果现在是离站状态,则查询下一个站台
        if(!isArrive)
        {
            //查询下一个站台
            for(int i=currentStationIndex;i>=0;i--)
            {
                if(stationState[i]==RHA_Normal)
                {
                    currentStationIndex = i;
                    break;
                }
            }
            //如果查询不到下个站台，说明已经到达终点站了
            if(stationState[currentStationIndex]==RHA_Pass)
                isArrive = true;
        }
    }
    else
    {
        //查找最后一个已经到的站
        for(int i=stationsNum-1;i>=0;i--)
        {
            if(stationState[i]==RHA_Pass)
            {
                currentStationIndex = i;
                break;
            }
        }
        //如果现在是离站状态,则查询下一个站台
        if(!isArrive)
        {
            //查询下一个站台
            for(int i=currentStationIndex;i<stationsNum;i++)
            {
                if(stationState[i]==RHA_Normal)
                {
                    currentStationIndex = i;
                    break;
                }
            }
            //如果查询不到下个站台，说明已经到达终点站了
            if(stationState[currentStationIndex]==RHA_Pass)
                isArrive = true;
        }
    }
    //显示当前站台
    showCurrentStation();
}
//司机对讲状态更新
void MainWindow::ccStatUpdate()
{}
//报警器状态更新
void MainWindow::annunciatorStatUpdate()
{}
void MainWindow::flashShowStation()
{
    static bool ok = true;
    labelStationPix[currentStationIndex].setVisible(ok);
    ok = !ok;
}
void MainWindow::showCurrentStation()
{
    static int oldIndex = -1;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/Arrive.png")));
    //未到站显示闪动标志
    if(!isArrive)
    {
        if(!timerFlash->isActive())
            timerFlash->start(500);
        if(oldIndex != -1)
            labelStationPix[oldIndex].setVisible(true);
        oldIndex = currentStationIndex;

    }
    else
    {
        if(timerFlash->isActive())
            timerFlash->stop();
        if(oldIndex != -1)
            labelStationPix[oldIndex].setVisible(true);
        oldIndex = -1;
    }
}

//下一车站
void MainWindow::nextStation()
{
    isArrive = true;
    stationState[currentStationIndex] = RHA_Pass;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
    if(isReverse)
    {
        for(int i=currentStationIndex-1;i>=0;i--)
        {
            if(stationState[i]==RHA_Normal)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    else
    {
        for(int i=currentStationIndex+1;i<stationsNum;i++)
        {
            if(stationState[i]==RHA_Normal)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    stationState[currentStationIndex] = RHA_Pass;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
    //显示当前站台
    showCurrentStation();
}
//上一车站
void MainWindow::prevStation()
{
    isArrive = true;
    stationState[currentStationIndex] = RHA_Normal;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/NormalStation.png")));
    if(!isReverse)
    {
        for(int i=currentStationIndex-1;i>=0;i--)
        {
            if(stationState[i]==RHA_Pass)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    else
    {
        for(int i=currentStationIndex+1;i<stationsNum;i++)
        {
            if(stationState[i]==RHA_Pass)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    stationState[currentStationIndex] = RHA_Pass;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
    //显示当前站台
    showCurrentStation();
}
//进站
void MainWindow::arriveStation()
{
    isArrive = true;
    stationState[currentStationIndex] = RHA_Pass;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
    //显示当前站台
    showCurrentStation();
}
//离站
void MainWindow::leaveStation()
{
    isArrive = false;
    stationState[currentStationIndex] = RHA_Pass;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/PassStation.png")));
    if(isReverse)
    {
        for(int i=currentStationIndex-1;i>=0;i--)
        {
            if(stationState[i]==RHA_Normal)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    else
    {
        for(int i=currentStationIndex+1;i<stationsNum;i++)
        {
            if(stationState[i]==RHA_Normal)
            {
                currentStationIndex = i;
                break;
            }
        }
    }
    stationState[currentStationIndex] = RHA_Normal;
    labelStationPix[currentStationIndex].setPixmap(QPixmap(QString::fromUtf8("image/NormalStation.png")));
    //显示当前站台
    showCurrentStation();
}
//启动
void MainWindow::start()
{
    msgHandle->start();
}
//口播，司机对整列车进行讲话广播
void MainWindow::pa()
{
    msgHandle->pa();
}
//紧急对讲应答，司机对报警进行应答
void MainWindow::pc()
{
    msgHandle->pc();
}
//司机与司机之间进行对讲
void MainWindow::cc()
{
    msgHandle->cc();
}
//音量调节
void MainWindow::sp()
{
    msgHandle->sp();
}
//监听
void MainWindow::mo()
{
    msgHandle->mo();
}
//push to talk，按下时讲话，松开时听话
void MainWindow::ptt(bool push)
{
    msgHandle->ptt(push);
}
