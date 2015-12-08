/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Mon Dec 7 16:12:09 2015
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelMainBG;
    QLabel *labelLine1;
    QLabel *labelLine2;
    QLabel *labelLine3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(480, 272);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        centralWidget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        labelMainBG = new QLabel(centralWidget);
        labelMainBG->setObjectName(QString::fromUtf8("labelMainBG"));
        labelMainBG->setGeometry(QRect(0, 0, 480, 272));
        labelMainBG->setTextFormat(Qt::AutoText);
        labelMainBG->setPixmap(QPixmap(QString::fromUtf8("image/MainBk.png")));
        labelMainBG->setScaledContents(false);
        labelLine1 = new QLabel(centralWidget);
        labelLine1->setObjectName(QString::fromUtf8("labelLine1"));
        labelLine1->setGeometry(QRect(20, 73, 440, 5));
        labelLine1->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 111, 127);"));
        labelLine2 = new QLabel(centralWidget);
        labelLine2->setObjectName(QString::fromUtf8("labelLine2"));
        labelLine2->setGeometry(QRect(20, 222, 440, 5));
        labelLine2->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 111, 127);"));
        labelLine3 = new QLabel(centralWidget);
        labelLine3->setObjectName(QString::fromUtf8("labelLine3"));
        labelLine3->setGeometry(QRect(457, 73, 5, 154));
        labelLine3->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 111, 127);"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        labelMainBG->setText(QString());
        labelLine1->setText(QString());
        labelLine2->setText(QString());
        labelLine3->setText(QString());
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
