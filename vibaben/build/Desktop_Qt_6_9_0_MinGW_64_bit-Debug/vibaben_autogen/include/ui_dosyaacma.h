/********************************************************************************
** Form generated from reading UI file 'dosyaacma.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOSYAACMA_H
#define UI_DOSYAACMA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DosyaAcma
{
public:
    QPushButton *btn_dosyaAc;
    QLineEdit *lineEdit_dosyaYolu;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *DosyaAcma)
    {
        if (DosyaAcma->objectName().isEmpty())
            DosyaAcma->setObjectName("DosyaAcma");
        DosyaAcma->resize(800, 600);
        btn_dosyaAc = new QPushButton(DosyaAcma);
        btn_dosyaAc->setObjectName("btn_dosyaAc");
        btn_dosyaAc->setGeometry(QRect(610, 80, 101, 31));
        lineEdit_dosyaYolu = new QLineEdit(DosyaAcma);
        lineEdit_dosyaYolu->setObjectName("lineEdit_dosyaYolu");
        lineEdit_dosyaYolu->setGeometry(QRect(100, 80, 481, 31));
        label = new QLabel(DosyaAcma);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 40, 231, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        pushButton = new QPushButton(DosyaAcma);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(100, 200, 611, 121));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);

        retranslateUi(DosyaAcma);

        QMetaObject::connectSlotsByName(DosyaAcma);
    } // setupUi

    void retranslateUi(QDialog *DosyaAcma)
    {
        DosyaAcma->setWindowTitle(QCoreApplication::translate("DosyaAcma", "Dialog", nullptr));
        btn_dosyaAc->setText(QCoreApplication::translate("DosyaAcma", "Dosya A\303\247", nullptr));
        label->setText(QCoreApplication::translate("DosyaAcma", "Se\303\247ti\304\237iniz dosya yolu:", nullptr));
        pushButton->setText(QCoreApplication::translate("DosyaAcma", "Dosyay\304\261 G\303\266ndermeye Ba\305\237la", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DosyaAcma: public Ui_DosyaAcma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOSYAACMA_H
