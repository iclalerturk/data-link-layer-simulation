#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include "crctablo.h"

namespace Ui {
class FramePanel;
}

class FramePanel : public QDialog
{
    Q_OBJECT

public:
    explicit FramePanel(const std::vector<std::string>& allFrames, QWidget *parent = nullptr);
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

    std::string frameBits;
    std::vector<std::string> frames;  // tüm frameler (tablo için)

    std::string data;
    std::string generator;
    int step;

    QTimer* timer;
};

#endif // FRAMEPANEL_H
