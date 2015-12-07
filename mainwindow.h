#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include "formmenu.h"
#include "message.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void stationChange();//车站信息改变，更新UI界面；如运行方向、不经过车站改变

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent ( QKeyEvent *e );
    //void keyReleaseEvent( QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);
private:
    Ui::MainWindow *ui;
    int stationsNum;                //站台数量
    QLabel *labelStationName;       //站台名字
    QLabel *labelStationPix;        //站台图标
    QLabel *labelDirection;         //行驶方向
    int currentStationIndex;        //当前站台索引号
    bool isArrive;                  //是否到站
    bool isReverse;                 //是否反向
    QTimer *timerFlash;              //闪动显示离站状态定时器
    enum StationState{RHA_NoPass,RHA_Normal,RHA_Pass,RHA_Unknow} *stationState;  //当前车站的状态
    FormMenu *menu;     //菜单界面
    Message *msgHandle; //消息处理器


    void loadMap();     //  车站地图信息加载
    void showCurrentStation();  //显示当前车站
    void nextStation();         //下一车站
    void prevStation();         //上一车站
    void arriveStation();       //进站
    void leaveStation();        //离站

private slots:
    void flashShowStation();      //闪动显示离站状态

};

#endif // MAINWINDOW_H
