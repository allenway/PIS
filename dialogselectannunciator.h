#ifndef DIALOGSELECTANNUNCIATOR_H
#define DIALOGSELECTANNUNCIATOR_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
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
    uchar *annunciator;
    QGroupBox car[8];
    QLabel label[8][4];
};

#endif // DIALOGSELECTANNUNCIATOR_H
