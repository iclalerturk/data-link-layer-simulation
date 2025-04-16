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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DosyaAcma
{
public:
    QPushButton *btn_dosyaAc;
    QLineEdit *lineEdit_dosyaYolu;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *labelFrame;
    QLabel *labelTitle;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelAnaVeri;
    QWidget *frameContainer;

    void setupUi(QDialog *DosyaAcma)
    {
        if (DosyaAcma->objectName().isEmpty())
            DosyaAcma->setObjectName("DosyaAcma");
        DosyaAcma->resize(800, 600);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(0, 99, 177, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        QBrush brush3(QColor(217, 240, 249, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        QBrush brush4(QColor(90, 113, 122, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        QBrush brush5(QColor(119, 151, 163, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        QBrush brush6(QColor(179, 226, 244, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush3);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush8(QColor(0, 0, 0, 127));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush);
        QBrush brush9(QColor(90, 113, 122, 127));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush9);
#endif
        QBrush brush10(QColor(249, 253, 255, 255));
        brush10.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush10);
#endif
        DosyaAcma->setPalette(palette);
        DosyaAcma->setAutoFillBackground(true);
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
        pushButton->setGeometry(QRect(630, 360, 131, 131));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(DosyaAcma);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(100, 130, 601, 71));
        pushButton_2->setFont(font1);
        labelFrame = new QLabel(DosyaAcma);
        labelFrame->setObjectName("labelFrame");
        labelFrame->setGeometry(QRect(320, 260, 421, 51));
        labelFrame->setFont(font);
        labelFrame->setAutoFillBackground(true);
        labelFrame->setFrameShape(QFrame::Shape::Box);
        labelFrame->setLineWidth(5);
        labelTitle = new QLabel(DosyaAcma);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(40, 260, 231, 51));
        labelTitle->setFont(font);
        labelTitle->setFrameShape(QFrame::Shape::Box);
        labelTitle->setFrameShadow(QFrame::Shadow::Plain);
        labelTitle->setLineWidth(5);
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(DosyaAcma);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 230, 131, 31));
        label_2->setFont(font);
        label_3 = new QLabel(DosyaAcma);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(320, 230, 191, 31));
        label_3->setFont(font);
        labelAnaVeri = new QLabel(DosyaAcma);
        labelAnaVeri->setObjectName("labelAnaVeri");
        labelAnaVeri->setGeometry(QRect(60, 340, 351, 151));
        frameContainer = new QWidget(DosyaAcma);
        frameContainer->setObjectName("frameContainer");
        frameContainer->setGeometry(QRect(300, 320, 321, 181));
#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(DosyaAcma);

        QMetaObject::connectSlotsByName(DosyaAcma);
    } // setupUi

    void retranslateUi(QDialog *DosyaAcma)
    {
        DosyaAcma->setWindowTitle(QCoreApplication::translate("DosyaAcma", "Dialog", nullptr));
        btn_dosyaAc->setText(QCoreApplication::translate("DosyaAcma", "Dosya A\303\247", nullptr));
        label->setText(QCoreApplication::translate("DosyaAcma", "Se\303\247ti\304\237iniz dosya yolu:", nullptr));
        pushButton->setText(QCoreApplication::translate("DosyaAcma", "Dosyay\304\261 G\303\266ndermeye Ba\305\237la", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DosyaAcma", "Veriyi Framelere B\303\266l", nullptr));
        labelFrame->setText(QString());
        labelTitle->setText(QString());
        label_2->setText(QCoreApplication::translate("DosyaAcma", "Frame Say\304\261s\304\261", nullptr));
        label_3->setText(QCoreApplication::translate("DosyaAcma", "Olu\305\237turulan Frameler", nullptr));
        labelAnaVeri->setText(QCoreApplication::translate("DosyaAcma", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DosyaAcma: public Ui_DosyaAcma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOSYAACMA_H
