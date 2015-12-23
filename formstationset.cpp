#include "formstationset.h"
#include "ui_formstationset.h"
#include "rha.h"
#include "mplayerprocess.h"
#include <QListWidgetItem>
#include <QListWidget>
#include <QSettings>
#include <QDebug>
FormStationSet::FormStationSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormStationSet)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    installEventFilter(this);
    ui->tableWidgetBroadcast->installEventFilter(this);
    ui->listWidgetStation->installEventFilter(this);

    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    int stationsNum;
    QString str;
    QListWidgetItem *litem;
    QStringList ignorelist;
    //加载站台信息
    if(settings.value("StationName/Reverse").toBool())
        ui->checkBoxReverse->setChecked(true);
    else
        ui->checkBoxReverse->setChecked(false);
    ui->listWidgetStation->setSortingEnabled(false);
    stationsNum = settings.value("StationName/Count").toInt();
    ignorelist = settings.value("StationName/Ignore").toString().split(",");
    for(int i=0;i<stationsNum;i++)
    {
        str = "StationName/" + QString::number(i+1);
        litem = new QListWidgetItem(settings.value(str).toString());
        if(ignorelist.contains(QString::number(i+1)))
            litem->setCheckState(Qt::Unchecked);
        else
            litem->setCheckState(Qt::Checked);
        ui->listWidgetStation->addItem(litem);
    }
    //加载广播信息
    QTableWidgetItem *titem;
    int broadcastsNum;
    broadcastsNum = settings.value("BroadCastInfo/Count").toInt();
    ui->tableWidgetBroadcast->setSortingEnabled(false);
    ui->tableWidgetBroadcast->setColumnCount(2);
    ui->tableWidgetBroadcast->setRowCount(broadcastsNum);
    ui->tableWidgetBroadcast->horizontalHeader()->setVisible(false);
    ui->tableWidgetBroadcast->verticalHeader()->setVisible(false);
    QStringList broadcastList;
    for(int i=0;i<broadcastsNum;i++)
    {
        str = "BroadCastInfo/" + QString::number(i+1);
        broadcastList = settings.value(str).toString().split(",");
        titem = new QTableWidgetItem();
        titem->setCheckState(Qt::Unchecked);
        titem->setText(broadcastList.first());
        ui->tableWidgetBroadcast->setItem(i, 0,titem);
        titem = new QTableWidgetItem();
        titem->setText(broadcastList.last());
        ui->tableWidgetBroadcast->setItem(i, 1,titem);
    }
    ui->tableWidgetBroadcast->setColumnWidth(0,50);
    ui->tableWidgetBroadcast->setColumnWidth(1,185);
    ui->tableWidgetBroadcast->resizeRowsToContents();
    //初始化widgetList
    widgetList.append(ui->checkBoxReverse);
    for(int i=0;i<ui->listWidgetStation->count();i++)
    {
        widgetList.append(ui->listWidgetStation);
    }
    for(int i=0;i<ui->tableWidgetBroadcast->rowCount();i++)
    {
        widgetList.append(ui->tableWidgetBroadcast);
    }
    widgetList.append(ui->pushButtonStartBro);
    widgetList.append(ui->pushButtonStopBro);
    widgetListIndex = 0;
    widgetList.at(widgetListIndex)->setFocus();
    isStationChanged = false;
}

FormStationSet::~FormStationSet()
{
    delete ui;
}

