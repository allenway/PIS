#ifndef FORMMENU_H
#define FORMMENU_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "formstationset.h"
#include "formsysstatus.h"
#include "formaudio.h"
#include "formmenu.h"

namespace Ui {
    class FormMenu;
}

class FormMenu : public QWidget {
    Q_OBJECT
public:
    FormMenu(QWidget *parent = 0);
    ~FormMenu();
    void showAudio();
signals:
    void stationChanged();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::FormMenu *ui;
    FormStationSet *stationSet;
    FormSysStatus *sysStatus;
    FormAudio *audio;
    QList<QPushButton *> buttonList;
    int buttonListIndex;



private slots:
    void on_pushButtonSysStatus_clicked();
    void on_pushButtonAudio_clicked();
    void on_pushButtonStationSet_clicked();
};

#endif // FORMMENU_H
