#ifndef FORMSTATIONSET_H
#define FORMSTATIONSET_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QListWidgetItem>
#include <QTableWidgetItem>


namespace Ui {
    class FormStationSet;
}

class FormStationSet : public QWidget {
    Q_OBJECT
public:
    FormStationSet(QWidget *parent = 0);
    ~FormStationSet();
signals:
    void stationChanged();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::FormStationSet *ui;
    QList<QWidget *> widgetList;   //由于维护光标选择部件
    int widgetListIndex;

    bool isStationChanged;
    void selectWidget();
    void doMenuKey();


private slots:

    void on_checkBoxReverse_clicked();
    void on_pushButtonStopBro_clicked();
    void on_pushButtonStartBro_clicked();
};

#endif // FORMSTATIONSET_H
