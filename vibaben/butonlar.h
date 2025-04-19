#ifndef BUTONLAR_H
#define BUTONLAR_H

#include <QDialog>
#include <vector>
#include <string>

// ❗️Forward declaration (çift taraflı bağımlılığı kırar)
class FramePanel;

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

private:
    Ui::Butonlar *ui;
    FramePanel *framePanel;
    std::vector<std::string> frames;  // tüm frameler (tablo için)
};

#endif // BUTONLAR_H
