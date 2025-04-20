/********************************************************************************
** Form generated from reading UI file 'frameekrani.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEEKRANI_H
#define UI_FRAMEEKRANI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_FrameEkrani
{
public:

    void setupUi(QDialog *FrameEkrani)
    {
        if (FrameEkrani->objectName().isEmpty())
            FrameEkrani->setObjectName("FrameEkrani");
        FrameEkrani->resize(1024, 640);
        QPalette palette;
        QBrush brush(QColor(62, 132, 244, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        QBrush brush1(QColor(143, 217, 244, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        FrameEkrani->setPalette(palette);

        retranslateUi(FrameEkrani);

        QMetaObject::connectSlotsByName(FrameEkrani);
    } // setupUi

    void retranslateUi(QDialog *FrameEkrani)
    {
        FrameEkrani->setWindowTitle(QCoreApplication::translate("FrameEkrani", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrameEkrani: public Ui_FrameEkrani {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEEKRANI_H
