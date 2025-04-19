#ifndef BUTONLAR_H
#define BUTONLAR_H

#include <QDialog>
#include <vector>
#include <string>
#include "frameekrani.h"
// ❗️Forward declaration (çift taraflı bağımlılığı kırar)
class FramePanel;
class CrcTablo;
class Checksum;


namespace Ui {
class Butonlar;
}

class Butonlar : public QDialog
{
    Q_OBJECT

public:
    explicit Butonlar(const std::vector<std::string>& allFrames, QWidget *parent = nullptr);
    ~Butonlar();

private slots:
    void on_pushButton_clicked();

<<<<<<< Updated upstream
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
=======
    void on_pushButton_4_clicked();
>>>>>>> Stashed changes

private:
    Ui::Butonlar *ui;
    FramePanel *framePanel;
<<<<<<< Updated upstream
    CrcTablo *crcTablo;
    Checksum* checksum;

=======
    FrameEkrani *frameEkrani;
>>>>>>> Stashed changes
    std::vector<std::string> frames;  // tüm frameler (tablo için)
};

#endif // BUTONLAR_H
