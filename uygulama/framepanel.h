#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include "crctablo.h"

class Butonlar;  // ❗️Forward declaration burada kalacak

namespace Ui {
class FramePanel;
}

class FramePanel : public QDialog
{
    Q_OBJECT

public:
    explicit FramePanel(const std::vector<std::string>& allFrames, Butonlar* previousPage, QWidget *parent = nullptr);
    ~FramePanel();

    void startCrcAnimation();

private slots:
    void nextStep();

private:
    void updateDisplay();

    Ui::FramePanel *ui;
    QLabel *frameLabel;
    QLabel *crcAnimLabel;
    QLabel *crcResultLabel;
    CrcTablo *crcTablo;

    Butonlar* previousPage;
    std::string frameBits;
    std::vector<std::string> frames;

    std::string data;
    std::string generator;
    int step;

    QTimer* timer;
};

#endif // FRAMEPANEL_H
