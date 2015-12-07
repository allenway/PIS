#ifndef FORMSYSSTATUS_H
#define FORMSYSSTATUS_H

#include <QWidget>

namespace Ui {
    class FormSysStatus;
}

class FormSysStatus : public QWidget {
    Q_OBJECT
public:
    FormSysStatus(QWidget *parent = 0);
    ~FormSysStatus();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::FormSysStatus *ui;
};

#endif // FORMSYSSTATUS_H
