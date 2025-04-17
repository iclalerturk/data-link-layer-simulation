#ifndef DOSYAACMA_H
#define DOSYAACMA_H
#include "frameekrani.h"
#include <QDialog>
#include <QTimer>
#include <vector>
#include <Qscrollarea.h>

namespace Ui {
class DosyaAcma;
}

class DosyaAcma : public QDialog
{
    Q_OBJECT

public:
    explicit DosyaAcma(QWidget *parent = nullptr);
    ~DosyaAcma();

private slots:
    void on_btn_dosyaAc_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void showNextFrame();
    void showNextVisualFrame();

private:
    Ui::DosyaAcma *ui;
    FrameEkrani *frameEkrani;
    std::vector<std::vector<bool>> frames;
    int currentFrameIndex = 0;
    QTimer *timer;
    QTimer *animTimer = nullptr;
    QScrollArea *scrollArea;

};

#endif // DOSYAACMA_H
