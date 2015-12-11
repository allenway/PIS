/********************************************************************************
** Form generated from reading ui file 'formstationset.ui'
**
** Created: Fri Dec 11 15:04:04 2015
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORMSTATIONSET_H
#define UI_FORMSTATIONSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormStationSet
{
public:
    QLabel *labelBG;
    QGroupBox *groupBox;
    QListWidget *listWidgetStation;
    QCheckBox *checkBoxReverse;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidgetBroadcast;
    QPushButton *pushButtonStartBro;
    QPushButton *pushButtonStopBro;

    void setupUi(QWidget *FormStationSet)
    {
        if (FormStationSet->objectName().isEmpty())
            FormStationSet->setObjectName(QString::fromUtf8("FormStationSet"));
        FormStationSet->resize(480, 272);
        FormStationSet->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	color: rgb(255, 255, 255);\n"
"	border-width:3px;\n"
"	border-style:solid;\n"
"	border-color: rgb(9,183,198);\n"
"}\n"
"QCheckBox{\n"
"	color: rgb(60, 60, 60);\n"
"	border:none;\n"
"	background-color: rgb(176, 143, 133);\n"
"}\n"
"QCheckBox::focus{\n"
"	color: rgb(60, 60, 60);\n"
"	border:none;\n"
"	background-color: rgb(208, 230, 255);\n"
"}\n"
"QPushButton{\n"
"	color:rgb(255, 255, 255);\n"
"	border:none;\n"
"	background-color: rgb(95, 95, 95);\n"
"}\n"
"QPushButton::focus{\n"
"	color:rgb(60, 60, 60);\n"
"	border:none;\n"
"	background-color: rgb(208, 230, 255);\n"
"}\n"
""));
        labelBG = new QLabel(FormStationSet);
        labelBG->setObjectName(QString::fromUtf8("labelBG"));
        labelBG->setGeometry(QRect(0, 0, 480, 272));
        labelBG->setPixmap(QPixmap(QString::fromUtf8("image/BK.png")));
        groupBox = new QGroupBox(FormStationSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 5, 190, 260));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        listWidgetStation = new QListWidget(groupBox);
        listWidgetStation->setObjectName(QString::fromUtf8("listWidgetStation"));
        listWidgetStation->setGeometry(QRect(5, 25, 180, 231));
        listWidgetStation->setEditTriggers(QAbstractItemView::NoEditTriggers);
        checkBoxReverse = new QCheckBox(groupBox);
        checkBoxReverse->setObjectName(QString::fromUtf8("checkBoxReverse"));
        checkBoxReverse->setGeometry(QRect(90, 5, 91, 17));
        groupBox_2 = new QGroupBox(FormStationSet);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(203, 5, 271, 260));
        tableWidgetBroadcast = new QTableWidget(groupBox_2);
        tableWidgetBroadcast->setObjectName(QString::fromUtf8("tableWidgetBroadcast"));
        tableWidgetBroadcast->setGeometry(QRect(5, 25, 260, 192));
        tableWidgetBroadcast->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetBroadcast->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetBroadcast->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetBroadcast->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetBroadcast->horizontalHeader()->setVisible(false);
        tableWidgetBroadcast->horizontalHeader()->setDefaultSectionSize(100);
        tableWidgetBroadcast->verticalHeader()->setVisible(false);
        tableWidgetBroadcast->verticalHeader()->setDefaultSectionSize(20);
        pushButtonStartBro = new QPushButton(groupBox_2);
        pushButtonStartBro->setObjectName(QString::fromUtf8("pushButtonStartBro"));
        pushButtonStartBro->setGeometry(QRect(5, 223, 127, 27));
        pushButtonStopBro = new QPushButton(groupBox_2);
        pushButtonStopBro->setObjectName(QString::fromUtf8("pushButtonStopBro"));
        pushButtonStopBro->setGeometry(QRect(135, 223, 127, 27));

        retranslateUi(FormStationSet);

        QMetaObject::connectSlotsByName(FormStationSet);
    } // setupUi

    void retranslateUi(QWidget *FormStationSet)
    {
        FormStationSet->setWindowTitle(QApplication::translate("FormStationSet", "Form", 0, QApplication::UnicodeUTF8));
        labelBG->setText(QString());
        groupBox->setTitle(QApplication::translate("FormStationSet", "Station Set", 0, QApplication::UnicodeUTF8));
        checkBoxReverse->setText(QApplication::translate("FormStationSet", "Reverse", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormStationSet", "Broadcast", 0, QApplication::UnicodeUTF8));
        pushButtonStartBro->setText(QApplication::translate("FormStationSet", "StartBro", 0, QApplication::UnicodeUTF8));
        pushButtonStopBro->setText(QApplication::translate("FormStationSet", "StopBro", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FormStationSet);
    } // retranslateUi

};

namespace Ui {
    class FormStationSet: public Ui_FormStationSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSTATIONSET_H
