/********************************************************************************
** Form generated from reading UI file 'checksum.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKSUM_H
#define UI_CHECKSUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Checksum
{
public:
    QListWidget *listWidget;
    QLabel *labelStep;
    QLabel *labelHex;

    void setupUi(QDialog *Checksum)
    {
        if (Checksum->objectName().isEmpty())
            Checksum->setObjectName("Checksum");
        Checksum->resize(1024, 640);
        listWidget = new QListWidget(Checksum);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(40, 150, 256, 192));
        labelStep = new QLabel(Checksum);
        labelStep->setObjectName("labelStep");
        labelStep->setGeometry(QRect(80, 420, 431, 71));
        labelHex = new QLabel(Checksum);
        labelHex->setObjectName("labelHex");
        labelHex->setGeometry(QRect(80, 540, 171, 31));

        retranslateUi(Checksum);

        QMetaObject::connectSlotsByName(Checksum);
    } // setupUi

    void retranslateUi(QDialog *Checksum)
    {
        Checksum->setWindowTitle(QCoreApplication::translate("Checksum", "Dialog", nullptr));
        labelStep->setText(QCoreApplication::translate("Checksum", "TextLabel", nullptr));
        labelHex->setText(QCoreApplication::translate("Checksum", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Checksum: public Ui_Checksum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKSUM_H
