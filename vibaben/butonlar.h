#ifndef BUTONLAR_H
#define BUTONLAR_H

#include <QDialog>
#include <vector>
#include <string>

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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Butonlar *ui;
    FramePanel *framePanel;
    CrcTablo *crcTablo;
    Checksum* checksum;

    std::vector<std::string> frames;  // tüm frameler (tablo için)
};

#endif // BUTONLAR_H
