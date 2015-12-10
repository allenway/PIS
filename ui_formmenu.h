/********************************************************************************
** Form generated from reading ui file 'formmenu.ui'
**
** Created: Thu Dec 10 16:05:11 2015
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORMMENU_H
#define UI_FORMMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormMenu
{
public:
    QLabel *labelBG;
    QLabel *labelName;
    QPushButton *pushButtonStationSet;
    QPushButton *pushButtonSysStatus;
    QPushButton *pushButtonAudio;

    void setupUi(QWidget *FormMenu)
    {
        if (FormMenu->objectName().isEmpty())
            FormMenu->setObjectName(QString::fromUtf8("FormMenu"));
        FormMenu->resize(120, 272);
        FormMenu->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"QLabel{\n"
"	color:rgb(255, 236, 213);\n"
"	background-color: rgb(63, 54, 50);\n"
"}"));
        labelBG = new QLabel(FormMenu);
        labelBG->setObjectName(QString::fromUtf8("labelBG"));
        labelBG->setGeometry(QRect(0, 0, 120, 272));
        labelBG->setPixmap(QPixmap(QString::fromUtf8("image/BK.png")));
        labelBG->setScaledContents(true);
        labelName = new QLabel(FormMenu);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(0, 0, 121, 41));
        QFont font;
        font.setPointSize(20);
        labelName->setFont(font);
        labelName->setStyleSheet(QString::fromUtf8(""));
        labelName->setAlignment(Qt::AlignCenter);
        pushButtonStationSet = new QPushButton(FormMenu);
        pushButtonStationSet->setObjectName(QString::fromUtf8("pushButtonStationSet"));
        pushButtonStationSet->setGeometry(QRect(15, 60, 90, 50));
        pushButtonStationSet->setStyleSheet(QString::fromUtf8(""));
        pushButtonSysStatus = new QPushButton(FormMenu);
        pushButtonSysStatus->setObjectName(QString::fromUtf8("pushButtonSysStatus"));
        pushButtonSysStatus->setGeometry(QRect(15, 125, 90, 50));
        pushButtonSysStatus->setStyleSheet(QString::fromUtf8(""));
        pushButtonAudio = new QPushButton(FormMenu);
        pushButtonAudio->setObjectName(QString::fromUtf8("pushButtonAudio"));
        pushButtonAudio->setGeometry(QRect(15, 190, 90, 50));
        pushButtonAudio->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(FormMenu);

        QMetaObject::connectSlotsByName(FormMenu);
    } // setupUi

    void retranslateUi(QWidget *FormMenu)
    {
        FormMenu->setWindowTitle(QApplication::translate("FormMenu", "Form", 0, QApplication::UnicodeUTF8));
        labelBG->setText(QString());
        labelName->setText(QApplication::translate("FormMenu", "Menu", 0, QApplication::UnicodeUTF8));
        pushButtonStationSet->setText(QApplication::translate("FormMenu", "Station Set", 0, QApplication::UnicodeUTF8));
        pushButtonSysStatus->setText(QApplication::translate("FormMenu", "Sys Status", 0, QApplication::UnicodeUTF8));
        pushButtonAudio->setText(QApplication::translate("FormMenu", "Audio", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FormMenu);
    } // retranslateUi

};

namespace Ui {
    class FormMenu: public Ui_FormMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMENU_H
