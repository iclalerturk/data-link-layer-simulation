/********************************************************************************
** Form generated from reading UI file 'crctablo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRCTABLO_H
#define UI_CRCTABLO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CrcTablo
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *CrcTablo)
    {
        if (CrcTablo->objectName().isEmpty())
            CrcTablo->setObjectName("CrcTablo");
        CrcTablo->resize(1024, 640);
        pushButton = new QPushButton(CrcTablo);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(910, 310, 111, 51));

        retranslateUi(CrcTablo);

        QMetaObject::connectSlotsByName(CrcTablo);
    } // setupUi

    void retranslateUi(QDialog *CrcTablo)
    {
        CrcTablo->setWindowTitle(QCoreApplication::translate("CrcTablo", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("CrcTablo", "Checksum i\303\247in\n"
"ilerle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CrcTablo: public Ui_CrcTablo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRCTABLO_H
