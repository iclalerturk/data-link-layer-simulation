#ifndef FRAMEEKRANI_H
#define FRAMEEKRANI_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
#include <vector>
#include <string>

namespace Ui {
class FrameEkrani;
}

class FrameEkrani : public QDialog
{
    Q_OBJECT

public:
    explicit FrameEkrani(const std::vector<std::string>& frames, QWidget *parent = nullptr);
    ~FrameEkrani();
    // Byte Stuffing fonksiyonları
    std::string applyByteStuffing(const std::string& rawData);
    std::string removeByteStuffing(const std::string& stuffedData);


private slots:
    void gonderFrame();
    void frameIlerle();
    void kontrolEt();


private:
    Ui::FrameEkrani *ui;

    // Görsel öğeler
    QLabel *gondericiKutusu;
    QLabel *aliciKutusu;
    QLabel *mektup;
    QLabel *durumEtiketi;
    QLabel *headerLabel;
    QLabel *dataLabel;
    QLabel *trailerLabel;
    QLabel *checksumHexLabel;
    QLabel *crcIcerik;
    QLabel* ackSinyali;
    QLabel* stuffingLabel;
    QString crcText;

    // Animasyonlar
    QPropertyAnimation *headerAnim;
    QPropertyAnimation *dataAnim;
    QPropertyAnimation *trailerAnim;
    QPropertyAnimation *animasyon;

    // Kontrol
    QTimer *ackTimer;
    QPushButton *gonderButonu;


    // Frame içeriği
    std::vector<std::string> crcList;
    QStringList frameList;
    std::vector<QLabel*> crcLabels;
    std::vector<std::string> header; // & işareti kalktı

    // Durumlar
    QString hexChecksum;
    int currentFrameIndex;
};

#endif // FRAMEEKRANI_H
