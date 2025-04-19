#ifndef FRAMEEKRANI_H
#define FRAMEEKRANI_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
#include <vector>
#include <string>

// ✅ Checksum fonksiyonu için ekleme:
#include "checksum.h"

namespace Ui {
class FrameEkrani;
}

class FrameEkrani : public QDialog
{
    Q_OBJECT

public:
    explicit FrameEkrani(const std::vector<std::string>& frames, QWidget *parent = nullptr);
    ~FrameEkrani();

private slots:
    void gonderFrame();
    void frameIlerle();
    void kontrolEt();

private:
    Ui::FrameEkrani *ui;
    QLabel *gondericiKutusu;
    QLabel *aliciKutusu;
    QLabel *mektup;
    QLabel *durumEtiketi;
    QPushButton *gonderButonu;
    QLabel *headerLabel;
    QLabel *dataLabel;
    QLabel *trailerLabel;

    QPropertyAnimation *headerAnim;
    QPropertyAnimation *dataAnim;
    QPropertyAnimation *trailerAnim;

    QTimer *ackTimer;
    QPropertyAnimation *animasyon;
    std::vector<std::string> frameList;
    std::vector<std::string> crcList;

    bool ackGeldi;
};

#endif // FRAMEEKRANI_H