void FormStationSet::changeEvent(QEvent *e)
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
void FormStationSet::selectWidget()
{
    QWidget *w;
    static int li = -1;
    static int  ti = -1;
    if(li!= -1)  //清空前次选择
    {
        ui->listWidgetStation->item(li)->setSelected(false);
        li= -1;
    }
    if(ti!=-1)  //清空前次选择
    {
        ui->tableWidgetBroadcast->item(ti,0)->setSelected(false);
        ui->tableWidgetBroadcast->item(ti,1)->setSelected(false);
        ti = -1;
    }
    w = widgetList.at(widgetListIndex);
    if(w==ui->listWidgetStation)
    {
        li = widgetListIndex-widgetList.indexOf(ui->listWidgetStation);
        ui->listWidgetStation->setCurrentRow(li);
    }
    else if(w==ui->tableWidgetBroadcast)
    {
        ti = widgetListIndex-widgetList.indexOf(ui->tableWidgetBroadcast);
        ui->tableWidgetBroadcast->selectRow(ti);
    }
    w->setFocus();
}
void FormStationSet::doMenuKey()
{
    QWidget *w;
    Qt::CheckState state;
    w = widgetList.at(widgetListIndex);
    if(w==ui->listWidgetStation)  //站台设置,是否要经过此站台
    {
       QListWidgetItem *li;
       li = ui->listWidgetStation->item(widgetListIndex-widgetList.indexOf(ui->listWidgetStation));
       state= li->checkState();
       state = (state==Qt::Checked?Qt::Unchecked:Qt::Checked);
       li->setCheckState(state);

       QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
       settings.setIniCodec("UTF-8");
       QString str;
       QStringList strlist;
       str = QString::number(widgetListIndex-widgetList.indexOf(ui->listWidgetStation)+1);
       strlist = settings.value("StationName/Ignore").toString().split(",");
       if(state==Qt::Checked)
       {
           if(strlist.contains(str))
           {
               strlist.removeAll(str);
               settings.setValue("StationName/Ignore",strlist.join(","));
           }
       }
       else
       {
           if(!strlist.contains(str))
           {
               strlist.append(str);
               settings.setValue("StationName/Ignore",strlist.join(","));
           }

       }
       isStationChanged = true;
       settings.sync();

    }
    else if(w==ui->tableWidgetBroadcast)   //广播选择
    {
       static QTableWidgetItem *ti = NULL;
       if(ti!=NULL)
           ti->setCheckState(Qt::Unchecked);
       ti = ui->tableWidgetBroadcast->item(widgetListIndex-widgetList.indexOf(ui->tableWidgetBroadcast),0);
       state = ti->checkState();
       state = (state==Qt::Checked?Qt::Unchecked:Qt::Checked);
       ti->setCheckState(state);
    }
    else if(w==ui->checkBoxReverse) //运行方向选择
    {
        ui->checkBoxReverse->click();
    }
    else if(w==ui->pushButtonStartBro) //打开广播
    {
        ui->pushButtonStartBro->click();
    }
    else if(w==ui->pushButtonStopBro)  //关闭广播
    {
        ui->pushButtonStopBro->click();
    }
}
bool FormStationSet::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        //qDebug("menu key press:0x%x",keyEvent->key());
        switch(keyEvent->key()){
        case RHA_KEY_MENU:
            qDebug("KEY_MENU");
            doMenuKey();
            break;
        case RHA_KEY_UP:
            qDebug("KEY_UP");
            widgetListIndex>0?widgetListIndex--:widgetListIndex = widgetList.count()-1;
            selectWidget();
            break;
        case RHA_KEY_DN:
            qDebug("KEY_DN");
            widgetListIndex<widgetList.count()-1?widgetListIndex++:widgetListIndex=0;
            selectWidget();
            break;
        case RHA_KEY_BACK:
            qDebug("KEY_BACK");
            //退出界面
            if(isStationChanged)
                emit stationChanged();
            isStationChanged = false;
            hide();
            break;
        }
        return true;
    }
    else
        return QObject::eventFilter(obj, e);
}

void FormStationSet::on_pushButtonStartBro_clicked()
{
    QTableWidgetItem *ti;
    for(int i = 0;i<ui->tableWidgetBroadcast->rowCount();i++)
    {
        ti = ui->tableWidgetBroadcast->item(i,0);
        if(ti->checkState()==Qt::Checked)
        {
            MplayerProcess::playBroadcast(ti->text());
            return;
        }
    }
}

void FormStationSet::on_pushButtonStopBro_clicked()
{
    MplayerProcess::stopBroadcast();
}

void FormStationSet::on_checkBoxReverse_clicked()
{
    //qDebug("Reverse click");
    QSettings settings(SYSTEM_CONFIG_PATH, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("StationName/Reverse",ui->checkBoxReverse->isChecked());
    settings.sync();
    isStationChanged = true;
}


