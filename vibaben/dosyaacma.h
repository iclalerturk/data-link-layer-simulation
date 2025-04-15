#ifndef DOSYAACMA_H
#define DOSYAACMA_H
#include "frameekrani.h"
#include <QDialog>

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

private:
    Ui::DosyaAcma *ui;
    FrameEkrani *frameEkrani;
};

#endif // DOSYAACMA_H
