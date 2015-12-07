#ifndef FORMAUDIO_H
#define FORMAUDIO_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QDir>

#define MUSIC_DIR   "./mp3"

namespace Ui {
    class FormAudio;
}

class FormAudio : public QWidget {
    Q_OBJECT
public:
    FormAudio(QWidget *parent = 0);
    ~FormAudio();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::FormAudio *ui;
    QList<QPushButton *> buttonList;
    int buttonListIndex;
    void loadMusicFile();

private slots:
    void on_pushButtonNext_clicked();
    void on_pushButtonPrev_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonPlay_clicked();
};

#endif // FORMAUDIO_H
