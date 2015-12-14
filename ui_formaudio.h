/********************************************************************************
** Form generated from reading ui file 'formaudio.ui'
**
** Created: Mon Dec 14 15:36:05 2015
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORMAUDIO_H
#define UI_FORMAUDIO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAudio
{
public:
    QLabel *labelBG;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonPrev;
    QPushButton *pushButtonNext;

    void setupUi(QWidget *FormAudio)
    {
        if (FormAudio->objectName().isEmpty())
            FormAudio->setObjectName(QString::fromUtf8("FormAudio"));
        FormAudio->resize(480, 272);
        FormAudio->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	color: rgb(255, 255, 255);\n"
"	border-width:3px;\n"
"	border-style:solid;\n"
"	border-color: rgb(9,183,198);\n"
"}\n"
"QPushButton{\n"
"	color: rgb(255, 255, 255);\n"
"	border:none;\n"
"	background-color: rgb(95, 95, 95);\n"
"}\n"
"QPushButton::focus{\n"
"	color:rgb(60, 60, 60);\n"
"	border:none;\n"
"	background-color: rgb(208, 230, 255);\n"
"}\n"
"QPushButton::disabled{\n"
"	color:rgb(0, 0, 0);\n"
"	border:none;\n"
"	background-color: rgb(226, 226, 226);\n"
"}\n"
""));
        labelBG = new QLabel(FormAudio);
        labelBG->setObjectName(QString::fromUtf8("labelBG"));
        labelBG->setGeometry(QRect(0, 0, 480, 272));
        labelBG->setPixmap(QPixmap(QString::fromUtf8("image/BK.png")));
        groupBox = new QGroupBox(FormAudio);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 5, 470, 262));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(131, 20, 331, 231));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pushButtonPlay = new QPushButton(groupBox);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(10, 20, 110, 51));
        pushButtonStop = new QPushButton(groupBox);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(10, 79, 110, 51));
        pushButtonPrev = new QPushButton(groupBox);
        pushButtonPrev->setObjectName(QString::fromUtf8("pushButtonPrev"));
        pushButtonPrev->setGeometry(QRect(10, 139, 110, 51));
        pushButtonNext = new QPushButton(groupBox);
        pushButtonNext->setObjectName(QString::fromUtf8("pushButtonNext"));
        pushButtonNext->setGeometry(QRect(10, 199, 110, 51));

        retranslateUi(FormAudio);

        QMetaObject::connectSlotsByName(FormAudio);
    } // setupUi

    void retranslateUi(QWidget *FormAudio)
    {
        FormAudio->setWindowTitle(QApplication::translate("FormAudio", "Form", 0, QApplication::UnicodeUTF8));
        labelBG->setText(QString());
        groupBox->setTitle(QApplication::translate("FormAudio", "MP3", 0, QApplication::UnicodeUTF8));
        pushButtonPlay->setText(QApplication::translate("FormAudio", "Play", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("FormAudio", "Stop", 0, QApplication::UnicodeUTF8));
        pushButtonPrev->setText(QApplication::translate("FormAudio", "Prev", 0, QApplication::UnicodeUTF8));
        pushButtonNext->setText(QApplication::translate("FormAudio", "Next", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FormAudio);
    } // retranslateUi

};

namespace Ui {
    class FormAudio: public Ui_FormAudio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAUDIO_H
