/********************************************************************************
** Form generated from reading ui file 'dialogselectannunciator.ui'
**
** Created: Tue Dec 22 19:30:03 2015
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGSELECTANNUNCIATOR_H
#define UI_DIALOGSELECTANNUNCIATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogSelectAnnunciator
{
public:
    QLabel *label;

    void setupUi(QDialog *DialogSelectAnnunciator)
    {
        if (DialogSelectAnnunciator->objectName().isEmpty())
            DialogSelectAnnunciator->setObjectName(QString::fromUtf8("DialogSelectAnnunciator"));
        DialogSelectAnnunciator->resize(480, 272);
        DialogSelectAnnunciator->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	color: rgb(255, 255, 255);\n"
"	border-width:1px;\n"
"	border-style:solid;\n"
"	border-color: rgb(9,183,198);\n"
"	background-color: rgb(89, 64, 64);\n"
"}\n"
"QLabel{\n"
"	background-color: rgb(254, 255, 185);\n"
"}"));
        label = new QLabel(DialogSelectAnnunciator);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 480, 272));
        label->setPixmap(QPixmap(QString::fromUtf8("image/BK.png")));
        label->setScaledContents(true);

        retranslateUi(DialogSelectAnnunciator);

        QMetaObject::connectSlotsByName(DialogSelectAnnunciator);
    } // setupUi

    void retranslateUi(QDialog *DialogSelectAnnunciator)
    {
        DialogSelectAnnunciator->setWindowTitle(QApplication::translate("DialogSelectAnnunciator", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        Q_UNUSED(DialogSelectAnnunciator);
    } // retranslateUi

};

namespace Ui {
    class DialogSelectAnnunciator: public Ui_DialogSelectAnnunciator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSELECTANNUNCIATOR_H
