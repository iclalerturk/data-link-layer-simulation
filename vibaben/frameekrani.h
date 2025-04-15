#ifndef FRAMEEKRANI_H
#define FRAMEEKRANI_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
namespace Ui {
class FrameEkrani;
}

class FrameEkrani : public QDialog
{
    Q_OBJECT

public:
    explicit FrameEkrani(QWidget *parent = nullptr);
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

    QTimer *ackTimer;
    QPropertyAnimation *animasyon;

    bool ackGeldi;
};

#endif // FRAMEEKRANI_H
