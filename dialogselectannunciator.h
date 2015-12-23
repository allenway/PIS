#ifndef DIALOGSELECTANNUNCIATOR_H
#define DIALOGSELECTANNUNCIATOR_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
namespace Ui {
    class DialogSelectAnnunciator;
}

class DialogSelectAnnunciator : public QDialog {
    Q_OBJECT
public:
    DialogSelectAnnunciator(QWidget *parent = 0);
    ~DialogSelectAnnunciator();
    void select(uchar *d);

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::DialogSelectAnnunciator *ui;
    //共8个字节,每两位表示一个警报器，如：
    //bit[7,6] bit[5,4] bit[3,2] bit[1,0]
    //警报1     警报2    警报3     警报4
    uchar *annunciator;
    QGroupBox car[8];
    QLabel label[8][4];
    QTimer *timer;
    int selectCar;  //选择车厢号
    int selectIndex;    //选择的警报器号
    void selectPrev();  //光标选择上一个
    void selectNext();  //光标选择下一个
private slots:
    void timeout();
};

#endif // DIALOGSELECTANNUNCIATOR_H
