/********************************************************************************
** Form generated from reading UI file 'framepanel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEPANEL_H
#define UI_FRAMEPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_FramePanel
{
public:

    void setupUi(QDialog *FramePanel)
    {
        if (FramePanel->objectName().isEmpty())
            FramePanel->setObjectName("FramePanel");
        FramePanel->resize(1024, 640);

        retranslateUi(FramePanel);

        QMetaObject::connectSlotsByName(FramePanel);
    } // setupUi

    void retranslateUi(QDialog *FramePanel)
    {
        FramePanel->setWindowTitle(QCoreApplication::translate("FramePanel", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FramePanel: public Ui_FramePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEPANEL_H
